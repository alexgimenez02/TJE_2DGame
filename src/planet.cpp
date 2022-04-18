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

