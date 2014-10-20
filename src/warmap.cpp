#include "warmap.h"

#define PROB(a) (((float)(rand() % 100000)) / 1000.0 < a) 
#define TERRAINEQUAL(x,y,t) (WarMap::terrainMap[x][y] != NULL && WarMap::terrainMap[x][y]->id == terrain[t]->id)
#define NATUREEQUAL(x,y,t) (WarMap::natureMap[x][y] != NULL && WarMap::natureMap[x][y]->id == nature[t]->id)
#define TERRAINNOTNULL(x,y) (WarMap::terrainMap[x][y] != NULL)

Drawer* WarMap::drawer;
Game* WarMap::game;
Keyboard* WarMap::keyboard;
Mouse* WarMap::mouse;
Options* WarMap::options;
Terrain*** WarMap::terrainMap;
Terrain** WarMap::terrain;
NatureObject*** WarMap::natureMap;
NatureObject** WarMap::nature;
ushort** WarMap::sourceMap;

WarMap::WarMap(Drawer* drawer, Game* game, Keyboard* keyboard, Mouse* mouse, Options* opt)
{
	WarMap::drawer = drawer;
	WarMap::game = game;
	WarMap::keyboard = keyboard;
	WarMap::mouse = mouse;
}

void WarMap::load(char* file)
{
	
}

void WarMap::loadRandom()
{
	initMaps(256, 256);

	terrain = new Terrain*[TERRAIN_TYPE_COUNT];
	terrain[0] = new Terrain("grass");
	terrain[1] = new Terrain("water", false, true);
	terrain[2] = new Terrain("mud");
	terrain[3] = new Terrain("sand");
	//terrain[4] = new Terrain("ground");
	
	nature = new NatureObject*[NATURE_TYPE_COUNT];	
	IntVector2 treegap(-5, -60);
	IntVector2 goldgap(0, -10);	
	nature[0] = new NatureObject("tree", false, false, RESOURCE_WOOD, 100, treegap);
	nature[1] = new NatureObject("gold", false, false, RESOURCE_GOLD, 100, goldgap);

	srand(time(NULL));

	for(int i = 0; i < size->x; i++)
		for(int j = 0; j < size->y; j++)
		{
			ushort mcn = getMCN(i, j);
			
			int r;
			
			if(terrain[mcn]->walkable)
			{
				if(PROB(70)) r = mcn;
				else if(PROB(70))
				{
					r = rand() % TERRAIN_TYPE_COUNT;
					while(!terrain[r]->walkable) r = rand() % TERRAIN_TYPE_COUNT;
				}
				else r = rand() % TERRAIN_TYPE_COUNT;
			}
			else
			{
				if(PROB(70)) r = mcn;
				else if(PROB(70))
				{
					r = rand() % TERRAIN_TYPE_COUNT;
					while(terrain[r]->walkable) r = rand() % TERRAIN_TYPE_COUNT;
				}
				else r = rand() % TERRAIN_TYPE_COUNT;
			}
				
			WarMap::terrainMap[i][j] = terrain[r];
		}

	// Eliminates isolated points and put nature objects
	for(int i = 0; i < size->x; i++)
		for(int j = 0; j < size->y; j++)
		{
			if(!hasON(i, j, WarMap::terrainMap[i][j]->id)) 
				WarMap::terrainMap[i][j] = terrain[getMCN(i, j)];
				
			if(WarMap::terrainMap[i][j]->walkable)
			{
				int count = 0;
				float cf = 0;
				
				if(i > 0 && j > 0 && (terrainMap[i - 1][j - 1]->navigable || (natureMap[i - 1][j - 1] != NULL && 
					natureMap[i - 1][j - 1]->resourceType == RESOURCE_WOOD))) count++;
				if(j > 0 && (terrainMap[i][j - 1]->navigable || (natureMap[i][j - 1] != NULL && 
					natureMap[i][j - 1]->resourceType == RESOURCE_WOOD))) count++;
				if(i < size->x - 1 && j > 0 && (terrainMap[i + 1][j - 1]->navigable || (natureMap[i + 1][j - 1] != NULL && 
					natureMap[i + 1][j - 1]->resourceType == RESOURCE_WOOD))) count++;
				if(i > 0 && (terrainMap[i - 1][j]->navigable || (natureMap[i - 1][j] != NULL && 
					natureMap[i - 1][j]->resourceType == RESOURCE_WOOD))) count++;
			
				if (count > 0) cf = 1;
            if (count > 3) cf = 1.5;

            if(PROB(cf * 43))
            	WarMap::natureMap[i][j] = nature[0];
            else
            {
            	count = 0;
				
					if(i > 0 && j > 0 && natureMap[i - 1][j - 1] != NULL && 
						natureMap[i - 1][j - 1]->resourceType == RESOURCE_GOLD) count++;
					if(j > 0 && natureMap[i][j - 1] != NULL && 
						natureMap[i][j - 1]->resourceType == RESOURCE_GOLD) count++;
					if(i < size->x - 1 && j > 0 && natureMap[i + 1][j - 1] != NULL && 
						natureMap[i + 1][j - 1]->resourceType == RESOURCE_GOLD) count++;
					if(i > 0 && natureMap[i - 1][j] != NULL && 
						natureMap[i - 1][j]->resourceType == RESOURCE_GOLD) count++;
						
					cf = sqrt(count);
					
					if(PROB(0.02 + cf * 33))
            		WarMap::natureMap[i][j] = nature[1];
            }
			
				if(WarMap::natureMap[i][j] != NULL) sourceMap[i][j] = natureMap[i][j]->source;
			}
		}
		
	ushort tileX = Res::getMiscImage(WarMap::terrainMap[0][0]->imageId)->size->x;
	ushort tileY = Res::getMiscImage(WarMap::terrainMap[0][0]->imageId)->size->y;
	
	map = 
		new IsometricMap(tileX, tileY, size->x, size->y,
			new Camera(*(drawer->screenSize), size->x * tileX / 2 - drawer->screenSize->x / 2, -drawer->screenSize->y / 2, 10, 5));

	map->setMapVisibleBounds();
}

ushort WarMap::getMCN(ushort x, ushort y)
{
	ushort neighboors[TERRAIN_TYPE_COUNT];
	
	for(int i = 0; i < TERRAIN_TYPE_COUNT; i++) neighboors[i] = 0;

	if(x > 0 && y > 0 && TERRAINNOTNULL(x - 1, y - 1)) neighboors[WarMap::terrainMap[x - 1][y - 1]->id]++;
	if(x > 0 && TERRAINNOTNULL(x - 1, y)) neighboors[WarMap::terrainMap[x - 1][y]->id]++;
	if(x > 0 && y < size->y - 1 && TERRAINNOTNULL(x - 1, y + 1)) neighboors[WarMap::terrainMap[x - 1][y + 1]->id]++;
	if(y > 0 && TERRAINNOTNULL(x, y - 1)) neighboors[WarMap::terrainMap[x][y - 1]->id]++;
	if(x < size->x - 1 && y > 0 && TERRAINNOTNULL(x + 1, y - 1)) neighboors[WarMap::terrainMap[x + 1][y - 1]->id]++;
	if(x < size->x - 1 && TERRAINNOTNULL(x + 1, y)) neighboors[WarMap::terrainMap[x + 1][y]->id]++;
	if(x < size->x - 1 && y < size->y - 1 && TERRAINNOTNULL(x + 1, y + 1)) neighboors[WarMap::terrainMap[x + 1][y + 1]->id]++;
	if(y < size->y - 1 && TERRAINNOTNULL(x, y + 1)) neighboors[WarMap::terrainMap[x][y + 1]->id]++;

	ushort dominant = 0;
	for(int i = 1; i < TERRAIN_TYPE_COUNT; i++) 
		if(neighboors[i] > neighboors[dominant]) 
			dominant = i;

	return dominant;
}

bool WarMap::hasN(ushort x, ushort y, ushort type)
{
	bool has = false;

	if(x > 0 && y > 0 && TERRAINEQUAL(x - 1, y - 1, type)) has = true;
	if(x > 0 && TERRAINEQUAL(x - 1, y, type)) has = true;
	if(x > 0 && y < size->y - 1 && TERRAINEQUAL(x - 1, y + 1, type)) has = true;
	if(y > 0 && TERRAINEQUAL(x, y - 1, type)) has = true;
	if(x < size->x - 1 && y > 0 && TERRAINEQUAL(x + 1, y - 1, type)) has = true;
	if(x < size->x - 1 && TERRAINEQUAL(x + 1, y, type)) has = true;
	if(x < size->x - 1 && y < size->y - 1 && TERRAINEQUAL(x + 1, y + 1, type)) has = true;
	if(y < size->y - 1 && TERRAINEQUAL(x, y + 1, type)) has = true;

	return has;
}

bool WarMap::hasNatureN(ushort x, ushort y, ushort type)
{
	bool has = false;

	if(x > 0 && y > 0 && NATUREEQUAL(x - 1, y - 1, type)) has = true;
	if(x > 0 && NATUREEQUAL(x - 1, y, type)) has = true;
	if(x > 0 && y < size->y - 1 && NATUREEQUAL(x - 1, y + 1, type)) has = true;
	if(y > 0 && NATUREEQUAL(x, y - 1, type)) has = true;
	if(x < size->x - 1 && y > 0 && NATUREEQUAL(x + 1, y - 1, type)) has = true;
	if(x < size->x - 1 && NATUREEQUAL(x + 1, y, type)) has = true;
	if(x < size->x - 1 && y < size->y - 1 && NATUREEQUAL(x + 1, y + 1, type)) has = true;
	if(y < size->y - 1 && NATUREEQUAL(x, y + 1, type)) has = true;

	return has;
}

bool WarMap::hasON(ushort x, ushort y, ushort type)
{
	bool has = false;

	if(x > 0 && TERRAINEQUAL(x - 1, y, type)) has = true;
	if(y > 0 && TERRAINEQUAL(x, y - 1, type)) has = true;
	if(x < size->x - 1 && TERRAINEQUAL(x + 1, y, type)) has = true;
	if(y < size->y - 1 && TERRAINEQUAL(x, y + 1, type)) has = true;

	return has;
}

bool WarMap::hasNatureON(ushort x, ushort y, ushort type)
{
	bool has = false;

	if(x > 0 && NATUREEQUAL(x - 1, y, type)) has = true;
	if(y > 0 && NATUREEQUAL(x, y - 1, type)) has = true;
	if(x < size->x - 1 && NATUREEQUAL(x + 1, y, type)) has = true;
	if(y < size->y - 1 && NATUREEQUAL(x, y + 1, type)) has = true;

	return has;
}

void WarMap::initMaps(ushort X, ushort Y)
{
	size = new IntVector2(X, Y);
	WarMap::terrainMap = new Terrain**[size->x];
	WarMap::natureMap = new NatureObject**[size->x];
	WarMap::sourceMap = new ushort*[size->x];

	for(int i = 0; i < size->x; i++)
	{
		WarMap::terrainMap[i] = new Terrain*[size->y];
		WarMap::natureMap[i] = new NatureObject*[size->y];
		WarMap::sourceMap[i] = new ushort[size->y];
	}
			
	for(int i = 0; i < size->x; i++)
		for(int j = 0; j < size->y; j++)
		{
			WarMap::terrainMap[i][j] = NULL;
			WarMap::natureMap[i][j] = NULL;
			WarMap::sourceMap[i][j] = 0;
		}
}

void WarMap::update()
{
	map->camera->update(keyboard->isKeyDown(keyboard->getIndex(AGL::KEY_UP)), 
								keyboard->isKeyDown(keyboard->getIndex(AGL::KEY_RIGHT)), 
								keyboard->isKeyDown(keyboard->getIndex(AGL::KEY_DOWN)), 
								keyboard->isKeyDown(keyboard->getIndex(AGL::KEY_LEFT)), 
								*(mouse->position));
}

/*void WarMap::drawTerrain(int i, int j, int x, int y)
{
	IntVector2 pos(x, y);
	
	//if(natureMap[i][j] != NULL)
	//	drawer->draw(Res::getMiscImage(terrain[4]->imageId), pos);
	//else
	drawer->draw(Res::getMiscImage(terrainMap[i][j]->imageId), pos);
}

void WarMap::drawObjects(int i, int j, int x, int y)
{	
	if(natureMap[i][j] != NULL)
	{ 
		IntVector2 pos(x + natureMap[i][j]->imageGap.x, y + natureMap[i][j]->imageGap.y);
		drawer->draw(Res::getMiscImage(natureMap[i][j]->imageId), pos);
	}
}

void WarMap::draw()
{
	map->forEachVisible(drawTerrain);
	map->forEachVisible(drawObjects);
}*/

