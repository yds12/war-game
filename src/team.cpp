#include "team.h"

Team::Team(Color color)
{
	this->color = color;
}

void Team::initMaps(IntVector2 size)
{
	mapSize = size;

	knownMap = new bool*[mapSize.x];
	sightMap = new bool*[mapSize.x];
	
	for(int i = 0; i < mapSize.x; i++)
	{
		knownMap[i] = new bool[mapSize.y];
		sightMap[i] = new bool[mapSize.y]; 
		
		for(int j = 0; j < mapSize.y; j++)
		{
			knownMap[i][j] = false;
			sightMap[i][j] = false;
		}
	}
}

void Team::resetSightMap()
{
	for(int i = 0; i < mapSize.x; i++)
		for(int j = 0; j < mapSize.y; j++)
			sightMap[i][j] = false;
}

