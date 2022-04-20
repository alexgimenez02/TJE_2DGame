#ifndef GAMEMAP_H
#define GAMEMAP_H
#include "includes.h"
#include <cassert>

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
	void SetCell(int x, int y, eCellType tp);
	

};
static GameMap* loadGameMap(const char* filename)
{
	FILE* file = fopen(filename, "rb");
	if (file == NULL) //file not found
		return NULL;

	sMapHeader header; //read header and store it in the struct
	fread(&header, sizeof(sMapHeader), 1, file);
	assert(header.bytes == 1); //always control bad cases!!


	//allocate memory for the cells data and read it
	unsigned char* cells = new unsigned char[header.w * header.h];
	fread(cells, header.bytes, header.w * header.h, file);
	fclose(file); //always close open files
	//create the map where we will store it
	GameMap* map = new GameMap(header.w, header.h);

	for (int x = 0; x < map->width; x++)
		for (int y = 0; y < map->height; y++)
			map->getCell(x, y).type = (eCellType)cells[x + y * map->width];

	delete[] cells; //always free any memory allocated!

	return map;
}
#endif // !GAMEMAP_H


