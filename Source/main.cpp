//TODO: mapGen -> more uncomon generation and remap ids
#include <irrlicht.h>
#include "GE.h"

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#endif


int main() {
	GE game;
	game.init();
	game.start();
	game.drop();
}