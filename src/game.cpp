#include <stdlib.h>
#include "agl/game.h"
#include "agl/drawer.h"

#include "agl/sound.h"
#include "agl/music.h"
#include "agl/joystick.h"
#include "agl/vector2.h"
#include "agl/intvector2.h"
#include "agl/gameobject.h"
#include "agl/support.h"
#include "agl/color.h"
#include "match.h"
#include "smatch.h"
#include "mmatch.h"
#include "options.h"

using namespace AGL;

// Game States
#define GS_INITIALIZING 0
#define GS_MATCH 1

bool debug;

Game* game = NULL;
Drawer* drawer = NULL;
Keyboard* keyboard = NULL;
Mouse* mouse = NULL;

Options* options;
unsigned char gameState;
Match* match;

void initialize()
{
	game = new AGL::Game;
	options = new Options();
	drawer = new Drawer(*(options->screenSize));
	
	game->showMouse(true);
	keyboard = new Keyboard(true, true, true, true, true, true);
	mouse = new Mouse;
	
	gameState = GS_INITIALIZING;
}

void loadContent()
{

}

void update()
{
	game->update(keyboard, mouse);
		
	if(debug && game->gameCounter % 60 == 0) printf("FPS: %f\n", game->getFps(1));
	
	if(keyboard->isKeyPressed(keyboard->getIndex(AGL::KEY_ESC))) game->setQuit(true);
	if(keyboard->isKeyDown(keyboard->getIndex(AGL::KEY_LEFTCONTROL)) &&
		keyboard->isKeyPressed(keyboard->getIndex(AGL::KEY_ENTER))) 
		drawer->setScreen(*(options->screenSize), !drawer->fullScreen);

	if(gameState == GS_MATCH)
	{
		match->update();
	}
	else if(gameState == GS_INITIALIZING)
	{		
		delete match;
		match = new SMatch(drawer, game, keyboard, mouse, options);
		gameState = GS_MATCH;
	}
}

void draw()
{
	drawer->clearScreen(options->backgroundColor);

	if(gameState == GS_MATCH)
	{
		match->draw();
	}	
	else if(gameState == GS_INITIALIZING)
	{
	
	}

	drawer->updateScreen();
}

void unloadContent()
{
	game->end();
}

/// Main method, initializes the program
int main(int argc, char *argv[])
{	
	initialize();
	
	if(argc > 1 && AGL::Format::compareChars(argv[1], (char*) "-d")) debug = true;
	else debug = false;
	
	loadContent();
	game->runFixedFps(update, draw, 60);
	unloadContent();

	return 0;
}

