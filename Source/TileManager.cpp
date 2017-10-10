/*
7/31/08
TileManager.cpp
Dan Bush
*/

#include "TileManager.h"
#include <string>
#include <iostream>
#include <vector>

using namespace irr;
using namespace video;
using namespace std;
using namespace core;

//TileManager()
TileManager::TileManager()
{

	free();

}

//~TileManager()
TileManager::~TileManager()
{
	free();
}

//load()
//loads a tileset given a texture, the width and hieght of the tiles, the number of collumns
//and the transparent color key
bool TileManager::load(IVideoDriver * p, char * s, const unsigned short w, const unsigned short h, const unsigned short c, SColor key)
{
	sTileSet set;

	set.texture = p->getTexture(s);
	set.width = w;
	set.height = h;
	set.collumns = c;
	tSet.push_back(set);


	p->makeColorKeyTexture(tSet[tSet.size() - 1].texture, key);


	return true;
}

//free()
bool TileManager::free()
{
	//dealloc the vector
	tSet.clear();
	return true;
}



//draw()
//draws a tile at x, y
//you probably wont call this directly very often (unless maybe you're writing an editor)
bool TileManager::draw(IVideoDriver * pDriver, const unsigned short texNum, const unsigned short tileNum, const short x, const short y, irr::core::rect<s32> * r)
{

	// get the source coordinates
	int sx = (tileNum % tSet.at(texNum).collumns) * tSet.at(texNum).width;
	int sy = (tileNum / tSet.at(texNum).collumns) * tSet.at(texNum).height;


	pDriver->draw2DImage(tSet.at(texNum).texture, position2d<s32>(x, y), rect<s32>(sx, sy, sx + tSet.at(texNum).width, sy + tSet.at(texNum).height),
		r, SColor(255, 255, 255, 255), true);

	return true;
}

//getNumTileSets()
short TileManager::getNumTileSets()
{
	return tSet.size();
}

//getTileSetAt()
sTileSet TileManager::getTileSetAt(const unsigned short i)
{
	if (i >= tSet.size())
		return tSet[tSet.size() - 1];

	else
		return tSet[i];
}