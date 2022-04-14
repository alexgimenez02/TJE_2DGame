#ifndef PLAYER_H
#define PLAYER_H


#include "includes.h"
#include "utils.h"
#include "image.h"
#include "utils.h"
#include "synth.h"
#include "sprite.h"

class Player
{
private:
	//Atributes
	Sprite sprite;
	Vector2 pos;
	bool isMoving = false, isJumping = false, death = false;
	PLAYER_DIR dir = LEFT;
public:
	Player();
	//ctor
	Player(Sprite *spr, int x, int y);
	//Methods
	void RenderPlayer(Image* framebuffer, float time, int sprite_width, int sprite_height);
	void MovePlayer(Vector2 movement);
	void Jump(Vector2 movement);
	 

};


#endif