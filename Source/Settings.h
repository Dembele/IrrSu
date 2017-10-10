#pragma once
class Settings
{
public:
	Settings();
	~Settings();
	int load();
	int save();

	//добавить функции и запихнуть переменные в приват
	int driverType=5;
	struct ScreenSet
	{
		int width=1024;
		int height=720;
	}screen;
	int bits=32;
	bool vsync=0;
	bool fullscreen=0;
	bool antiAlias=0;
};

