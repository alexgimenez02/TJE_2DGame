#include "planet.h"

Planet::Planet()
{
	pos = Vector2(0, 0);
	width = height = 0;
}

Planet::Planet(Vector2 p, int w, int h)
{
	pos = p;
	width = w;
	height = h;
}

Planet::Planet(Vector2 p, Sprite* spr)
{
	pos = p;
	sprite = *spr;
	width = spr->getWidth();
	height = spr->getHeight();
}

void Planet::RenderPlanet(Image* framebuffer, float time, int sprite_width , Vector2 offset)
{
	Vector2 renderPlanetPos = this->pos - offset;
	int planet_x = ((int)(time * 2.0f) % 5) * sprite_width;
	sprite.DrawSprite(framebuffer, renderPlanetPos.x, renderPlanetPos.y, planet_x, 0);
}

