#pragma once
#include <irrlicht.h>
class MapGen
{
public:
	//! generates a map of tiles depending on params.
	/* 
	height - height - number of tiles in height. 
	width - number of tiles in width
	startX (h), startY (w) - положение на карте
	seed - seed for random in perlin noise
	ax & ay & e - how smooth the noise is (amplitude) by x, y, z coordinates (e unused)
	*/
	int ** Generate(int height, int width, int radius, unsigned int seed = 1, double ax = 10, double ay = 10, double e = 0);
	int SaveChunk();
	irr::video::IImage* MiniMapGen(irr::video::IVideoDriver* p, int w, int h);
	//! delete[] tileMap;
	~MapGen();
private:
	irr::video::IImage* miniMap;
	int ** tileMap;
	int ** tileMap2;
	bool mapCreated = false;
	bool miniMapCreated = false;
};

