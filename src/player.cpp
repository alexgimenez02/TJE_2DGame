#include "player.h"
#include "world.h"

#define OFFSET_FEET_X 6
#define OFFSET_FEET_Y 16
#define OFFSET_BODY_X 13
#define OFFSET_BODY_Y 8

Player::Player() {}

Player::Player(Sprite *spr, int x, int y) {
	this->sprite = *spr;
	pos = Vector2(x, y);
	dir = RIGHT;
}

void Player::RenderPlayer(Image* framebuffer, float time, int sprite_width, int sprite_height, Vector2 offset){
	int sprite_x, sprite_y;
	renderPlayerPos = this->pos - offset;
	if (death){
		sprite_x = ((int)(time * 4.0f) % 4);
		sprite_y = 6;
	}
	else if (isJumping) {
		sprite_x = ((int)(time * 2.0f) % 5);
		sprite_y = dir + 4;
	}
	else if (isFalling) {
		sprite_x = 3;
		sprite_y = dir + 4;
	}
	else {
		sprite_x = ((int)(time * 2.0f) % 6);
		sprite_y = ((isMoving ? 2 : 0) + dir);
	}
	
	this->sprite.DrawSprite(framebuffer, renderPlayerPos.x, renderPlayerPos.y,sprite_x *= sprite_width,sprite_y *= sprite_height);

}
void Player::MovePlayer(Vector2 movement, World* world){

	if(!death) {
		if (movement.x >= 0) dir = RIGHT;
		else dir = LEFT;
		isMoving = movement.x != 0.0f || movement.y != 0.0f;
		Vector2 prev_pos = pos;
		Vector2 target = pos + movement * speed;
		Vector2 target1 = target - Vector2(10, 0);
		Vector2 target2 = target - Vector2(10, -17);
		Vector2 target3 = target - Vector2(-10, -17);
		Vector2 target4 = target - Vector2(-10, 0);

		//Check floor
		if (world->isValid(target1) && world->isValid(target2) && world->isValid(target3) && world->isValid(target4))
			pos = target;
		else if (world->isValid(Vector2(target1.x, pos.y)) && world->isValid(Vector2(target2.x, pos.y)) && world->isValid(Vector2(target3.x, pos.y)) && world->isValid(Vector2(target4.x, pos.y)))
			pos = Vector2(target.x, pos.y);
		else if (world->isValid(Vector2(pos.x, target1.y)) && world->isValid(Vector2(pos.x, target2.y)) && world->isValid(Vector2(pos.x, target3.y)) && world->isValid(Vector2(pos.x, target4.y)))
			pos = Vector2(pos.x, target.y);
		if (!world->ship.getPlayerInside()) {
			if (world->isValid(target - Vector2(0, -18)) && !isJumping) {

				pos.y += 1;
				isFalling = true;
			}
			else {
				isFalling = false;
			}
		}
	}
}
void Player::Jump(float speed, World* world) {
	if(!world->ship.getPlayerInside())
	{
		if (speed != 0.0) {
			Vector2 target = Vector2(pos.x,pos.y - speed);
			Vector2 target1 = target - Vector2(10, 0);
			Vector2 target2 = target - Vector2(10, -17);
			Vector2 target3 = target - Vector2(-10, -17);
			Vector2 target4 = target - Vector2(-10, 0);
			if (speed < -1.05f) {
				speed = 0.0f;
			}
			else {
				if (world->isValid(target1) && world->isValid(target2) && world->isValid(target3) && world->isValid(target4))
					pos = target;
				else if (world->isValid(Vector2(target1.x, pos.y)) && world->isValid(Vector2(target2.x, pos.y)) && world->isValid(Vector2(target3.x, pos.y)) && world->isValid(Vector2(target4.x, pos.y)))
					pos = Vector2(target.x, pos.y);
				else if (world->isValid(Vector2(pos.x, target1.y)) && world->isValid(Vector2(pos.x, target2.y)) && world->isValid(Vector2(pos.x, target3.y)) && world->isValid(Vector2(pos.x, target4.y)))
					pos = Vector2(pos.x, target.y);
			
			}
			isJumping = speed == 0.0f ? false : true;
		}
	}
	
}
void Player::setPosition(Vector2 p)
{
	pos = p;
}
void Player::die(World* world) {
	death = true;
	pos.y -= -1.0f;
}

Vector2 Player::getPosition()
{
	return pos;
}

void Player::setSpeed(float spd)
{
	speed = spd;
}

bool Player::distanceToShip(Vector2 ship_pos) {
	return pos.distance(ship_pos) < 10.0f;
}
