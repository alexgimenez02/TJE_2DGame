#ifndef PLAYER_H
#define PLAYER_H


#include "includes.h"
#include "utils.h"
#include "image.h"
#include "sprite.h"

class World;

class Player
{
private:
	//Atributes
	Sprite sprite;
	Vector2 pos;
	bool isMoving = false, isJumping = false, death = false;
	PLAYER_DIR dir;
	float speed = 1.0f;
	Vector2 renderPlayerPos;
	

public:
	Player();
	//ctor
	Player(Sprite *spr, int x, int y);
	//Methods
	void RenderPlayer(Image* framebuffer, float time, int sprite_width, int sprite_height, Vector2 offset);
	void MovePlayer(Vector2 movement, World* world);
	void Jump(float speed);
	void setPosition(Vector2 p);
	Vector2 getPosition();
	void die(bool which);
	bool distanceToShip(Vector2 ship_pos);
	void setSpeed(float spd);

};


#endif