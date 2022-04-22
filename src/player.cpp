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
	else {
		sprite_x = ((int)(time * 2.0f) % 6);
		sprite_y = ((isMoving ? 2 : 0) + dir);
	}
	
	this->sprite.DrawSprite(framebuffer, renderPlayerPos.x, renderPlayerPos.y,sprite_x *= sprite_width,sprite_y *= sprite_height);
	framebuffer->setPixel(renderPlayerPos.x + OFFSET_FEET_X, renderPlayerPos.y + OFFSET_FEET_Y, Color::RED);
	framebuffer->setPixel(renderPlayerPos.x, renderPlayerPos.y + OFFSET_BODY_Y, Color::RED);
	framebuffer->setPixel(renderPlayerPos.x + OFFSET_BODY_X, renderPlayerPos.y + OFFSET_BODY_Y, Color::RED);
	
	framebuffer->setPixel(pos.x, pos.y, Color::GREEN);

}
void Player::MovePlayer(Vector2 movement, World* world){

	
	if (movement.x >= 0) dir = RIGHT;
	else dir = LEFT;
	isMoving = movement.x != 0.0f || movement.y != 0.0f;
	Vector2 prev_pos = pos;
	Vector2 target = pos + movement * speed;
	Vector2 target1 = (target + renderPlayerPos) + Vector2(OFFSET_FEET_X, OFFSET_FEET_Y);
	Vector2 target2 = (target + renderPlayerPos) + Vector2(0, OFFSET_BODY_Y);
	Vector2 target3 = (target + renderPlayerPos) + Vector2(OFFSET_BODY_X, OFFSET_BODY_Y);

	//Check floor
	if (world->isValid(target1) && world->isValid(target2) && world->isValid(target3))
		pos = target;
	else if (world->isValid(Vector2(target1.x, pos.y)) && world->isValid(Vector2(target2.x, pos.y)) && world->isValid(Vector2(target3.x, pos.y)))
		pos = Vector2(target.x, pos.y);
	else if (world->isValid(Vector2(pos.x, target1.y)) && world->isValid(Vector2(pos.x, target2.y)) && world->isValid(Vector2(pos.x, target3.y)))
		pos = Vector2(pos.x, target.y);
}
void Player::Jump(float speed) {
	if (speed != 0.0) {
		
		if (speed < -1.05f) {
			speed = 0.0f;
			
		}
		pos.y -= speed;
		isJumping = speed == 0.0f ? false : true;
	}
	
}
void Player::setPosition(Vector2 p)
{
	pos = p;
}
void Player::die(bool which)
{
	death = which;
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
