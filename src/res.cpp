#include "res.h"

Image*** Res::imageTable;
Image** Res::miscImageTable;
Image** Res::darkMiscImageTable;
Sound** Res::soundTable;		
unsigned short Res::imageCount;
unsigned short Res::miscImageCount;
unsigned short Res::soundCount;
unsigned short Res::maxImages;
unsigned short Res::maxMiscImages;
unsigned short Res::maxSounds;
unsigned char Res::maxColors;
Color* Res::colors;
Graphics* Res::gph;
Options* Res::options;
string* Res::imageFiles;
string* Res::miscImageFiles;
string* Res::soundFiles;

void Res::initialize(unsigned char _maxColors, unsigned short _maxImages, unsigned short _maxMiscImages, unsigned short _maxSounds, Options* opt)
{
	options = opt;
	maxImages = _maxImages;
	maxMiscImages = _maxMiscImages;
	maxSounds = _maxSounds;
	maxColors = _maxColors;

	imageFiles = new string[maxImages];
	miscImageFiles = new string[maxMiscImages];
	soundFiles = new string[maxSounds];

	imageTable = new Image**[maxImages];	
	for(int i = 0; i < maxImages; i++)
	{
		imageFiles[i] = "";
		imageTable[i] = new Image*[maxColors];		
		for(int j = 0; j < maxColors; j++) imageTable[i][j] = NULL;
	}
	
	soundTable = new Sound*[maxSounds];	
	for(int i = 0; i < maxSounds; i++) 
	{		
		soundFiles[i] = "";
		soundTable[i] = NULL;
	}
		
	miscImageTable = new Image*[maxMiscImages];
	darkMiscImageTable = new Image*[maxMiscImages];	
	for(int i = 0; i < maxMiscImages; i++) 
	{
		miscImageFiles[i] = "";
		miscImageTable[i] = NULL;
		darkMiscImageTable[i] = NULL;
	}
	
	imageCount = 0;
	miscImageCount = 0;
	soundCount = 0;
	
	colors = new Color[maxColors];
	for(int i = 0; i < maxColors; i++)
	{
		colors[i].red = 0;
		colors[i].green = 0;
		colors[i].blue = 0;
	}
}

void Res::setColor(unsigned short index, unsigned char red, unsigned char green, unsigned char blue)
{
	colors[index].red = red;
	colors[index].green = green;
	colors[index].blue = blue;
}

void Res::setColor(unsigned short index, Color color)
{
	colors[index] = color;
}

int Res::addImage(char* file, Color teamColor, unsigned char colorIndex)
{
	char path[MAX_PATHNAME_LENGTH];
	sprintf(path, "%s%s", DATA_PATH, file);

	int imageIndex = imageCount;
	bool exists = false;

	for(int i = 0; i < imageCount; i++)
	{
		if(Format::compareCharString(path, imageFiles[i]) && imageTable[i][colorIndex] != NULL) 
		{
			imageIndex = i;
			exists = true;
			break;
		}
	}

	if(!exists) 
	{
		imageCount++;
		imageFiles[imageIndex] = path;
		
		Image* image = new Image(AGL_PNG, path);
		if(!COLOREQUAL(colors[colorIndex], teamColor)) gph->replaceGradient(image, teamColor, colors[colorIndex], 40);	
		imageTable[imageIndex][colorIndex] = image;		
	}
	
	return imageIndex;
}

int Res::addMiscImage(char* file)
{
	return addMiscImage(file, false);
}

int Res::addMiscImage(char* file, bool addDark)
{
	char path[MAX_PATHNAME_LENGTH];
	sprintf(path, "%s%s", DATA_PATH, file);

	int miscImageIndex = miscImageCount;
	bool exists = false;

	for(int i = 0; i < miscImageCount; i++)
	{
		if(Format::compareCharString(path, miscImageFiles[i])) 
		{
			miscImageIndex = i;
			exists = true;
			break;
		}
	}

	if(!exists) 
	{
		miscImageCount++;
		miscImageFiles[miscImageIndex] = path;
	}

	Image* image = new Image(AGL_PNG, path);
	miscImageTable[miscImageIndex] = image;

	if(addDark && darkMiscImageTable[miscImageIndex] == NULL)
	{
		Image* dark = new Image(image);
		gph->applyColorFilter(dark, options->farColor);
		darkMiscImageTable[miscImageIndex] = dark;
	}

	return miscImageIndex;
}

int Res::addMiscImage(Image* image)
{
	int miscImageIndex = miscImageCount;
	miscImageCount++;
	miscImageTable[miscImageIndex] = image;

	return miscImageIndex;
}

int Res::addSound(char* file)
{
	char path[MAX_PATHNAME_LENGTH];	
	sprintf(path, "%s%s", SOUND_PATH, file);

	int soundIndex = soundCount;
	bool exists = false;
	
	for(int i = 0; i < soundCount; i++)
	{
		if(Format::compareCharString(path, soundFiles[i])) 
		{
			soundIndex = i;
			exists = true;
			break;
		}
	}

	if(!exists) 
	{
		soundCount++;
		soundFiles[soundIndex] = path;
	}
	
	soundTable[soundIndex] = new Sound(AGL_SOUND, path);
	return soundIndex;
}

int Res::addMusic(char* file)
{
	char path[MAX_PATHNAME_LENGTH];	
	sprintf(path, "%s%s", MUSIC_PATH, file);

	int soundIndex = soundCount;
	bool exists = false;
	
	for(int i = 0; i < soundCount; i++)
	{
		if(Format::compareCharString(path, soundFiles[i])) 
		{
			soundIndex = i;
			exists = true;
			break;
		}
	}

	if(!exists) 
	{
		soundCount++;
		soundFiles[soundIndex] = path;
	}

	soundTable[soundIndex] = new Sound(AGL_MUSIC, path);
	return soundIndex;
}

Sound* Res::getSound(unsigned short index)
{
	return soundTable[index];
}

Sound* Res::getMusic(unsigned short index)
{
	return soundTable[index];
}

Image* Res::getImage(unsigned short index, unsigned char colorIndex)
{
	return imageTable[index][colorIndex];
}

Image* Res::getMiscImage(unsigned short index)
{
	return miscImageTable[index];
}

Image* Res::getMiscImage(unsigned short index, bool dark)
{
	if(dark)
		return darkMiscImageTable[index];
	else
		return miscImageTable[index];
}

void Res::clear()
{
	for(int i = 0; i < imageCount; i++)
		for(int j = 0; j < maxColors; j++)
			delete imageTable[i][j];
			
	for(int i = 0; i < maxSounds; i++)
		delete soundTable[i];
			
	for(int i = 0; i < maxMiscImages; i++)
		delete miscImageTable[i];
}

void Res::info()
{
	printf("\nResource Controller information:\n");
	printf("Images: %d\n", imageCount);
	printf("Misc Images: %d\n", miscImageCount);
	printf("Sounds: %d\n", soundCount);
	printf("-----------------------------------\n");
}

