#include "unit.h"

Unit::Unit(UnitModel* model, ushort teamIndex, Drawer* drawer, Game* game, ushort id)
{
	this->id = id;
	this->selected = false;
	basicAnimationSet = new Animation*[BASIC_ANIMATION_COUNT];

	this->drawer = drawer;
	this->game = game;
	this->model = model;
	this->teamIndex = teamIndex;
	currentAnimation = ANIMATION_STAND_FRONT;

	for(int i = 0; i < BASIC_ANIMATION_COUNT; i++)
	{
		int imageIndex = Res::addImage(model->animationFiles[i], model->imageTeamColor, teamIndex);
		basicAnimationSet[i] = new Animation(Res::getImage(imageIndex, teamIndex), drawer, 3, 1);
	}
	
	hp = model->maxHp;
}

void Unit::update()
{
	basicAnimationSet[currentAnimation]->update(0.15, game);
}

void Unit::draw(IntVector2 position)
{
	basicAnimationSet[currentAnimation]->draw(position);
}

float Unit::getPercentualHp()
{
	return (float)hp / model->maxHp;
}

