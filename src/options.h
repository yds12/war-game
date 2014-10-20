#ifndef _WARGAME_OPTIONS_H
#define _WARGAME_OPTIONS_H

#include "agl/support.h"
#include "agl/intvector2.h"

using namespace AGL;

/// Options class
class Options
{
	private:
	public:
		// Match settings ########
		
		bool multiplayer;
		ushort numberOfPlayers;
		Color* colors;
		ushort myIndex;
		
		// #######################
	
		IntVector2* screenSize;
		
		bool musicOn;
		bool soundOn;
		float musicVolume;
		float soundVolume;
		Color backgroundColor;
		Color farColor;
		Color selectionRectangleColor;
		Uint8 selectionRectangleAlpha;
		
		unsigned short maxSelection;
		unsigned short populationLimit;
	
		Options();		
};

#endif

