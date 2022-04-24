#include "sprite.h"


Sprite::Sprite() {}

Sprite::Sprite(const char* filename,SPRITE_TYPE s_n,int sw, int sh) {
	//Loads the TGA and add the information
	if (sprite.loadTGA(filename)) {
		sprite_name = s_n;
		sprite_width = sw;
		sprite_height = sh;
	}
	//If it fails, the SPRITE_TYPE is -1 (error code)
	else sprite_name = (SPRITE_TYPE)-1;
}


void Sprite::DrawSprite(Image* framebuffer, int x, int y,int ax, int ay) {
	//draws the sprite into the framebuffer
	framebuffer->drawImage(sprite,x,y,Area(ax, ay, sprite_width, sprite_height));
}
//Getters
int Sprite::getHeight()
{
	return sprite_height;
}

int Sprite::getWidth()
{
	return sprite_width;
}

Image Sprite::getImage()
{
	return this->sprite;
}

SPRITE_TYPE Sprite::getType()
{
	return this->sprite_name;
}

