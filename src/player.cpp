#include "player.h"

Player::Player() {}

Player::Player(Sprite *spr, int x, int y) {
	this->sprite = *spr;
	pos = Vector2(x, y);
}

void Player::RenderPlayer(Image* framebuffer, float time, int sprite_width, int sprite_height){
	int sprite_x, sprite_y;
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
	this->sprite.DrawSprite(framebuffer,pos.x,pos.y,sprite_x *= sprite_width,sprite_y *= sprite_height);
}
void Player::MovePlayer(Vector2 movement){

	if (movement.x >= 0) dir = RIGHT;
	else dir = LEFT;
	isMoving = movement.x != 0.0f || movement.y != 0.0f;
	pos += movement;
}
void Player::Jump(Vector2 movement) {

}