#ifndef WORLD_H
#define WORLD_H

#include "game.h"

constexpr int NUMBEROFWORLDS = 3;
constexpr int NUMBEROFPAGESTUTORIAL = 3;

class World
{
public:
	//atributes
	Player player;
	GameMap* worldMap;
	GameMap* worlds[NUMBEROFWORLDS];
	GameMap* worldsColiders[NUMBEROFWORLDS];
	GameMap* actualMap;
	GameMap* actualMapColider;
	Image tileset;
	Image background;
	Image tutorial[NUMBEROFPAGESTUTORIAL];
	Vector2 mapaActualPos = Vector2(1, 2);
	Vector2 mapaActualPosC = Vector2(1, 2);
	int currentWorld = 0;
	int currentPage = 0;

	//ctor
	World();
	//methods
	void showWorld(Image* framebuffer);
	Vector2i worldToCell(Vector2 worldSize);
	bool isValid(Vector2 worldPos);
};

#endif