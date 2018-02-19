#include "MapGen.h"
#include "PN.h" //perlin noise


//need fix for single tile

int ** MapGen::Generate(int height, int width, int radius, unsigned int seed, double ax, double ay, double e)
{
	
	enum {AIR, STONE, SAND, GRASS, FOREST, LAST };
	int prev = -1, now = 0;

	tileMap = new int*[height];
	for (int w=0; w<width; w++)
		tileMap[w] = new int[width];

	for (int w=0; w<width; w++)
		for (int h = 0; h < height; h++)
			tileMap[w][h] = AIR;



	/*
	if (!mapCreated)
	{
		PN heightmap(seed);
		tileMap = new int*[height];
		tileMap2 = new int*[height];
		for (int w = 0; w < width; w++)
		{
			tileMap[w] = new int[width];
			tileMap2[w] = new int[width];
		}
		double tilemask = 0, n = 0;
		radius = (height + width) / 2.3;
		for (int h = 0; h < height; ++h)
		{
			for (int w = 0; w < width; ++w)
			{
				tileMap2[h][w] = WATER;
				double res = (h - height / 2)*(h - height / 2) + (w - width / 2)*(w - width / 2);
				if (res <= radius*radius)
				{
					tilemask = res / double(radius*radius) * 2;
					double x = (double)w / ((double)(width));
					double y = (double)h / ((double)(height));
					n = heightmap.PNoise(x*ax, y*ay, e);
					n -= tilemask;
				}
				else n = -1;

				if (n <= 0.2) tileMap[h][w] = WATER;
				if (n > 0.2 && n <= 0.3) tileMap[h][w] = SAND;
				if (n > 0.3 && n <= 0.5) tileMap[h][w] = GRASS;
				if (n > 0.5 && n <= 0.7) tileMap[h][w] = FOREST;
				if (n > 0.7) tileMap[h][w] = STONE;
			}
		}
		//check for bullshit tiles and replacement
		for (int i = 1; i < LAST; i++)
			for (int h = 1; h < height - 1; ++h)
				for (int w = 1; w < width - 1; ++w)
				{
					if (tileMap[h - 1][w - 1] != i && tileMap[h - 1][w] != i && tileMap[h - 1][w + 1] != i && tileMap[h][w - 1] != i && tileMap[h][w] == i && tileMap[h][w + 1] != i && tileMap[h + 1][w - 1] == i && tileMap[h + 1][w] == i && tileMap[h + 1][w + 1] == i)
						tileMap[h][w] = i - 1;
				}
				
		for (int i = 4; i < 7; i++)
			for (int j = 4; j < 7; j++)
				tileMap[i][j] = SAND;
		for (int i = 4; i < 7; i++)
			for (int j = 7; j < 10; j++)
				tileMap[i][j] = GRASS;
		for (int i = 1; i < LAST; i++)
			for (int h = 1; h < height - 1; h++)
				for (int w = 1; w < width - 1; w++)
				{

					if (tileMap[h][w] == i)
					{
						//topleft
						if (tileMap[h + 1][w] == i && tileMap[h][w + 1] == i && tileMap[h][w - 1] == i - 1 && tileMap[h - 1][w] == i - 1)
						{
							tileMap2[h][w] = i * 12;
							continue;
						}
						//top
						if (tileMap[h + 1][w] == i && tileMap[h][w + 1] == i && tileMap[h][w - 1] == i && tileMap[h - 1][w] == i - 1)
						{
							tileMap2[h][w] = i * 12 + 1;
							continue;
						}
						//topright
						if (tileMap[h + 1][w] == i && tileMap[h][w + 1] == i - 1 && tileMap[h][w - 1] == i && tileMap[h - 1][w] == i - 1)
						{
							tileMap2[h][w] = i * 12 + 2;
							continue;
						}
						//left
						if (tileMap[h + 1][w] == i && tileMap[h][w + 1] == i && tileMap[h][w - 1] == i - 1 && tileMap[h - 1][w] == i)
						{
							tileMap2[h][w] = i * 12 + 3;
							continue;
						}
						//right
						if (tileMap[h + 1][w] == i && tileMap[h][w + 1] == i - 1 && tileMap[h][w - 1] == i && tileMap[h - 1][w] == i)
						{
							tileMap2[h][w] = i * 12 + 4;
							continue;
						}
						//bottomleft
						if (tileMap[h + 1][w] == i - 1 && tileMap[h][w + 1] == i && tileMap[h][w - 1] == i - 1 && tileMap[h - 1][w] == i)
						{
							tileMap2[h][w] = i * 12 + 5;
							continue;
						}
						//bottom
						if (tileMap[h + 1][w] == i - 1 && tileMap[h][w + 1] == i && tileMap[h][w - 1] == i && tileMap[h - 1][w] == i)
						{
							tileMap2[h][w] = i * 12 + 6;
							continue;
						}
						//bottomright
						if (tileMap[h + 1][w] == i - 1 && tileMap[h][w + 1] == i - 1 && tileMap[h][w - 1] == i && tileMap[h - 1][w] == i)
						{
							tileMap2[h][w] = i * 12 + 7;
							continue;
						}
						//innerBottomright
						if (tileMap[h + 1][w] == i && tileMap[h][w + 1] == i && tileMap[h][w - 1] == i && tileMap[h - 1][w] == i && tileMap[h + 1][w + 1] == i - 1)
						{
							tileMap2[h][w] = i * 12 + 8;
							continue;
						}
						//innerBottomleft
						if (tileMap[h + 1][w] == i && tileMap[h][w + 1] == i && tileMap[h][w - 1] == i && tileMap[h - 1][w] == i && tileMap[h + 1][w - 1] == i - 1)
						{
							tileMap2[h][w] = i * 12 + 9;
							continue;
						}
						//innerTopright
						if (tileMap[h + 1][w] == i && tileMap[h][w + 1] == i && tileMap[h][w - 1] == i && tileMap[h - 1][w] == i && tileMap[h - 1][w + 1] == i - 1)
						{
							tileMap2[h][w] = i * 12 + 10;
							continue;
						}

						//innerTopleft
						if (tileMap[h + 1][w] == i && tileMap[h][w + 1] == i && tileMap[h][w - 1] == i && tileMap[h - 1][w] == i && tileMap[h - 1][w - 1] == i - 1)
						{
							tileMap2[h][w] = i * 12 + 11;
							continue;
						}
						//center
						//if (tileMap[h + 1][w] == i && tileMap[h][w + 1] == i && tileMap[h][w - 1] == i && tileMap[h - 1][w] == i)
						//{
						tileMap2[h][w] = tileMap[h][w];


					}

				}
		tileMap2[2][1] = 1;
		tileMap2[1][2] = 2;
		tileMap2[3][2] = 3;
		tileMap2[2][3] = 4;
	}
	*/
	
	

	return tileMap;
}

irr::video::IImage* MapGen::MiniMapGen(irr::video::IVideoDriver * p, int width, int height)
{
	if (!miniMapCreated)
	{
		irr::video::SColor color;
		miniMap = p->createImage(irr::video::ECF_A8R8G8B8, irr::core::dimension2d<irr::u32>(width, height));
		for (int h = 0; h < height; h++)
		{
			for (int w = 0; w < width; w++)
			{
				switch (tileMap[h][w])
				{
				case 0: color.set(255, 0, 30, 140);
					break;
				case 1: color.set(255, 195, 201, 12);
					break;
				case 2: color.set(255, 40, 142, 17);
					break;
				case 3: color.set(255, 10, 58, 0);
					break;
				case 4: color.set(255, 191, 191, 191);
					break;
				default:
					break;
				}
				miniMap->setPixel(h, w, color);
			}
		}
	}
	return miniMap;
}


MapGen::~MapGen()
{
	delete[] tileMap;
}