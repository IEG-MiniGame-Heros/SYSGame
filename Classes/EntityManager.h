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
	 * Ѱ�ҷ�Χ�ڵ�һ��Entity
	 * @param pMe	���ĵ�
	 * @param range ��Χ
	 * @param type	����
	 */
	BaseEntity* findEntityInRange(BaseEntity* pMe, float range, EEntityType type);

	/** 
	 * Ѱ�ҷ�Χ�����е�Entity
	 * @see findNearestEntityInRange(BaseEntity* pMe, float range, EEntityType type)
	 */
	CCArray* findAllEntitiesInRange(BaseEntity* pMe, float range, EEntityType type);

	/** 
	 * Ѱ�ҷ�Χ��û�м�����е�Ӣ��
	 */
	Hero* findHeroNotInQueue(BaseEntity* pMe, float range);

	/// Find Entity End

protected:

	CCArray* m_pAllEntities;
};

#endif