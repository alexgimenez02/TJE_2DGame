#include "world.h"

World::World(){
	Game* game = Game::instance;
	player = game->player;
	//worldMap = loadGameMap("");
	for (int i = 0; i < NUMBEROFWORLDS; i++) {
		string str = "data/mapa" + to_string(i) + ".tga";
		worlds[i] = loadGameMap(str.c_str());
		worldsColiders[i] = loadGameMap(str.c_str());
		
	}
	actualMap = worlds[currentWorld];
	actualMapColider = worldsColiders[currentWorld];
	tileset.loadTGA("data/tileset.tga");
	background.loadTGA("data/space.tga");
	/*for (int i = 0; i < NUMBEROFPAGESTUTORIAL; i++)
	{
		string str2 = "tutorial"+i+".tga";
		tutorials.loadTGA(str2.c_str());
	}*/


}

void World::showWorld(Image* framebuffer){
//size in pixels of a cell, we assume every row has 16 cells so the cell size must be image.width / 16
int cs = tileset.width / 16;

//for every cell
	for (int x = 0; x < actualMap->width; ++x)
		for (int y = 0; y < actualMap->height; ++y)
		{
			//get cell info
			sCell& cell = actualMap->getCell(x, y);
			if (cell.type == 0) //skip empty
				continue;
			int type = (int)cell.type;
			//compute tile pos in tileset image
			int tilex = (type % 16) * cs; 	//x pos in tileset
			int tiley = floor(type / 16) * cs;	//y pos in tileset
			Area area(tilex, tiley, cs, cs); //tile area
			int screenx = x * cs - player.getPosition().x; //place offset here if you want
			int screeny = y * cs - player.getPosition().y; 
			//avoid rendering out of screen stuff
			if (screenx < -cs || screenx > framebuffer->width ||
				screeny < -cs || screeny > framebuffer->height)
				continue;

			//draw region of tileset inside framebuffer
			framebuffer->drawImage(tileset, 		//image
				screenx, screeny, 	//pos in screen
				area); 		//area
		}
}

Vector2i World::worldToCell(Vector2 worldSize)
{ 
	Vector2i mapOrigin = Vector2i(0, 0);
	Vector2 posWorld = Vector2(20.0f, 20.0f);
	int cellSize = 12;

	Vector2i cellPos = (posWorld - mapOrigin) / cellSize;
	posWorld = (cellPos * cellSize) + mapOrigin;

	int halfCell = cellSize / 2;
	posWorld = ((cellPos * cellSize) + mapOrigin) + Vector2i(halfCell, halfCell);
	return posWorld;
}

bool World::isValid(Vector2 worldPos)
{
	if (worldPos.x < 0 || worldPos.x > actualMap->width - 1) return false;
	
	if (actualMapColider->getCell(worldPos.x,worldPos.y).type != 0) return false;
	return true;
}
