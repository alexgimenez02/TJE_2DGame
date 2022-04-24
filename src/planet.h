#ifndef PLANET_H
#define PLANET_H
#include "sprite.h"
#include "utils.h"
class Planet
{
public:
	Vector2 pos;
	int width, height;
	Sprite sprite;

	Planet();
	Planet(Vector2 p, int w, int h);
	Planet(Vector2 p, Sprite* spr);
	void RenderPlanet(Image* framebuffer, float time, int sprite_width, Vector2 offset);
};

#endif PLANET_H