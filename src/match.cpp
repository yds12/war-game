#include "match.h"

Team** Match::teams;
Drawer* Match::drawer;
Options* Match::options;
Unit*** Match::unitMap;

Match::Match(Drawer* drawer, Game* game, Keyboard* keyboard, Mouse* mouse, Options* opt)
{
	this->game = game;
	this->drawer = drawer;
	this->options = opt;
	this->keyboard = keyboard;
	this->mouse = mouse;
	
	Res::initialize(12, 1000, 1000, 1000, opt);
}

