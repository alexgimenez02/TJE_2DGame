#include "ship.h"
#include "world.h"


Ship::Ship(){}

Ship::Ship(Sprite *spt, int x, int y)
{
	//Constructor
	sprite = *spt;
	pos = Vector2(x, y);
	dir = UP; //default direction
}


void Ship::RenderShip(Image* framebuffer, float time, int sprite_width, int sprite_height, Vector2 offset)
{
	//It draws the ship into the framebuffer getting all the necesary options
	Vector2 renderShipPos = this->pos - offset;
	int ship_x = UP, ship_y = 0; //Direction and movement
	if (playerInside) {
		if (isMoving) { //If it's moving it changes between interactions
			ship_x = ((int)(time * 2.0f) % 4);
			ship_y = dir + 1;
		}
		else { //Else, it get's the idle animation
			ship_x = dir;
			ship_y = 0;
		}
	}
	ship_x *= sprite_width;
	ship_y *= sprite_height;
	sprite.DrawSprite(framebuffer, renderShipPos.x, renderShipPos.y, ship_x, ship_y);
}

void Ship::ShipMovement(Vector2 movement, World *world)
{
	//Check target colisions
	Vector2 target = pos + movement;
	Vector2 target1 = target - Vector2(10, 0);
	Vector2 target2 = target - Vector2(10, -17);
	Vector2 target3 = target - Vector2(-10, -17);
	Vector2 target4 = target - Vector2(-10, 0);

	//Check if it's moving and which direction it takes
	if (movement.x != 0.0f) dir = movement.x >= 0 ? RIGHT : LEFT;
	else if (movement.y != 0.0f) dir = movement.y >= 0 ? DOWN : UP;
	isMoving = movement.x != 0.0f || movement.y != 0.0f;

	//Check colisions
	if (world->isValid(target1) && world->isValid(target2) && world->isValid(target3) && world->isValid(target4))
		pos = target;
	else if (world->isValid(Vector2(target1.x, pos.y)) && world->isValid(Vector2(target2.x, pos.y)) && world->isValid(Vector2(target3.x, pos.y)) && world->isValid(Vector2(target4.x, pos.y)))
		pos = Vector2(target.x, pos.y);
	else if (world->isValid(Vector2(pos.x, target1.y)) && world->isValid(Vector2(pos.x, target2.y)) && world->isValid(Vector2(pos.x, target3.y)) && world->isValid(Vector2(pos.x, target4.y)))
		pos = Vector2(pos.x, target.y);
	
}

void Ship::setPlayerInside() {
	playerInside = !playerInside; //Change the playerInside state
}

//Getters

Sprite* Ship::getSprite() {
	return &sprite;
}

Vector2 Ship::getPosition()
{
	return pos;
}

bool Ship::getPlayerInside()
{
	return playerInside;
}

//Setters
void Ship::setDirection(PLAYER_DIR d)
{
	dir = d;
}


void Ship::setPosition(int x, int y)
{
	this->pos = Vector2(x, y);
}
