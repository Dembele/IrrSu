/*
8/11/08
cTileMap.h
Dan Bush
*/

#include "cTileMap.h"
#include <fstream>

using namespace irr;
using namespace video;
using namespace std;
using namespace core;


//cTileMap()
//initializes everything to arbitrary values
//you probably want to set your own values using setNodeDimensions()... etc..
cTileMap::cTileMap()
{
	map = NULL;
	freeNodes();
	setNodeDimensions(32, 32);
	setViewPortDimensions(320, 320);
	maxNodeX = 0;
	maxNodeY = 0;
	cameraX = 0;
	cameraY = 0;
}

//~cTileMap()
//calls freeNodes()
cTileMap::~cTileMap()
{
	freeNodes();
}

//freeNodes
//not much to say about this
bool cTileMap::freeNodes()
{
	nodes.clear();
	return true;
}


//draw()
//draws the map to the screen at given positions using the camera viewport
bool cTileMap::draw(IVideoDriver * driver, const short drawX, const short drawY)
{
	//translate from fine coordinates to tile coordinates
	unsigned int startY = cameraY / nodeHeight;
	unsigned int endY = (cameraY + viewPortWidth) / nodeHeight;

	unsigned int startX = cameraX / nodeWidth;
	unsigned int endX = (cameraX + viewPortHeight) / nodeWidth;

	//shift the tiles over because we want to have per pixel scrolling
	unsigned int shiftY = cameraY % nodeHeight;
	unsigned int shiftX = cameraX % nodeWidth;

	//finally draw the tiles using the above calculations
	for (unsigned int y = 0; y <= (endY - startY); y++)
	{
		for (unsigned int x = 0; x <= (endX - startX); x++)
		{
			if ((startX + x) > nodes.size() - 1)   //this shouldnt happen ever due to our camera, but just in case
				break;
			if ((startY + y) > nodes[startX + x].size() - 1)//this shouldnt happen ever due to our camera, but just in case
				break;

			nodes[startX + x][startY + y].draw(driver, &manager, drawX + ((x * nodeWidth) - shiftX), drawY + ((y * nodeHeight) - shiftY), &rect<s32>(drawX, drawY, drawX + viewPortWidth, drawY + viewPortHeight));
		}
	}
	return true;
}

//load()
//not yet implemented
bool cTileMap::load(IVideoDriver * driver, const std::string s)
{
	freeNodes();
	ifstream f(s.c_str(), ios::binary);


	//read the header information
	sMapHeader h;
	f.read((char *)&h, sizeof(h));
	createNodes(h.width, h.height);
	setNodeDimensions(h.nWidth, h.nHeight);

	// READ THE TILEMANAGER INFORMATION
	short sets;
	f.read((char *)&sets, sizeof(short));

	for (int q = 0; q < sets; q++)
	{
		char name[30];
		f.read(name, sizeof(char) * 30);
		unsigned short w;
		f.read((char *)&w, sizeof(unsigned short));
		unsigned short h;
		f.read((char *)&h, sizeof(unsigned short));
		unsigned short col;
		f.read((char *)&col, sizeof(unsigned short));

		manager.load(driver, name, w, h, col, SColor((255, 255, 0, 255)));

	}

	for (int y = 0; y < h.height; y++)
	{
		for (int x = 0; x < h.width; x++)
		{
			unsigned char c;
			unsigned short num;
			sTile t(0, 0);
			f.read((char *)&c, sizeof(unsigned char));
			f.read((char *)&num, sizeof(unsigned short));
			for (int i = 0; i < num; i++)
			{
				f.read((char *)&t, sizeof(sTile));
				addTile(t, x, y);
			}
		}
	}

	f.close();


	return true;
}

//save()
//not yet implemented
bool cTileMap::save(const std::string s)
{
	ofstream f(s.c_str(), ios::binary | ios::trunc);


	// SAVE THE MAP HEADER
	sMapHeader h;
	h.width = maxNodeX;
	h.height = maxNodeY;
	h.nWidth = nodeWidth;
	h.nHeight = nodeHeight;

	f.write((char *)&h, sizeof(h));


	// SAVE THE TILEMANAGER INFORMATION
	short sets = manager.getNumTileSets();
	f.write((char *)&sets, sizeof(short));

	for (int q = 0; q < sets; q++)
	{
		sTileSet t = manager.getTileSetAt(q);
		//int s = sizeof(t.texture->getName().operator irr::core::stringc);
		char name[30];
		//strcpy_s(name, t.texture->getName().operator irr::core::stringc);
		f.write(name, sizeof(char) * 30);
		f.write((char *)&t.width, sizeof(unsigned short));
		f.write((char *)&t.height, sizeof(unsigned short));
		f.write((char *)&t.collumns, sizeof(unsigned short));
	}


	// SAVE THE NODES

	for (int y = 0; y < h.height; y++)
	{
		for (int x = 0; x < h.width; x++)
		{
			unsigned char c = nodes[x][y].getFlags();
			unsigned short num = nodes[x][y].getNumTiles();
			f.write((char *)&c, sizeof(unsigned char));
			f.write((char *)&num, sizeof(unsigned short));
			for (int i = 0; i < num; i++)
				f.write((char *)&nodes[x][y].getTileAt(i), sizeof(sTile));
		}
	}

	f.close();


	return true;
}

//setNodeDimensions()
//self explanatory
bool cTileMap::setNodeDimensions(const unsigned short w, const  unsigned short h)
{
	if (w == 0 || h == 0)
		return false;

	nodeWidth = w;
	nodeHeight = h;
	return true;
}

//createNodes()
//self explanatory
bool cTileMap::createNodes(const unsigned short x, const unsigned y)
{
	freeNodes();
	vector<cTileMapNode> v(y);

	for (int i = 0; i < x; i++)
		nodes.push_back(v);

	maxNodeX = x;
	maxNodeY = y;

	return true;
}


//setViewPortDimensions()
//self explanatory
bool cTileMap::setViewPortDimensions(const unsigned short w, const unsigned short h)
{
	if (w <= 0 || h <= 0)
		return false;

	viewPortWidth = w;
	viewPortHeight = h;
	return true;
}



//getNodes()
//self explanatory
vector<vector<cTileMapNode>> * cTileMap::getNodes()
{
	return &nodes;
}

//getNodes()
//self explanatory
TileManager * cTileMap::getTileManager()
{
	return &manager;
}

//addTile()
//adds a tile to node[x][y]
bool cTileMap::addTile(sTile t, unsigned int nodeX, unsigned int nodeY)
{
	if (nodeX > nodes.size())
		return false;

	if (nodeY > nodes[nodeX].size())
		return false;
	nodes[nodeX][nodeY].addTile(t);

	return true;
}


//setCamera()
//positions the camera upper left coordinate at x,y, this location can be
//outside the map, the camera will automatically shift over to the map boundary
bool cTileMap::setCamera(const short x, const short y)
{
	if (x < 0)
		cameraX = 0;
	else if (x >((maxNodeX * nodeWidth) - viewPortWidth))
		cameraX = ((maxNodeX * nodeWidth) - viewPortWidth);
	else
		cameraX = x;

	if (y < 0)
		cameraY = 0;
	else if (y >((maxNodeY * nodeHeight) - viewPortHeight))
		cameraY = ((maxNodeY * nodeHeight) - viewPortHeight);
	else
		cameraY = y;

	return true;
}

//getCameraX()
//self explanatory
unsigned short cTileMap::getCameraX()
{
	return cameraX;
}

//getCameraY()
//self explanatory
unsigned short cTileMap::getCameraY()
{
	return cameraY;
}