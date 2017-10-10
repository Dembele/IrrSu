#pragma once
#include <irrlicht.h>

using namespace irr;
using namespace video;
using namespace std;

class tileDrawer
{
private:
	int ** tilemap;
	ITexture * texture;

public:
	ITexture * convert(int ** tilemap, ITexture * tileatlas, int height, int width, int columns);
	tileDrawer();
	~tileDrawer();
};

