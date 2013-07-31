#include "Hero.h"
#include "GameInfo.h"

void Hero::onEnter()
{
	Character::onEnter();

	schedule(schedule_selector(Hero::onUpdate));
}

void Hero::onExit()
{
	unschedule(schedule_selector(Hero::onUpdate));

	Character::onExit();
}

void Hero::onUpdate(float dt)
{
	onMove();
}

Hero* Hero::create(const char *pszFileName)
{
	Hero *pobSprite = new Hero();
	if (pobSprite && pobSprite->initWithFile(pszFileName))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

bool Hero::init()
{
	if (!CCSprite::init())
	{
		return false;
	}

	setType(ET_Goods);
	return true;
}