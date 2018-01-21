#pragma once
#include <irrlicht.h>
#include <iostream>
#include "Settings.h"
#include "MapGen.h"
#include "TileManager.h"
#include "EventsHolder.h"
#include "Character.h"
#include "Player.h"
#include "MainMenu.h"
#include "GE.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class GE
{
private:

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


	//-------- POINTERS ----------//
	IrrlichtDevice*					device;
	IVideoDriver*					driver;
	IGUIEnvironment*				guienv;
	IGUISkin*						skin;
	IGUIFont*						font;
	IGUIStaticText*					fpstext;
	ITexture*						miniMap;
	ITexture*						tileAtlas;
	ITexture*						menubg;
	ITexture*						buttonbg;
	int **							tilemap;
	Settings						settings;
	MapGen							gameMap;
	TileManager						tm;
	EventsHolder					events;
	SIrrlichtCreationParameters		params;
	Player							player;
	core::array<position2d<s32>>	destinationBatch;
	core::array<rect<s32>>			sourceBatch;
	enum							GUIElement { GAME, MAP, OPTIONS, MAINMENU, PAUSEMENU, CHARACTER, START };
	int								draw = MAINMENU;
	SAppContext						context;
	IGUIButton						*newgame, *load, *options, *exit;
	MyEventReceiver					receiver;
public:
	GE();
	~GE();

	int init();
	int start();
	int drop();
	//--------- SETS -------------//
	SIrrlichtCreationParameters setParams(
		int driverType = 5,
		int width = 1024,
		int height = 720,
		int bits = 32,
		bool vsync = 0,
		bool fullscreen = 0,
		bool antiAlias = 0
	);


	//-------- RETURNS -----------//
	IrrlichtDevice*		getDevice();
	IVideoDriver*		getDriver();
	IGUIEnvironment*	getGuienv();
	IGUISkin*			getSkin();
	IGUIFont*			getFont();
	IGUIStaticText*		getFpstext();
	ITexture*			getMiniMap();
	ITexture*			getTileAtlas();
	ITexture*			getMenubg();
	ITexture*			getButtonbg();
	int **				getTilemap();
	Settings			getSettings();
	MapGen				getGameMap();
	TileManager			getTm();
	EventsHolder		getEvents();
	dimension2d<u32>	getScreenSize();
	dimension2d<s32>	getScreenTileSize();
};

