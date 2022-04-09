#ifndef GAMEMAP_H
#define GAMEMAP_H
#include "includes.h"

enum eCellType {
	EMPTY, START,
	WALL,
	DOOR,
	CHEST
};

enum eItemType{
	NOTHING,
	SWORD,
	POTION
};

struct sCell {
	eCellType type;
	eItemType item;
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


