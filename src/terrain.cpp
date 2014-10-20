#include "terrain.h"

Terrain::Terrain(char* file)
{
	navigable = false;
	walkable = true;
	
	char path[MAX_PATHNAME_LENGTH];
	sprintf(path, "%s%s.png", "terrain/", file);
	imageId = Res::addMiscImage(path, true);
	id = imageId;
}


Terrain::Terrain(char* file, bool _walkable, bool _navigable)
{
	navigable = _navigable;
	walkable = _walkable;
	
	char path[MAX_PATHNAME_LENGTH];
	sprintf(path, "%s%s.png", "terrain/", file);
	imageId = Res::addMiscImage(path, true);
	id = imageId;
}

