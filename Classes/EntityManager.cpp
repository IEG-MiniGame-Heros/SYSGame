#include "EntityManager.h"
#include "Hero.h"
#include "Queue.h"
#include "FirstStage.h"
#include "GameInfo.h"

EntityManager& EntityManager::instance()
{
	static EntityManager inst;
	return inst;
}

EntityManager::EntityManager()
{
	m_pAllEntities = CCArray::create();
	m_pAllEntities->retain();
}

EntityManager::~EntityManager()
{
	m_pAllEntities->release();
}

Hero* EntityManager::addAHero(CCPoint pos)
{
	if (GI.Game)
	{
		Hero* pHero = Hero::create(GI.PathOfHero.c_str());
		GI.Game->addChild(pHero);
		pHero->setPosition(pos);
		m_pAllEntities->addObject(pHero);
		return pHero;
	}

	return NULL;
}

bool EntityManager::removeAHero(Hero* pHero)
{
	if (pHero && GI.Game)
	{
		GI.Game->removeChild(pHero);
		m_pAllEntities->removeObject(pHero);
		return true;
	}
	return false;
}

CCArray* EntityManager::getAllEntities() const 
{
	return m_pAllEntities;
}

BaseEntity* EntityManager::findEntityInRange(BaseEntity* pMe, float range, EEntityType type)
{
	BaseEntity* ret = NULL;
	float min_dist = range * range;
	CCObject* tObject;	

	CCARRAY_FOREACH(m_pAllEntities, tObject)
	{
		BaseEntity* tEntity = (BaseEntity*)(tObject);
		if (tEntity != pMe && tEntity->getType() == type)
		{
			float dist_sqrt = pMe->getPosition().getDistanceSq(tEntity->getPosition());
			if (dist_sqrt < range * range + 1e-6)
			{
				ret = tEntity;
			}
		}
	}

	return ret;
}

Hero* EntityManager::findHeroNotInQueue(BaseEntity* pMe, float range)
{
	Hero* ret = NULL;
	CCObject* tObject;	

	CCARRAY_FOREACH(m_pAllEntities, tObject)
	{
		Hero* tEntity = (Hero*)(tObject);
		if (tEntity != pMe && tEntity->getType() == ET_Hero)
		{
			// û�мӽ�������
			if (!tEntity->getQueue())
			{
				float dist_sqrt = pMe->getPosition().getDistanceSq(tEntity->getPosition());
				if (dist_sqrt < range * range + 1e-6)
				{
					ret = tEntity;
				}
			}
		}
	}

	return ret;
}

CCArray* EntityManager::findAllEntitiesInRange(BaseEntity* pMe, float range, EEntityType type)
{
	return NULL;
}