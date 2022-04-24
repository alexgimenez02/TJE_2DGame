#ifndef SPRITE_H
#define SPRITE_H


#include "utils.h"
#include "image.h"
#include "utils.h"
#include "synth.h"



class Sprite
{
private:
	Image sprite;
	SPRITE_TYPE sprite_name;
	int sprite_width = 0, sprite_height = 0;

public:
	
	Sprite();
	Sprite(const char* filename, SPRITE_TYPE s_n, int sw, int sh);
	

	void DrawSprite(Image* framebuffer, int x, int y, int ax, int ay);
	int getHeight();
	int getWidth();
	Image getImage();
	SPRITE_TYPE getType();
};

#endif