#include "options.h"

Options::Options()
{
	// Match Settings ####
	
	myIndex = 0;
	multiplayer = false;
	numberOfPlayers = 2;
	
	colors = new Color[numberOfPlayers];
	
	srand(time(NULL));
	
	SETCOLOR(colors[0], rand()%255, rand()%255, rand()%255);
	SETCOLOR(colors[1], rand()%255, rand()%255, rand()%255);
	
	// ###################

	screenSize = new IntVector2(1280, 800);
	
	musicOn = true;
	soundOn = true;
	musicVolume = 1.0;
	soundVolume = 1.0;

	maxSelection = 40;
	populationLimit = 1000;

	SETCOLOR(farColor, 40, 40, 40);
	SETCOLOR(backgroundColor, 0, 0, 0);
	SETCOLOR(selectionRectangleColor, 0, 255, 0);
	selectionRectangleAlpha = 200;
}

