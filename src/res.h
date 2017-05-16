#ifndef _WARGAME_RES_H
#define _WARGAME_RES_H

#include "agl/image.h"
#include "agl/sound.h"
#include "agl/format.h"
#include "agl/graphics.h"
#include "options.h"

using namespace AGL;

#define MAX_PATHNAME_LENGTH 256

#define ANIMATION_PATH "data/animation/"
#define NATURE_PATH "data/nature/"
#define SOUND_PATH "data/sound/"
#define MUSIC_PATH "data/music/"
#define DATA_PATH "data/"

/// Resource controller class
class Res
{
	private:
		static Image*** imageTable;
		static Image** miscImageTable;
		static Image** darkMiscImageTable;
		static Sound** soundTable;		
		static unsigned short imageCount;
		static unsigned short miscImageCount;
		static unsigned short soundCount;
		static unsigned short maxImages;
		static unsigned short maxMiscImages;
		static unsigned short maxSounds;
		static unsigned char maxColors;
		static Color* colors;
		static Graphics* gph;
		static Options* options;
		static string* imageFiles;
		static string* miscImageFiles;
		static string* soundFiles;

	public:
		static void initialize(unsigned char _maxColors, unsigned short _maxImages, unsigned short _maxMiscImages, unsigned short _maxSounds, Options* opt);
		static void setColor(unsigned short index, unsigned char red, unsigned char green, unsigned char blue);
		static void setColor(unsigned short index, Color color);
		static int addImage(char* file, Color teamColor, unsigned char colorIndex);
		static int addMiscImage(char* file);
		static int addMiscImage(char* file, bool addDark);
		static int addMiscImage(Image* image);
		static int addSound(char* file);
		static int addMusic(char* file);
		static Sound* getSound(unsigned short index);
		static Sound* getMusic(unsigned short index);
		static Image* getImage(unsigned short index, unsigned char colorIndex);
		static Image* getMiscImage(unsigned short index);
		static Image* getMiscImage(unsigned short index, bool dark);
		static void clear();
		static void info();
};

#endif

