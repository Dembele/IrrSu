/*
7/31/08
TileManager.h
Dan Bush
*/

#ifndef TILE_MANAGER_H
#define TILE_MANAGER_H

#include <irrlicht.h>
#include <string>
#include <vector>

using namespace irr;
using namespace video;
using namespace std;

// structure that stores the images and tile information
//for each texture we load
struct sTileSet
{
	ITexture * texture;
	unsigned short width;
	unsigned short height;
	unsigned short collumns;
};


class TileManager
{
private:

	vector<sTileSet> tSet;

public:
	TileManager();
	~TileManager();

	bool load(IVideoDriver * p, char * s, const unsigned short w, const unsigned short h, const unsigned short c, SColor key);
	bool free();
	bool draw(IVideoDriver * pDriver, const unsigned short texNum, const unsigned short tileNum, const short x, const short y, irr::core::rect<s32> * r = 0);

	short getNumTileSets();
	sTileSet getTileSetAt(const unsigned short i);
};


#endif