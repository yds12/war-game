
#include "natureobject.h"

NatureObject::NatureObject(char* file, bool _walkable, bool _navigable, unsigned short resType, unsigned short _source, IntVector2 _imageGap)
{
	imageGap = _imageGap;
	resourceType = resType;
	source = _source;
	navigable = _navigable;
	walkable = _walkable;
	
	char path[MAX_PATHNAME_LENGTH];
	sprintf(path, "%s%s.png", "nature/", file);
	imageId = Res::addMiscImage(path, true);
	id = imageId;
}

