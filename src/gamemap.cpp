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

void GameMap::SetCell(int x, int y, eCellType tp)
{
	data[x + y * width].type = tp;
}




//int celdax = (posx - map_origin.x) / cellsize;