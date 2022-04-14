#include "sprite.h"


Sprite::Sprite() {}

Sprite::Sprite(const char* filename,SPRITE_TYPE s_n,int sw, int sh) {
	if (sprite.loadTGA(filename)) {
		sprite_name = s_n;
		sprite_width = sw;
		sprite_height = sh;
	}
	else sprite_name = SPRITE_TYPE::EMPTY;
}


void Sprite::DrawSprite(Image* framebuffer, int x, int y,int ax, int ay) {
	framebuffer->drawImage(sprite,x,y,Area(ax, ay, sprite_width, sprite_height));
}

