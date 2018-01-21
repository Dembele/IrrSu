#include "GE.h"
#define VERSION L"0.02"
#define DEBUG_GEN_WIDTH 1000
#define DEBUG_GEN_HEIGHT 1000
#define TILESIZE 64
#define BUTTON_HEIGHT 60
#define BUTTON_WIDTH 200


GE::GE()
{
}


GE::~GE()
{
}

//! if returns not 0 then it crashed
int GE::init()
{
	events.init();
	setParams(settings.driverType,settings.screen.width,settings.screen.height,settings.bits,settings.vsync,settings.fullscreen, settings.antiAlias);
	device = createDeviceEx(params);
	if (!device) return 1;
	device->setWindowCaption(L"IrrSu ver" VERSION);
	device->maximizeWindow();
	driver = device->getVideoDriver();
	screenSize = driver->getScreenSize();
	tileAtlas = driver->getTexture("Media/images/tileset.png");
	menubg = driver->getTexture("Media/images/menubg.png");
	guienv = device->getGUIEnvironment();
	skin = guienv->getSkin();
	font = guienv->getFont("Media/fonts/myfont.xml");
	if (font)
		skin->setFont(font);
	fpstext = guienv->addStaticText(L"",
		core::rect<s32>(4, 4, settings.screen.width / 8, 400), false, true);
	buttonbg = driver->getTexture("Media/images/button.png");	
	screenTileSize.Height = screenSize.Height / TILESIZE + 1;
	screenTileSize.Width = screenSize.Width / TILESIZE + 1;
	context.device = device;
	context.counter = 0;


	newgame = guienv->addButton(rect<s32>(screenSize.Width / 2 - BUTTON_WIDTH / 2,
		screenSize.Height / 2 - 3 * (BUTTON_HEIGHT),
		screenSize.Width / 2 + BUTTON_WIDTH / 2,
		screenSize.Height / 2 - 2 * BUTTON_HEIGHT),
		0, B_NEWGAME, L"NEW GAME");
	load = guienv->addButton(rect<s32>(screenSize.Width / 2 - BUTTON_WIDTH / 2,
		screenSize.Height / 2 - 2 * (BUTTON_HEIGHT),
		screenSize.Width / 2 + BUTTON_WIDTH / 2,
		screenSize.Height / 2 - BUTTON_HEIGHT),
		0, B_LOAD, L"LOAD");
	options = guienv->addButton(rect<s32>(screenSize.Width / 2 - BUTTON_WIDTH / 2,
		screenSize.Height / 2,
		screenSize.Width / 2 + BUTTON_WIDTH / 2,
		screenSize.Height / 2 + BUTTON_HEIGHT),
		0, B_OPTIONS, L"OPTIONS");
	exit = guienv->addButton(rect<s32>(screenSize.Width / 2 - BUTTON_WIDTH / 2,
		screenSize.Height / 2 + 2 * (BUTTON_HEIGHT),
		screenSize.Width / 2 + BUTTON_WIDTH / 2,
		screenSize.Height / 2 + 3 * BUTTON_HEIGHT),
		0, B_EXIT, L"EXIT");

	newgame->setImage(buttonbg);
	load->setImage(buttonbg);
	options->setImage(buttonbg);
	exit->setImage(buttonbg);

	newgame->setVisible(0);
	load->setVisible(0);
	options->setVisible(0);
	exit->setVisible(0);
	player.setCoordinates(300, 300);
	receiver.set(context);
	device->setEventReceiver(&receiver);
	return 0;
}

int GE::start()
{
	while (device->run())
	{

		now = device->getTimer()->getTime();
		if (now - sceneStartTime > sceneSkipTime)
		{

			sceneStartTime = device->getTimer()->getTime();
			{
				core::stringw str(L"FPS: ");
				str.append(core::stringw(driver->getFPS()));

				events.endEventProcess();
				driver->beginScene(true, true, SColor(255, 255, 255, 255));
				if (draw == MAINMENU)
				{
					driver->draw2DImage(menubg, rect<s32>(0, 0, screenSize.Width, screenSize.Height), rect<s32>(0, 0, 400, 240));

					newgame->setVisible(1);
					load->setVisible(1);
					options->setVisible(1);
					exit->setVisible(1);

					guienv->drawAll();
					fpstext->setText(str.c_str());

					if (receiver.clicked == 2)
					{
						//-----core->map----//
						tilemap = gameMap.Generate(DEBUG_GEN_HEIGHT, DEBUG_GEN_WIDTH, 100, rand(), 10, 10);

						driver->makeColorKeyTexture(tileAtlas, SColor(255, 255, 255, 255));

						//---gui->minimap---//
						stringc name = L"minimap";
						miniMap = driver->addTexture(name.c_str(), gameMap.MiniMapGen(driver, DEBUG_GEN_WIDTH, DEBUG_GEN_HEIGHT));

						draw = GAME;
						device->setEventReceiver(&events);
						newgame->setVisible(0);
						load->setVisible(0);
						options->setVisible(0);
						exit->setVisible(0);
					}
					if (receiver.clicked == 3)
					{

					}

				}
				else
				{
					//--core->mainloop->prep--//
					if (events.keyPressed(KEY_KEY_M))
					{
						if (draw == MAP) draw = GAME;
						else draw = MAP;

					}
					if (events.keyPressed(KEY_KEY_O))
						draw = OPTIONS;
					if (events.keyPressed(KEY_ESCAPE))
						draw = GAME;
					if (draw == GAME)
					{
						//movement events
						if (events.keyDown(KEY_KEY_S))
						{
							if (player.getCoordinatesX() < DEBUG_GEN_HEIGHT - screenTileSize.Height)
							{
								player.setCoordinates(player.getCoordinatesX() + player.GetMovespeed(), player.getCoordinatesY());
							}

						}
						if (events.keyDown(KEY_KEY_W))
						{
							if (player.getCoordinatesX() > screenTileSize.Height)
							{
								player.setCoordinates(player.getCoordinatesX() - player.GetMovespeed(), player.getCoordinatesY());
							}
						}
						if (events.keyDown(KEY_KEY_D))
						{
							if (player.getCoordinatesY() < DEBUG_GEN_WIDTH - screenTileSize.Width)
							{
								player.setCoordinates(player.getCoordinatesX(), player.getCoordinatesY() + player.GetMovespeed());
							}
						}
						if (events.keyDown(KEY_KEY_A))
						{
							if (player.getCoordinatesY() > screenTileSize.Width)
							{
								player.setCoordinates(player.getCoordinatesX(), player.getCoordinatesY() - player.GetMovespeed());
							}
						}

						//clear batch
						destinationBatch.clear();
						sourceBatch.clear();

						//fill up batch with visible area
						int i = 0, j = 0;
						for (int h = player.getCoordinatesX() - screenTileSize.Height / 2; h <= screenTileSize.Height / 2 + player.getCoordinatesX(); h++)
						{
							for (int w = player.getCoordinatesY() - screenTileSize.Width / 2; w <= screenTileSize.Width / 2 + player.getCoordinatesY(); w++)
							{

								int posH = tilemap[h][w] / 12;
								int posW = tilemap[h][w] % 12;

								destinationBatch.push_back(vector2d<s32>(TILESIZE * i, TILESIZE * j));
								sourceBatch.push_back(rect<s32>(posW * TILESIZE, posH * TILESIZE, (posW + 1) * TILESIZE, (posH + 1) * TILESIZE));
								i++;
							}
							j++;
							i = 0;
						}

						//draw player (placeholder)
						destinationBatch.push_back(position2d<s32>(screenSize.Width / 2, screenSize.Height / 2));
						sourceBatch.push_back(rect<s32>(11 * TILESIZE, 0, 12 * TILESIZE, TILESIZE));
					}
					switch (draw)
					{
					case GAME:
						//draw batch
						driver->draw2DImageBatch(tileAtlas, destinationBatch, sourceBatch, 0, SColor(255, 255, 255, 255), true);
						str.append("\nx:");
						str.append(core::stringw(player.getCoordinatesX()));
						str.append("\ny:");
						str.append(core::stringw(player.getCoordinatesY()));
						fpstext->setText(str.c_str());
						guienv->drawAll();
						break;
					case MAP:
						//draw map
						driver->draw2DImage(miniMap, rect<s32>(0, 0, screenSize.Width, screenSize.Height), rect<s32>(0, 0, DEBUG_GEN_HEIGHT, DEBUG_GEN_WIDTH));
						str.append("\nx:");
						str.append(core::stringw(player.getCoordinatesX()));
						str.append("\ny:");
						str.append(core::stringw(player.getCoordinatesY()));
						fpstext->setText(str.c_str());
						guienv->drawAll();
						break;
					case OPTIONS:
						break;
					case PAUSEMENU:
						break;
					case CHARACTER:
						break;
					case START:
						break;
					default:
						draw = GAME;
						break;
					}
				}
				driver->endScene();
				events.startEventProcess();
			}
		}
	}
	//--core->destroy--//

	return 0;
}

int GE::drop()
{
	device->drop();
	return 0;
}

SIrrlichtCreationParameters GE::setParams(int driverType, int width, int height, int bits, bool vsync, bool fullscreen, bool antiAlias)
{
	params.DriverType = static_cast<E_DRIVER_TYPE>(driverType);
	params.WindowSize.Width = width;
	params.WindowSize.Height = height;
	params.Bits = bits;
	params.Vsync = vsync;
	params.Fullscreen = fullscreen;
	params.AntiAlias = antiAlias;
	params.EventReceiver = &events;

	return params;
}

IrrlichtDevice * GE::getDevice()
{
	return device;
}

IVideoDriver*		GE::getDriver()
{
	return driver;
}

IGUIEnvironment * GE::getGuienv() 
{
	return guienv;
}

IGUISkin * GE::getSkin() 
{
	return skin;
}

IGUIFont * GE::getFont() 
{
	return font;
}

IGUIStaticText * GE::getFpstext() 
{
	return fpstext;
}

ITexture * GE::getMiniMap() 
{
	return miniMap;
}

ITexture * GE::getTileAtlas() 
{
	return tileAtlas;
}

ITexture * GE::getMenubg() 
{
	return menubg;
}

ITexture * GE::getButtonbg()
{
	return buttonbg;
}

int ** GE::getTilemap()
{
	return tilemap;
}

Settings GE::getSettings()
{
	return settings;
}

MapGen GE::getGameMap()
{
	return gameMap;
}

TileManager GE::getTm()
{
	return tm;
}

EventsHolder GE::getEvents()
{
	return events;
}

dimension2d<u32> GE::getScreenSize()
{
	return screenSize;
}

dimension2d<s32> GE::getScreenTileSize()
{
	return screenTileSize;
}
