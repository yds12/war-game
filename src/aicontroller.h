#ifndef _WARGAME_AICONTROLLER_H
#define _WARGAME_AICONTROLLER_H

#include "playercontroller.h"
#include "unit.h"
#include "support.h"
#include "warmap.h"

using namespace AGL;

/// AIController class
class AIController : public PlayerController
{
	private:	

	public:
		AIController(Game* game, Options* opt);
		Command getCommand();
		void update(WarMap* warmap, vector<Unit*> units);
};

#endif

