#include "player.h"
#include "world.h"
//Empty constructor
Player::Player() {}


//Constructor
Player::Player(Sprite *spr, int x, int y) {
	this->sprite = *spr;
	pos = Vector2(x, y);
	dir = RIGHT; //Default position
}

void Player::RenderPlayer(Image* framebuffer, float time, int sprite_width, int sprite_height, Vector2 offset){
	int sprite_x, sprite_y; //Sprite position in the tga
	if(sprite.getType() == PLAYER){ //If it is the player
		renderPlayerPos = this->pos - offset;
		if (isJumping) { //Jumping
			sprite_x = ((int)(time * 2.0f) % 5);
			sprite_y = dir + 4;
		}
		else if (isFalling) { //falling
			sprite_x = 3;
			sprite_y = dir + 4;
		}
		else { //Running or idle
			sprite_x = ((int)(time * 2.0f) % 6);
			sprite_y = ((isMoving ? 2 : 0) + dir);
		}
	}
	else { //If it is the monster
		renderPlayerPos = this->pos - offset;
		sprite_x = ((int)(time * 2.0f) % 6);
		sprite_y = ((isMoving ? 2 : 0) + LEFT);

	}
	//We draw the sprite
	this->sprite.DrawSprite(framebuffer, renderPlayerPos.x, renderPlayerPos.y,sprite_x *= sprite_width,sprite_y *= sprite_height);

}
void Player::MovePlayer(Vector2 movement, World* world){

	if(!death) {
		if (movement.x >= 0) dir = RIGHT;
		else dir = LEFT;
		//Moving
		isMoving = movement.x != 0.0f || movement.y != 0.0f;
		//Bounding box
		Vector2 prev_pos = pos;
		Vector2 target = pos + movement * speed;
		Vector2 target1 = target - Vector2(10, 0);
		Vector2 target2 = target - Vector2(10, -17);
		Vector2 target3 = target - Vector2(-10, -17);
		Vector2 target4 = target - Vector2(-10, 0);

		//Check floor collision
		if (world->isValid(target1) && world->isValid(target2) && world->isValid(target3) && world->isValid(target4))
			pos = target;
		else if (world->isValid(Vector2(target1.x, pos.y)) && world->isValid(Vector2(target2.x, pos.y)) && world->isValid(Vector2(target3.x, pos.y)) && world->isValid(Vector2(target4.x, pos.y)))
			pos = Vector2(target.x, pos.y);
		else if (world->isValid(Vector2(pos.x, target1.y)) && world->isValid(Vector2(pos.x, target2.y)) && world->isValid(Vector2(pos.x, target3.y)) && world->isValid(Vector2(pos.x, target4.y)))
			pos = Vector2(pos.x, target.y);

		//Check if it is inside the ship
		if (!world->ship.getPlayerInside()) {
			//Check if is falling
			if (world->isValid(target - Vector2(0, -18)) && !isJumping) {
				pos.y += 1; //Update
				isFalling = true;
			}
			else {
				isFalling = false;
			}
		}
	}
}
void Player::Jump(float speed, World* world) {
	//If the player is outside the ship
	
	if (speed != 0.0) { //If it isn't in the ground (no jumping)
		//Check colisions
		Vector2 target = Vector2(pos.x,pos.y - speed);
		Vector2 target1 = target - Vector2(10, 0);
		Vector2 target2 = target - Vector2(10, -17);
		Vector2 target3 = target - Vector2(-10, -17);
		Vector2 target4 = target - Vector2(-10, 0);
		if (speed < -1.05f) { //If no colision reach peak and fall
			speed = 0.0f;
		}
		else {
			//If colision, check it
			if (world->isValid(target1) && world->isValid(target2) && world->isValid(target3) && world->isValid(target4))
				pos = target;
			else if (world->isValid(Vector2(target1.x, pos.y)) && world->isValid(Vector2(target2.x, pos.y)) && world->isValid(Vector2(target3.x, pos.y)) && world->isValid(Vector2(target4.x, pos.y)))
				pos = Vector2(target.x, pos.y);
			else if (world->isValid(Vector2(pos.x, target1.y)) && world->isValid(Vector2(pos.x, target2.y)) && world->isValid(Vector2(pos.x, target3.y)) && world->isValid(Vector2(pos.x, target4.y)))
				pos = Vector2(pos.x, target.y);
			
		}
		//Check if jumping or not
		isJumping = speed == 0.0f ? false : true;
	}
	
	
}

//Getters
Sprite Player::getSprite()
{
	return this->sprite;
}

Vector2 Player::getPosition()
{
	return pos;
}
//Setters
void Player::setPosition(Vector2 p)
{
	pos = p;
}

void Player::setSpeed(float spd)
{
	speed = spd;
}

//Check player distance to ship
bool Player::distanceToShip(Vector2 ship_pos) {
	return pos.distance(ship_pos) < 10.0f;
}
