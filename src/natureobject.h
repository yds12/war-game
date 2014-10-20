#ifndef _WARGAME_NATUREOBJECT_H
#define _WARGAME_NATUREOBJECT_H

#include <stdio.h>

#include "agl/intvector2.h"

//#include "support.h"
#include "res.h"

using namespace std;

#define RESOURCE_NONE 3
#define RESOURCE_WOOD 0
#define RESOURCE_GOLD 1
#define RESOURCE_FOOD 2

/// NatureObject
class NatureObject
{
	private:
				
	public:
		unsigned short resourceType;
		unsigned short source;
	
		bool navigable;
		bool walkable;	
		unsigned short imageId;	
		unsigned short id;
		IntVector2 imageGap;

		NatureObject(char* file, bool _walkable, bool _navigable, unsigned short resType, unsigned short _source, IntVector2 _imageGap);
};

#endif

