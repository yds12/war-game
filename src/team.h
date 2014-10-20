#ifndef _WARGAME_TEAM_H
#define _WARGAME_TEAM_H

#include "agl/support.h"
#include "agl/intvector2.h"

using namespace AGL;

/// Team class
class Team
{
	private:
		IntVector2 mapSize;
				
	public:
		bool** knownMap;
		bool** sightMap;	
		Color color;
	
		Team(Color color);		
		void initMaps(IntVector2 size);
		void resetSightMap();
};

#endif

