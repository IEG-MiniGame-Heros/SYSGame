#ifndef SYS_ENTITY_MANAGER
#define SYS_ENTITY_MANAGER

#include "cocos2d.h"
#include "BaseEntity.h"

#define EM (EntityManager::instance())

USING_NS_CC;

class Hero;

class EntityManager
{
public:
	EntityManager();
	~EntityManager();

	static EntityManager& instance();

	CCArray* getAllEntities() const;

	Hero* addAHero(CCPoint pos);
	bool removeAHero(Hero* pHero);

	/// Find Entity Begin
	////////////////////////
	
	/** 
	 * 寻找范围内第一个Entity
	 * @param pMe	中心点
	 * @param range 范围
	 * @param type	类型
	 */
	BaseEntity* findEntityInRange(BaseEntity* pMe, float range, EEntityType type);

	/** 
	 * 寻找范围内所有的Entity
	 * @see findNearestEntityInRange(BaseEntity* pMe, float range, EEntityType type)
	 */
	CCArray* findAllEntitiesInRange(BaseEntity* pMe, float range, EEntityType type);

	/** 
	 * 寻找范围内没有加入队列的英雄
	 */
	Hero* findHeroNotInQueue(BaseEntity* pMe, float range);

	/// Find Entity End

protected:

	CCArray* m_pAllEntities;
};

#endif