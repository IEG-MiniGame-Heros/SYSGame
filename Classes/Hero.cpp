#include "Hero.h"
#include "Queue.h"
#include "EntityManager.h"
#include "GameInfo.h"

void Hero::onEnter()
{
	Character::onEnter();

	setCurSpeed(GI.HeroInitSpeed);
	setMaxSpeed(GI.HeroMaxSpeed);
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

	// 检查有没有英雄要“吃”
	if (m_pQueue && m_pQueue->getHead() == this)
	{
		BaseEntity* entity = EM.findHeroNotInQueue(this, GI.RangeToPickupHero);
		if (entity != NULL)
		{
			m_pQueue->appendCharacter((Character*)(entity));
		}
	}

	
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

Hero::Hero()
{
	setType(ET_Hero);
}