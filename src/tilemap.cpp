#include "tilemap.h"

Tilemap::Tilemap(){}

Tilemap::Tilemap(const char* filename)
{
	map.loadTGA(filename);
}
