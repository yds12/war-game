#ifndef _WARGAME_SMATCH_H
#define _WARGAME_SMATCH_H

#include <vector>
#include "agl/drawer.h"
#include "agl/mouse.h"
#include "agl/keyboard.h"
#include "warmap.h"
#include "match.h"

using namespace AGL;

/// Single Player Match class
class SMatch : public Match
{
	private:
	
	public:
		int unitId;
		vector<Unit*> units; 
	
		SMatch(Drawer* drawer, Game* game, Keyboard* keyboard, Mouse* mouse, Options* opt);		
		void update();
		void draw();
		static void drawTerrain(int i, int j, int x, int y);
		static void drawObjects(int i, int j, int x, int y);
		bool createUnit(UnitModel* model, ushort team, IntVector2* position);
};

#endif

