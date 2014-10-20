#include "aicontroller.h"

AIController::AIController(Game* game, Options* opt) : PlayerController(game, opt)
{

}	
		
Command AIController::getCommand()
{
	Command cmd;
	cmd.taskType = TASK_NONE;
	return cmd;
}
		
void AIController::update(WarMap* warmap, vector<Unit*> units)
{
	
}

