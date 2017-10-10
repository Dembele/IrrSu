#include "Settings.h"
#include <fstream>
#include <iomanip>
#include <string>
#include <iostream>

Settings::Settings()
{
	load();
}


Settings::~Settings()
{
	save();
}


int Settings::load()
{
	std::ifstream fin("settings.ini");
	fin >> driverType;
	fin >> screen.width;
	fin >> screen.height;
	fin >> bits;
	fin >> vsync;
	fin >> fullscreen;
	fin >> antiAlias;

	std::cout <<"driver type: "<< driverType << "\nscreen: " << screen.width << "x" << screen.height << "\nbits: " << bits << "\nvsync: " << vsync << "\nfullscreen: " << fullscreen << "\nantiAlias: " << antiAlias << std::endl;


	return 0;
}

int Settings::save()
{
	std::ofstream fout("settings.ini");

	/*
	fout << "#the width of the screen \n";
	fout << std::left << std::setw(25) << "screen->width: " << screen.width << "\n\n";
	fout << "#the height of the screen \n";
	fout << std::left << std::setw(25) << "screen->height: " << screen.height << "\n\n";
	fout << "#the bits of the screen \n";
	fout << std::left << std::setw(25) << "bits: " << bits << "\n\n";
	fout << "#vertical sync of the screen \n";
	fout << std::left << std::setw(25) << "vsync: " << vsync << "\n\n";
	fout << "#fullscreen? \n";
	fout << std::left << std::setw(25) << "fullscreen: " << fullscreen << "\n\n";
	fout << "#antiAlising \n";
	fout << std::left << std::setw(25) << "antiAlias: " << antiAlias << "\n\n";
	fout << "#yes, i know that i should rewrite it later \n";
	*/

	fout << driverType << "\n" << screen.width << "\n" << screen.height << "\n" << bits << "\n" << vsync << "\n" << fullscreen << "\n" << antiAlias;

	return 0;
}

