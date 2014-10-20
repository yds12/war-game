#ifndef _WARGAME_MMATCH_H
#define _WARGAME_MMATCH_H

#include "agl/drawer.h"
#include "agl/mouse.h"
#include "agl/keyboard.h"
#include "warmap.h"
#include "match.h"

using namespace AGL;

/// Multiplayer Match class
class MMatch : public Match
{
	private:
	
	public:
		MMatch(Drawer* drawer, Game* game, Keyboard* keyboard, Mouse* mouse, Options* opt);		
		void update();
		void draw();	
};

#endif

