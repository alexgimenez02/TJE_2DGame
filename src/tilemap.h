#ifndef TILEMAP_H
#define TILEMAP_H

#include "includes.h"
#include "image.h"
#include "utils.h"
#include "synth.h"
#include "player.h"
#include "ship.h"


enum eCellType {
	AIR = 0,
	FLOOR = 1,
	WALL = 2,
	INIVS_WALL = 3

};
struct sCell {
	eCellType type;
};

class Tilemap
{
private:
	Image map;
	int width, height;
public:
	Vector2i spawnPoint;
	Vector2i enemySpawnPoint;
	sCell* data;
	
	Tilemap();
	Tilemap(const char* filename);

};

#endif