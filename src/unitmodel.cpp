#include "unitmodel.h"

#define SETANIMATION(a,b) sprintf(animationFiles[a], "%s%s.png", "animation/", b);

UnitModel::UnitModel()
{
	
}

void UnitModel::load()
{
	imageGap = new IntVector2(-12, -48);
	animationFiles = new char*[BASIC_ANIMATION_COUNT];
	
	for(int i = 0; i < BASIC_ANIMATION_COUNT; i++) animationFiles[i] = new char[MAX_PATHNAME_LENGTH];
	
	SETCOLOR(imageTeamColor, 0, 0, 128);
	
	SETANIMATION(ANIMATION_STAND_BACK, "lancer-mb");
	SETANIMATION(ANIMATION_STAND_RIGHT, "lancer-mr");
	SETANIMATION(ANIMATION_STAND_FRONT, "lancer2-mf");
	SETANIMATION(ANIMATION_STAND_LEFT, "lancer-ml");
	SETANIMATION(ANIMATION_MOVE_BACK, "lancer-mb");
	SETANIMATION(ANIMATION_MOVE_RIGHT, "lancer-mr");
	SETANIMATION(ANIMATION_MOVE_FRONT, "lancer-mf");
	SETANIMATION(ANIMATION_MOVE_LEFT, "lancer-ml");
	SETANIMATION(ANIMATION_ATTACK_BACK, "lancer-mb");
	SETANIMATION(ANIMATION_ATTACK_RIGHT, "lancer-mr");
	SETANIMATION(ANIMATION_ATTACK_FRONT, "lancer-mf");
	SETANIMATION(ANIMATION_ATTACK_LEFT, "lancer-ml");
	
	//for(int i = 0; i < BASIC_ANIMATION_COUNT; i++)
		//printf("%s\n", animationFiles[i]);
	
	isBuilding = false;
	sight = 20;
	maxHp = 100;
	/*animationFiles[ANIMATION_STAND_BACK] = (char*)"lancer-mb.agr";
	animationFiles[ANIMATION_STAND_RIGHT] = (char*)"lancer-mr.agr";
	animationFiles[ANIMATION_STAND_FRONT] = (char*)"lancer-mf.agr";
	animationFiles[ANIMATION_STAND_LEFT] = (char*)"lancer-ml.agr";
	animationFiles[ANIMATION_MOVE_BACK] = (char*)"lancer-mb.agr";
	animationFiles[ANIMATION_MOVE_RIGHT] = (char*)"lancer-mr.agr";
	animationFiles[ANIMATION_MOVE_FRONT] = (char*)"lancer-mf.agr";
	animationFiles[ANIMATION_MOVE_LEFT] = (char*)"lancer-ml.agr";
	animationFiles[ANIMATION_ATTACK_BACK] = (char*)"lancer-mb.agr";
	animationFiles[ANIMATION_ATTACK_RIGHT] = (char*)"lancer-mr.agr";
	animationFiles[ANIMATION_ATTACK_FRONT] = (char*)"lancer-mf.agr";
	animationFiles[ANIMATION_ATTACK_LEFT] = (char*)"lancer-ml.agr";*/
}

void UnitModel::load(char* file)
{
	
}

