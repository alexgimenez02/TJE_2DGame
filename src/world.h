#ifndef WORLD_H
#define WORLD_H

#include "player.h"
#include "planet.h"
#include "ship.h"
#include "gamemap.h"
#include "image.h"
#include <vector>


constexpr int NUMBEROFWORLDS = 3;
constexpr int NUMBEROFPLANETS = 3;
constexpr int NUMBEROFPAGESTUTORIAL = 3;



class World
{
public:
	//atributes
	Vector2 camOffset;
	Vector2 playerToCam = Vector2(-70.0f, -40.0f);
	vector<Vector2> spawnPoints;
	Planet planets[NUMBEROFPLANETS];
	Player player;
	Ship ship;
	GameMap* worldMap;
	GameMap* worlds[NUMBEROFWORLDS];
	GameMap* actualMap;
	GameMap* actualMapColider;
	Image tileset;
	Image background;
	Image tutorial[NUMBEROFPAGESTUTORIAL];
	int currentWorld = 0;
	int currentPage = 0;

	//ctor
	World();
	//methods
	void showWorld(Image* framebuffer,float elapsed_time);
	Vector2i worldToCell(Vector2 worldSize);
	bool isValid(Vector2 worldPos);
	void updateMap(int map);
};

#endif