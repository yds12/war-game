#ifndef _WARGAME_MATCH_H
#define _WARGAME_MATCH_H

#include "agl/drawer.h"
#include "agl/mouse.h"
#include "agl/keyboard.h"
#include "warmap.h"
#include "options.h"
#include "support.h"
#include "team.h"
#include "unit.h"
#include "playercontroller.h"
#include "aicontroller.h"
#include "humancontroller.h"

#define HEALTH_BAR_WIDTH 60
#define HEALTH_BAR_HEIGHT 3

using namespace AGL;

/// Match class
class Match
{
	protected:
		static Drawer* drawer;
		Game* game;
		Keyboard* keyboard;
		Mouse* mouse;
		WarMap* warmap;
		static Options* options;
		static Unit*** unitMap;
	
	public:
		ushort numberOfPlayers;
		static Team** teams;
		PlayerController** controllers;
	
		Match(Drawer* drawer, Game* game, Keyboard* keyboard, Mouse* mouse, Options* opt);		
		virtual void update() = 0;
		virtual void draw() = 0;
};

#endif

