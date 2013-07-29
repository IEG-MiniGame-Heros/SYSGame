#include "EntityManager.h"
#include "Hero.h"
#include "FirstStage.h"
#include "GameInfo.h"

EntityManager& EntityManager::instance()
{
	static EntityManager inst;
	return inst;
}

EntityManager::EntityManager()
{
	m_pAllCharacters = CCArray::create();
	m_pAllCharacters->retain();
}

EntityManager::~EntityManager()
{
	m_pAllCharacters->release();
}

Hero* EntityManager::addAHero(CCPoint pos)
{
	if (GI.Game)
	{
		Hero* pHero = Hero::create(GI.PathOfHero.c_str());
		GI.Game->addChild(pHero);
		pHero->setPosition(pos);
		m_pAllCharacters->addObject(pHero);
		return pHero;
	}

	return NULL;
}

bool EntityManager::removeAHero(Hero* pHero)
{
	if (pHero && GI.Game)
	{
		GI.Game->removeChild(pHero);
		m_pAllCharacters->removeObject(pHero);
		return true;
	}
	return false;
}