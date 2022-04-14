#ifndef SHIP_H
#define SHIP_H

#include "includes.h"
#include "utils.h"
#include "image.h"
#include "utils.h"
#include "synth.h"
#include "sprite.h"

class Ship
{
private:
	//attributes
	Sprite sprite;
	Vector2 pos;
	bool isMoving = false, playerInside = false;
	PLAYER_DIR dir;
public:
	//ctor
	Ship();
	Ship(Sprite *spt, int x, int y);
	//methods
	void RenderShip(Image* framebuffer, float time, int sprite_width, int sprite_height);
	void ShipMovement(Vector2 movement);
	void setPlayerInside();
	void setDirection(PLAYER_DIR d);
	Sprite* getSprite();
	Vector2 getPosition();
	bool getPlayerInside();
};

#endif