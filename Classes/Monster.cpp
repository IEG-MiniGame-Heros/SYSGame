#include "Monster.h"
#include "GameInfo.h"

Monster::Monster()
{
	setType(ET_Monster);
}

void Monster::onEnter()
{
	Character::onEnter();

	setCurSpeed(GI.MonsterInitSpeed);
	setMaxSpeed(GI.MonsterMaxSpeed);
	setCurHealth(100);
	setMaxHealth(100);
}

void Monster::onExit()
{
	Character::onExit();
}

void Monster::onUpdate(float dt)
{

}

Monster* Monster::create(const char *pszFileName)
{
	Monster *pobSprite = new Monster();
	if (pobSprite && pobSprite->initWithFile(pszFileName))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}