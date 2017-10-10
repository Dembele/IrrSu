//TODO: mapGen -> more uncomon generation and remap ids
#define VERSION L"0.02"
#define DEBUG_GEN_WIDTH 1000
#define DEBUG_GEN_HEIGHT 1000
#define TILESIZE 64
#define BUTTON_HEIGHT 60
#define BUTTON_WIDTH 200

#include <irrlicht.h>
#include <iostream>
#include "Settings.h"
#include "MapGen.h"
#include "TileManager.h"
#include "EventsHolder.h"
#include "Character.h"
#include "Player.h"
#include "MainMenu.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#endif

//-----------GUI TEST------------------//


//----------GLOBAL POINTERS------------//
IrrlichtDevice *device;
IVideoDriver* driver;
IGUIEnvironment* guienv;
IGUISkin* skin;
IGUIFont* font;
IGUIStaticText* fpstext;
ITexture* miniMap;
ITexture* tileAtlas;
ITexture* menubg;
ITexture* buttonbg;
int ** tilemap;
Settings settings;
MapGen GameMap;
TileManager tm;
EventsHolder events;

//----------SOME VARS------------------//
dimension2d<u32> screenSize;
dimension2d<s32> screenTileSize;

s32 time;

// Переменные для фиксации FPS { 
s32 framelimit = 60, //FPS 
now = 0;
u32 sceneStartTime = 0,
sceneSkipTime = 1000 / framelimit;
//} Переменные для фиксации FPS

int main() {
	//-----classes------//
	events.init();

	//-----device-------//
	SIrrlichtCreationParameters params;
	params.AntiAlias = settings.antiAlias;
	params.Bits = settings.bits;
	params.DriverType = static_cast<E_DRIVER_TYPE>(settings.driverType);
	params.Fullscreen = settings.fullscreen;
	params.Vsync = settings.vsync;
	params.WindowSize = dimension2d<u32>(settings.screen.width, settings.screen.height);
	params.EventReceiver = &events;
	device = createDeviceEx(params);
	if (!device) return 1;
	device->setWindowCaption(L"IrrSu ver" VERSION);
	device->maximizeWindow();

	//------driver------//
	driver = device->getVideoDriver();
	screenSize = driver->getScreenSize();
	tileAtlas = driver->getTexture("Media/images/tileset.png");
	menubg = driver->getTexture("Media/images/menubg.jpg");

	//-------gui--------//
	guienv = device->getGUIEnvironment();
	skin = guienv->getSkin();
	font = guienv->getFont("Media/fonts/myfont.xml");
	if (font)
		skin->setFont(font);
	fpstext = guienv->addStaticText(L"",
		core::rect<s32>(4, 4, settings.screen.width / 8, 400), false, true);
	buttonbg = driver->getTexture("Media/images/button.png");


	//-------DEBUG------//
	enum GUIElement { GAME, MAP, OPTIONS, MAINMENU, PAUSEMENU, CHARACTER, START };
	int draw = 3;
	Player player;
	screenTileSize.Height = screenSize.Height / TILESIZE + 1;
	screenTileSize.Width = screenSize.Width / TILESIZE + 1; 
	double x, y;

	core::array<position2d<s32>> destinationBatch;
	core::array<rect<s32>> sourceBatch;

	SAppContext context;
	context.device = device;
	context.counter = 0;


	IGUIButton* newgame = guienv->addButton(rect<s32>(screenSize.Width / 2 - BUTTON_WIDTH / 2,
		screenSize.Height / 2 - 3 * (BUTTON_HEIGHT),
		screenSize.Width / 2 + BUTTON_WIDTH / 2,
		screenSize.Height / 2 - 2 * BUTTON_HEIGHT),
		0, B_NEWGAME, L"NEW GAME");
	IGUIButton* load = guienv->addButton(rect<s32>(screenSize.Width / 2 - BUTTON_WIDTH / 2,
		screenSize.Height / 2 - 2 * (BUTTON_HEIGHT),
		screenSize.Width / 2 + BUTTON_WIDTH / 2,
		screenSize.Height / 2 - BUTTON_HEIGHT),
		0, B_LOAD, L"LOAD");
	IGUIButton* options = guienv->addButton(rect<s32>(screenSize.Width / 2 - BUTTON_WIDTH / 2,
		screenSize.Height / 2,
		screenSize.Width / 2 + BUTTON_WIDTH / 2,
		screenSize.Height / 2 + BUTTON_HEIGHT),
		0, B_OPTIONS, L"OPTIONS");
	IGUIButton* exit = guienv->addButton(rect<s32>(screenSize.Width / 2 - BUTTON_WIDTH / 2,
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
	MyEventReceiver receiver(context);

	// And tell the device to use our custom event receiver.
	device->setEventReceiver(&receiver);

	//--core->mainloop--//
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
					driver->draw2DImage(menubg, vector2d<s32>(0, 0));

					newgame->setVisible(1);
					load->setVisible(1);
					options->setVisible(1);
					exit->setVisible(1);

					guienv->drawAll();
					fpstext->setText(str.c_str());

					if (receiver.clicked == 2)
					{
						//-----core->map----//
						tilemap = GameMap.Generate(DEBUG_GEN_HEIGHT, DEBUG_GEN_WIDTH, 100, rand(), 10, 10);

						driver->makeColorKeyTexture(tileAtlas, SColor(255, 255, 255, 255));

						//---gui->minimap---//
						stringc name = L"minimap";
						miniMap = driver->addTexture(name.c_str(), GameMap.MiniMapGen(driver, DEBUG_GEN_WIDTH, DEBUG_GEN_HEIGHT));

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
					x = player.getCoordinatesX();
					y = player.getCoordinatesY();

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

						if (events.keyDown(KEY_KEY_S))
						{
							if (player.getCoordinatesX() < DEBUG_GEN_HEIGHT - screenTileSize.Height)
							{
								x += player.GetMovespeed();
								player.setCoordinates(x, y);
							}

						}
						if (events.keyDown(KEY_KEY_W))
						{
							if (player.getCoordinatesX() > 0)
							{
								x -= player.GetMovespeed();
								player.setCoordinates(x, y);
							}
						}
						if (events.keyDown(KEY_KEY_D))
						{
							if (player.getCoordinatesY() < DEBUG_GEN_WIDTH - screenTileSize.Width)
							{
								y += player.GetMovespeed();
								player.setCoordinates(x, y);
							}
						}
						if (events.keyDown(KEY_KEY_A))
						{
							if (player.getCoordinatesY() > 0)
							{
								y -= player.GetMovespeed();
								player.setCoordinates(x, y);
							}
						}
						destinationBatch.clear();
						sourceBatch.clear();
						int i = 0, j = 0;
						for (int h = player.getCoordinatesX() - screenTileSize.Height/2; h <= screenTileSize.Height/2 + player.getCoordinatesX(); h++)
						{
							for (int w = player.getCoordinatesY()- screenTileSize.Width / 2; w <= screenTileSize.Width/2 + player.getCoordinatesY(); w++)
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
						destinationBatch.push_back(position2d<s32>(screenSize.Width / 2, screenSize.Height / 2));
						sourceBatch.push_back(rect<s32>(7 * TILESIZE, 0, 8 * TILESIZE, TILESIZE));
					}
					switch (draw)
					{
					case GAME:
						driver->draw2DImageBatch(tileAtlas, destinationBatch, sourceBatch, 0, SColor(255, 255, 255, 255), true);
						str.append("\nx:");
						str.append(core::stringw(x));
						str.append("\ny:");
						str.append(core::stringw(y));
						fpstext->setText(str.c_str());
						guienv->drawAll();
						break;
					case MAP:
						driver->draw2DImage(miniMap, rect<s32>(0, 0, screenSize.Width, screenSize.Height), rect<s32>(0, 0, DEBUG_GEN_HEIGHT, DEBUG_GEN_WIDTH));
						str.append("\nx:");
						str.append(core::stringw(x));
						str.append("\ny:");
						str.append(core::stringw(y));
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
	device->drop();
	return 0;
}