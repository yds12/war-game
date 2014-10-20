#ifndef _WARGAME_UNIT_H
#define _WARGAME_UNIT_H

#include "agl/intvector2.h"
#include "agl/animation.h"
#include "unitmodel.h"
#include "res.h"

using namespace AGL;

/// Unit class
class Unit
{
	private:
		Drawer* drawer;
		Game* game;
				
	public:
		UnitModel* model;
		ushort teamIndex;
		Animation** basicAnimationSet;
		ushort currentAnimation;
		
		ushort id;
		ushort hp;
		IntVector2* position;
		IntVector2* intraSquarePosition;
		bool selected;
		
		Unit(UnitModel* model, ushort teamIndex, Drawer* drawer, Game* game, ushort id);		
		void update();		
		void draw(IntVector2 position);		
		float getPercentualHp();
};

#endif

