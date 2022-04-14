#include "ship.h"



Ship::Ship(){}

Ship::Ship(Sprite *spt, int x, int y)
{
	sprite = *spt;
	pos = Vector2(x, y);
	dir = UP;
}

void Ship::RenderShip(Image* framebuffer, float time, int sprite_width, int sprite_height)
{
	int ship_x = UP, ship_y = 0;
	if (playerInside) {
		if (isMoving) {
			ship_x = ((int)(time * 2.0f) % 4);
			ship_y = dir + 1;
		}
		else {
			ship_x = dir;
			ship_y = 0;
		}
	}
	ship_x *= sprite_width;
	ship_y *= sprite_height;
	sprite.DrawSprite(framebuffer, pos.x, pos.y, ship_x, ship_y);
}

void Ship::ShipMovement(Vector2 movement)
{
	if (movement.x != 0.0f) dir = movement.x >= 0 ? RIGHT : LEFT;
	else if (movement.y != 0.0f) dir = movement.y >= 0 ? DOWN : UP;
	isMoving = movement.x != 0.0f || movement.y != 0.0f;
	pos += movement;
}

void Ship::setPlayerInside() {
	playerInside = !playerInside;
}

Sprite* Ship::getSprite() {
	return &sprite;
}

void Ship::setDirection(PLAYER_DIR d)
{
	dir = d;
}

Vector2 Ship::getPosition()
{
	return pos;
}

bool Ship::getPlayerInside()
{
	return playerInside;
}
