#include "smatch.h"

SMatch::SMatch(Drawer* drawer, Game* game, Keyboard* keyboard, Mouse* mouse, Options* opt) : Match(drawer, game, keyboard, mouse, opt)
{
	numberOfPlayers = opt->numberOfPlayers;	
	teams = new Team*[numberOfPlayers];	
	controllers = new PlayerController*[numberOfPlayers];
	
	for(int i = 0; i < numberOfPlayers; i++)
	{
		Res::setColor(i, opt->colors[i]);
		teams[i] = new Team(opt->colors[i]);
		
		if(i == options->myIndex) controllers[i] = new HumanController(drawer, game, keyboard, mouse, options);
		else controllers[i] = new AIController(game, options);
	}
	
	warmap = new WarMap(drawer, game, keyboard, mouse, options);
	warmap->loadRandom();

	unitMap = new Unit**[warmap->size->x];
	for(int i = 0; i < warmap->size->x; i++)
	{
		unitMap[i] = new Unit*[warmap->size->y];
		for(int j = 0; j < warmap->size->y; j++)
		{
			unitMap[i][j] = NULL;
		}
	}

	unitId = 0;	
	units.clear();
	UnitModel* lancer = new UnitModel;
	lancer->load();
	
  int count = 0;
  int space = 4;
	for(int i = 0; i < warmap->size->x; i += space)
	{
    for(int j = 0; j < warmap->size->y; j += space)
    {
      IntVector2* position = new IntVector2(i, j);
      if(!createUnit(lancer, (i/space)%2, position))
      {
        //printf("Unit can not be created here\n");
      }
      else
      {
        count++;
      }
    }
	}

  // DEBUG
  printf("%d units created", count);
	
	for(int i = 0; i < numberOfPlayers; i++)
		teams[i]->initMaps(*(warmap->size));
}

bool SMatch::createUnit(UnitModel* model, ushort team, IntVector2* position)
{
	if(unitMap[position->x][position->y] != NULL || 
		warmap->natureMap[position->x][position->y] != NULL ||
		!warmap->terrainMap[position->x][position->y]->walkable) return false;
	
	Unit* lancer1 = new Unit(model, team, drawer, game, unitId);
	lancer1->position = position;
	unitMap[lancer1->position->x][lancer1->position->y] = lancer1;
	units.push_back(lancer1);
	unitId++;
	return true;
}

void SMatch::update()
{	
	Command commands[numberOfPlayers];

	for(int i = 0; i < numberOfPlayers; i++)
	{
		// resets sightmap
		if(game->gameCounter == 0)	teams[i]->resetSightMap();
		
		// get controls from input (or net or AI)
		controllers[i]->update(warmap, units);
		Command cmd = controllers[i]->getCommand();
		commands[i] = cmd;
		
		if(commands[i].taskType > 0)
		printf("player %d performed command %d with target %d,%d\n", 
			i, commands[i].taskType, commands[i].targetX, commands[i].targetY);
	}

	for(int k = 0; k < units.size(); k++)
	{
		units[k]->update();
		
		// Sightmap update is done once each 60 updates for each unit (in different times depending on the unit id)
		if(units[k]->id % 60 != game->gameCounter) continue;
		
		//if(game->gameCounter > 0) continue;
		
		int i = units[k]->position->x;
		int j = units[k]->position->y;

		if(units[k] != NULL)
		{
			int sight = units[k]->model->sight;
			int mini = i - sight;
			int maxi = i + sight;
			int minj = j - sight;
			int maxj = j + sight;
			
			if(mini < 0) mini = 0;
			if(minj < 0) minj = 0;
			if(maxi > warmap->size->x - 1) maxi = warmap->size->x - 1;
			if(maxj > warmap->size->y - 1) maxj = warmap->size->y - 1;
		
			for(int ii = mini; ii < maxi; ii++)
				for(int jj = minj; jj < maxj; jj++)
				{
					IntVector2 v1(i, j);
					IntVector2 v2(ii, jj);
					
					if(v1.distance(v2) < units[k]->model->sight) 
					{
						teams[units[k]->teamIndex]->sightMap[ii][jj] = true;
						teams[units[k]->teamIndex]->knownMap[ii][jj] = true;
					}
				}
		}
	}

	warmap->update();
}

void SMatch::draw()
{
	warmap->map->forEachVisible(drawTerrain);
	warmap->map->forEachVisible(drawObjects);
	((HumanController*)controllers[options->myIndex])->draw(warmap);
}

void SMatch::drawTerrain(int i, int j, int x, int y)
{
	IntVector2 pos(x, y);
		
	if(teams[options->myIndex]->knownMap[i][j])
		drawer->draw(Res::getMiscImage(WarMap::terrainMap[i][j]->imageId, !(teams[options->myIndex]->sightMap[i][j])), pos);
}

#include "agl/color.h"

void SMatch::drawObjects(int i, int j, int x, int y)
{
	Graphics gph;

	if(teams[options->myIndex]->knownMap[i][j])
	{ 
		if(WarMap::natureMap[i][j] != NULL)
		{
			IntVector2 pos(x + WarMap::natureMap[i][j]->imageGap.x, y + WarMap::natureMap[i][j]->imageGap.y);
			drawer->draw(Res::getMiscImage(WarMap::natureMap[i][j]->imageId, !(teams[options->myIndex]->sightMap[i][j])), pos);
		}
		if(unitMap[i][j] != NULL)
		{
			IntVector2 pos(x + unitMap[i][j]->model->imageGap->x, y + unitMap[i][j]->model->imageGap->y);
			unitMap[i][j]->draw(pos);
			
			if(unitMap[i][j]->selected)
			{
				Image* redRect = 
					gph.getCompleteRectangle(HEALTH_BAR_WIDTH, HEALTH_BAR_HEIGHT, AGL_COLOR_RED, AGL_COLOR_BLACK, 255);
				drawer->draw(redRect, pos);
				delete redRect;

				int healthBar = CEIL(HEALTH_BAR_WIDTH * unitMap[i][j]->getPercentualHp());
				Image* greenRect = 
					gph.getCompleteRectangle(healthBar, HEALTH_BAR_HEIGHT, AGL_COLOR_LIME, AGL_COLOR_BLACK, 255);
				drawer->draw(greenRect, pos);
				delete greenRect;
			}
		}
	}
}

