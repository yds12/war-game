#ifndef _WARGAME_PLAYERCONTROLLER_H
#define _WARGAME_PLAYERCONTROLLER_H

#include <stack>
#include <vector>
#include "agl/game.h"
#include "agl/drawer.h"
#include "agl/mouse.h"
#include "agl/keyboard.h"
#include "options.h"
#include "warmap.h"
#include "unit.h"

using namespace AGL;

// Command performed by the player
struct Command
{
	ushort taskType;
	ushort targetX;
	ushort targetY;
	//stack<IntVector2*> path;
};

/// PlayerController class
class PlayerController
{
	protected:
		Drawer* drawer;
		Game* game;
		Keyboard* keyboard;
		Mouse* mouse;
		Options* options;
	
	public:
	
		PlayerController(Game* game, Options* opt);
		virtual void update(WarMap* warmap, vector<Unit*> units) = 0;
		virtual Command getCommand() = 0;
};

#endif

