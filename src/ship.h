#ifndef SHIP_H
#define SHIP_H

#include "includes.h"
#include "utils.h"
#include "image.h"
#include "utils.h"
#include "synth.h"

class Ship
{
private:
	Vector2 pos;
	bool isMoving = false, playerInside = false;
	PLAYER_DIR dir;
public:
	void RenderShip(Image* framebuffer, float time, int sprite_width, int sprite_height);
	void ShipMovement(Vector2 movement);
	void rotate(Vector2 dir);
};

#endif