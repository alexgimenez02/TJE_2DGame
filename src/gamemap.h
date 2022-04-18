#ifndef GAMEMAP_H
#define GAMEMAP_H
#include "includes.h"

enum eCellType {
	EMPTY = 0,
	START = 1,
	WALL = 2,
	FLOOR = 3
};

struct sCell {
	eCellType type;
};
struct sMapHeader {
	int w; //width of map
	int h; //height of map
	unsigned char bytes; //num bytes per cell
	unsigned char extra[7]; //filling bytes, not used
};

class GameMap
{
public:
	int width;
	int height;
	sCell* data;

	GameMap();
	GameMap(int w, int h);
	sCell& getCell(int x, int y);
	

};
#endif // !GAMEMAP_H


