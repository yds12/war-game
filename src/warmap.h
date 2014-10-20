#ifndef _WARGAME_WARMAP_H
#define _WARGAME_WARMAP_H

#include <math.h>
#include <string>

#include "agl/drawer.h"
#include "agl/game.h"
#include "agl/mouse.h"
#include "agl/keyboard.h"
#include "agl/mapping/isometricmap.h"

#include "support.h"
#include "terrain.h"
#include "options.h"
#include "natureobject.h"

using namespace std;
using namespace AGL;

#define TERRAIN_TYPE_COUNT 4
#define NATURE_TYPE_COUNT 2

/// WarMap class
class WarMap
{
	private:	
		static Drawer* drawer;
		static Game* game;
		static Keyboard* keyboard;
		static Mouse* mouse;
		static Options* options;
		
		static Terrain** terrain;
		static NatureObject** nature;
		
		// Most common neighbors
		ushort getMCN(ushort x, ushort y);
		
		// Has neighbor
		bool hasN(ushort x, ushort y, ushort type);
		
		// Has neighbor (nature)
		bool hasNatureN(ushort x, ushort y, ushort type);
		
		// Has ortogonal neighbor
		bool hasON(ushort x, ushort y, ushort type);
		
		// Has ortogonal neighbor (nature)
		bool hasNatureON(ushort x, ushort y, ushort type);
		
		void initMaps(ushort X, ushort Y);
		
	public:		
		IntVector2* size;
		static ushort** sourceMap;
		static Terrain*** terrainMap;
		static NatureObject*** natureMap;
		IsometricMap* map;
	
		WarMap(Drawer* drawer, Game* game, Keyboard* keyboard, Mouse* mouse, Options* opt);
		
		void load(char* file);
		void loadRandom();
		void update();
		//static void drawTerrain(int i, int j, int x, int y);
		//static void drawObjects(int i, int j, int x, int y);
		//void draw();
};

#endif

