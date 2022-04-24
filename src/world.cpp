#include "world.h"

World::World()
{
	//Load every element of the game world
	player = Player(&Sprite("data/Sprites/spritesheet1.tga", SPRITE_TYPE::PLAYER, 14, 17), 0, 97);
	ship = Ship(&Sprite("data/Sprites/spritesheet_ship.tga", SPRITE_TYPE::SHIP, 30, 30), 10, 97);
	planets[0] = Planet(Vector2(0, 0), &Sprite("data/Sprites/MainPlanet.tga", SPRITE_TYPE::PLANET, 50, 50));
	planets[1] = Planet(Vector2(200,50),&Sprite("data/Sprites/DryPlanet.tga",SPRITE_TYPE::PLANET,50,50));
	planets[2] = Planet(Vector2(150, 225), &Sprite("data/Sprites/BlackHole.tga", SPRITE_TYPE::PLANET, 75, 73));
	ship.setPlayerInside(); //Set the player inside the ship
	worldMap = loadGameMap("data/emptymap.map"); //Fist map (Just an empty .map of 32x32
	monster = Player(&Sprite("data/Sprites/spritesheet2.tga", SPRITE_TYPE::MONSTER, 14, 17), 1023, 246);
	//Load all stages
	for (int i = 0; i < NUMBEROFWORLDS; i++) {
		string str = "data/mapa" + to_string(i) + ".map";
		worlds[i] = loadGameMap(str.c_str());
	}
	//Set starting map
	actualMap = worldMap;
	//Load the tileset and background
	tileset.loadTGA("data/tileset.tga");
	background.loadTGA("data/fondo1.tga");

	//Load of the pages of the tutorial
	for (int i = 0; i < NUMBEROFPAGESTUTORIAL; i++)
	{
		string str2 = "data/tutorial"+ to_string(i + 1) +".tga";
		tutorial[i].loadTGA(str2.c_str());
	}

	//Spawnpoints setting
	spawnPoints.push_back(Vector2(0, 96));
	spawnPoints.push_back(Vector2(0, 96));
	spawnPoints.push_back(Vector2(70, 257));

	
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
			if (cell.type == 0 && actualMap != worldMap)  //skip empty
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
			if(actualMap != worldMap)
				framebuffer->drawImage(tileset, 		//image
				screenx, screeny, 	//pos in screen
				area); 		//area
			
		}
		
}

Vector2i World::worldToCell(Vector2 worldPos)
{
	//Get the position of each tile
	int cellSize = 12;
	return worldPos /12;
}

bool World::isValid(Vector2 worldPos)
{
	//Check if the position is valid
	Vector2i cellCoord = worldToCell(worldPos);
	if (cellCoord.x < 0|| cellCoord.x > actualMap->width - 1) return false;

	return actualMap->getCell(cellCoord.x, cellCoord.y).type == EMPTY;
}

void World::updateMap(int map)
{
	//Update which map will be rendered
	if (map != -1) {
		//Load the 3 worlds
		if (map < 3)
		{

			currentWorld = map;
			actualMap = worlds[currentWorld];
			player.setPosition(spawnPoints[currentWorld]);
		}
		//Load the worldMap
		else {
			actualMap = worldMap;
		}
	}
}
