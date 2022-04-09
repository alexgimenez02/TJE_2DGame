#include "gamemap.h"

GameMap::GameMap() {
	width = height = 0;
	data = NULL;
}

GameMap::GameMap(int w, int h)
{
	width = w;
	height = h;
	data = new sCell[w * h];
}

sCell& GameMap::getCell(int x, int y)
{
	return data[x + y * width];
}

//int celdax = (posx - map_origin.x) / cellsize;