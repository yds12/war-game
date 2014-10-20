#ifndef _WARGAME_TERRAIN_H
#define _WARGAME_TERRAIN_H

#include <string>

#include "agl/format.h"
#include "agl/image.h"

#include "res.h"

using namespace AGL;

/// Terrain class
class Terrain
{
	private:
	public:
		bool navigable;
		bool walkable;
		unsigned short imageId;
		unsigned short darkImageId;
		unsigned short id;
		
		Terrain(char* file);
		Terrain(char* file, bool _walkable, bool _navigable);
};

#endif

