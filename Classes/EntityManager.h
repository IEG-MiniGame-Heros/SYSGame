#ifndef SYS_ENTITY_MANAGER
#define SYS_ENTITY_MANAGER

#include "cocos2d.h"

USING_NS_CC;

class Hero;

class EntityManager
{
public:
	EntityManager();
	~EntityManager();

	static EntityManager& instance();

	Hero* addAHero(CCPoint pos);
	bool removeAHero(Hero* pHero);

protected:

	CCArray* m_pAllCharacters;
};

#endif