#include "humancontroller.h"

HumanController::HumanController(Drawer* drawer, Game* game, Keyboard* keyboard, Mouse* mouse, Options* opt) : 
	PlayerController(game, opt)
{
	this->drawer = drawer;
	this->keyboard = keyboard;
	this->mouse = mouse;
	
	selectedAction = TASK_NONE;
	currentCommand.taskType = TASK_NONE;
   lastCommandPoint = NULL;
   rectangleCamera = NULL;
   rectangleInit = NULL;
   drawingRectangle = false;
   
   selectedPositions.clear();
   selectedObjects.clear();
}	

Command HumanController::getCommand()
{
	return currentCommand;
}

void HumanController::update(WarMap* warmap, vector<Unit*> units)
{
	currentCommand.taskType = TASK_NONE;
	if(keyboard->isKeyPressed(keyboard->getIndex(AGL::KEY_ESC)))
		selectedAction = TASK_NONE;
		
	int mouseX = mouse->position->x;
	int mouseY = mouse->position->y;
	IntVector2* cameraOrigin = warmap->map->camera->origin;
		
	if(mouse->isLeftButtonDown())
	{
		if (selectedAction == TASK_NONE)
		{
			// Desenha retângulo de seleção
			if(!drawingRectangle)
			{
				delete rectangleInit;
				delete rectangleCamera;
				rectangleInit = new IntVector2(mouseX, mouseY);
				rectangleCamera = new IntVector2(*cameraOrigin);
				drawingRectangle = true;
			}
		}
	}
	else if(mouse->isRightButtonDown())
	{
		IntVector2 actionTarget(mouseX, mouseY);
		IntVector2 actionTarget2 = warmap->map->getPosition(actionTarget);
		
		if(warmap->map->isInMap(actionTarget))
		{
			currentCommand.taskType = TASK_MOVE;
			currentCommand.targetX = actionTarget2.x;
			currentCommand.targetY = actionTarget2.y;
			
			/*currentCommand.path.clear();
			
			// Pegar do A*
			currentCommand.path.push_back(new IntVector2(0, 0));
			currentCommand.path.push_back(new IntVector2(1, 1));
			currentCommand.path.push_back(new IntVector2(2, 2));
			currentCommand.path.push_back(new IntVector2(3, 3));
			currentCommand.path.push_back(new IntVector2(4, 4));
			currentCommand.path.push_back(new IntVector2(5, 5));
			currentCommand.path.push_back(new IntVector2(6, 6));*/
		}
	}
	else
	{
		if(drawingRectangle)
		{
			setSelectedPositions(rectangleInit->x + rectangleCamera->x - cameraOrigin->x, 
										rectangleInit->y + rectangleCamera->y - cameraOrigin->y, 
										mouseX, mouseY, warmap);
			selectArea(units);
			drawingRectangle = false;
		}
	}
}

void HumanController::draw(WarMap* warmap)
{
	drawRectangle(warmap);
}

void HumanController::setSelectedPositions(int x, int y, int finalX, int finalY, WarMap* warmap)
{
	int minorX, majorX, minorY, majorY;

	if(x > finalX)
	{
		minorX = finalX;
		majorX = x;
	}
	else
	{
		minorX = x;
		majorX = finalX;
	}

	if(y > finalY)
	{
		minorY = finalY;
		majorY = y;
	}
	else
	{
		minorY = y;
		majorY = finalY;
	}

	IntVector2 v1(minorX, minorY);
	IntVector2 v2(majorX, minorY);
	IntVector2 v3(minorX, majorY);
	IntVector2 v4(majorX, majorY);
	IntVector2 upLeft = warmap->map->getPosition(v1);
	IntVector2 upRight = warmap->map->getPosition(v2);
	IntVector2 downLeft = warmap->map->getPosition(v3);
	IntVector2 downRight = warmap->map->getPosition(v4);

	selectedPositions.clear();

	bool ul = false, dr = false;
	int cols = 1;
	int initCol = upRight.x;
	int j = upRight.y;

	while(cols > 0)
	{
		for(int i = initCol; i < initCol + cols; i++)
		{
			if(i >= 0 && i < warmap->map->getSize().x && j >= 0 && j < warmap->map->getSize().y)
			{
				IntVector2* sp = new IntVector2(i, j);
				selectedPositions.push_back(sp);
				//delete sp;
			}

			if(j >= upLeft.y) ul = true;
			if(j >= downRight.y) dr = true;
		}

		if(ul && dr) { cols -= 2; initCol++; }
		else if(ul) initCol++;
		else if(dr) initCol--;
		else { cols += 2; initCol -= 1; }

		if(cols < 1 || j > warmap->map->getSize().y) break;
		j++;
	}
}

void HumanController::selectArea(vector<Unit*> units)
{
	for(int j = 0; j < units.size(); j++)
	{
		if(units[j]->teamIndex != options->myIndex) continue;
		
		units[j]->selected = false;
		
		for(int i = 0; i < selectedPositions.size(); i++)
		{
			if(units[j]->position->x == selectedPositions[i]->x && units[j]->position->y == selectedPositions[i]->y)
			{
				units[j]->selected = true;
				break;
			}
		}
	}	
}

void HumanController::drawRectangle(WarMap* warmap)
{
	if(drawingRectangle)
	{
		IntVector2 rectangleVector(rectangleInit->x + rectangleCamera->x - warmap->map->camera->origin->x,
											rectangleInit->y + rectangleCamera->y - warmap->map->camera->origin->y);
		
		int minorX, majorX, minorY, majorY;

		if(rectangleVector.x > mouse->position->x)
		{
			minorX = mouse->position->x;
			majorX = rectangleVector.x;
		}
		else
		{
			minorX = rectangleVector.x;
			majorX = mouse->position->x;
		}

		if(rectangleVector.y > mouse->position->y)
		{
			minorY = mouse->position->y;
			majorY = rectangleVector.y;
		}
		else
		{
			minorY = rectangleVector.y;
			majorY = mouse->position->y;
		}

		Graphics gph;
		Image* rectangle = NULL;
		
		if(minorX < majorX && minorY < majorY)
		{
			rectangle = gph.getRectangleOutline(majorX - minorX, majorY - minorY, 
															options->selectionRectangleColor, options->selectionRectangleAlpha);
			IntVector2 pos(minorX, minorY);
			drawer->draw(rectangle, pos);
			delete rectangle;
		}
	}
}

