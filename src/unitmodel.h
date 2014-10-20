#ifndef _WARGAME_UNITMODEL_H
#define _WARGAME_UNITMODEL_H

#include <string>
#include <stdio.h>

#include "agl/support.h"
#include "team.h"
#include "res.h"

#define BASIC_ANIMATION_COUNT 12

// Animation types
#define ANIMATION_STAND_BACK 0
#define ANIMATION_STAND_RIGHT 1
#define ANIMATION_STAND_FRONT 2
#define ANIMATION_STAND_LEFT 3
#define ANIMATION_MOVE_BACK 4
#define ANIMATION_MOVE_RIGHT 5
#define ANIMATION_MOVE_FRONT 6
#define ANIMATION_MOVE_LEFT 7
#define ANIMATION_ATTACK_BACK 8
#define ANIMATION_ATTACK_RIGHT 9
#define ANIMATION_ATTACK_FRONT 10
#define ANIMATION_ATTACK_LEFT 11

using namespace AGL;
using namespace std;

/// UnitModel class
class UnitModel
{
	private:
				
	public:
		char** animationFiles;
		Color imageTeamColor;
		IntVector2* imageGap;
	
		unsigned short id;
		string name;
		
		unsigned int foodCost;
		unsigned short sight;
		unsigned short range;
		unsigned short damage;
		unsigned short armor;
		unsigned short attackDelay;
		unsigned short moveDelay;
		unsigned short trainingTime;
		unsigned short maxHp;
		bool isBuilding;
		
		UnitModel();
		
		void load();
		void load(char* file);
};

#endif

