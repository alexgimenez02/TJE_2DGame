#include "world.h"

World::World()
{
	player = Player(&Sprite("data/Sprites/spritesheet1.tga", SPRITE_TYPE::PLAYER, 14, 17), 0, 97);
	ship = Ship(&Sprite("data/Sprites/spritesheet_ship.tga", SPRITE_TYPE::SHIP, 30, 30), 10, 97);

	//worldMap = loadGameMap("");
	for (int i = 0; i < NUMBEROFWORLDS; i++) {
		string str = "data/mapa" + to_string(i) + ".map";
		worlds[i] = loadGameMap(str.c_str());
		worldsColiders[i] = loadGameMap(str.c_str());
	}
	actualMap = worlds[currentWorld];
	actualMapColider = worldsColiders[currentWorld];
	tileset.loadTGA("data/tileset.tga");
	background.loadTGA("data/space2.tga");
	/*for (int i = 0; i < NUMBEROFPAGESTUTORIAL; i++)
	{
		string str2 = "tutorial"+i+".tga";
		tutorials.loadTGA(str2.c_str());
	}*/
	spawnPoints.push_back(Vector2(0, 96));
	spawnPoints.push_back(Vector2(0, 96));
	spawnPoints.push_back(Vector2(61, 258));
}

void World::showWorld(Image* framebuffer, float elapsed_time)
{
	int cs = tileset.width / 16;
	//for every cell
	for (int x = 0; x < actualMap->width; ++x)
		for (int y = 0; y < actualMap->height; ++y)
		{
			//get cell info
			sCell& cell = actualMap->getCell(x, y);
			if (cell.type == 0)  //skip empty
			{
				continue;
			}
			int type = (int)cell.type;
			//compute tile pos in tileset image
			int tilex = (type % 16) * cs; 	//x pos in tileset
			int tiley = floor(type / 16) * cs;	//y pos in tileset
			Area area(tilex, tiley, cs, cs); //tile area
			int screenx = x * cs - camOffset.x; //place offset here if you want
			int screeny = y * cs - camOffset.y;

			
			
			//avoid rendering out of screen stuff
			if (screenx < -cs || screenx > (int) framebuffer->width ||
				screeny < -cs || screeny > (int) framebuffer->height)
				continue;
			
			//draw region of tileset inside framebuffer
			framebuffer->drawImage(tileset, 		//image
				screenx, screeny, 	//pos in screen
				area); 		//area
		}
}

Vector2i World::worldToCell(Vector2 worldPos)
{
	int cellSize = 12;
	return worldPos /12;
}

bool World::isValid(Vector2 worldPos)
{
	Vector2i cellCoord = worldToCell(worldPos);
	if (cellCoord.x < 0|| cellCoord.x > actualMap->width - 1) return false;

	return actualMap->getCell(cellCoord.x, cellCoord.y).type == EMPTY;
}

void World::updateMap(int map)
{
	if (map != -1) {
		currentWorld = map;
		actualMap = worlds[currentWorld];
		player.setPosition(spawnPoints[currentWorld]);
	}
	if (player.death) {
		playerToCam = Vector2(0.0f, 0.0f);
	}
}
