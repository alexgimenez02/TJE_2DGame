#ifndef TILEMAP_H
#define TILEMAP_H

#include "includes.h"
#include "image.h"
#include "utils.h"
#include "synth.h"
#include "player.h"
#include "ship.h"

class Tilemap
{
private:
	Image map;
public:
	Tilemap();
	Tilemap(const char* filename);

};

#endif