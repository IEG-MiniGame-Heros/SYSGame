#ifndef SYS_ENTITY_MANAGER
#define SYS_ENTITY_MANAGER

#include "cocos2d.h"
#include "BaseEntity.h"
#include "Comm.h"

#define EM (EntityManager::instance())

USING_NS_CC;

class Hero;
class Monster;
class Effect;

class EntityManager
{
public:
	EntityManager();
	~EntityManager();

	static EntityManager& instance();

	//CCArray* getAllEntities() const;

	/** 
	 * 移除一个对象
	 */
	void removeAnEntity(BaseEntity* entity, EEntityType);

	Hero* addAHero(CCPoint pos);
	Monster* addAMonster(CCPoint pos);
	Effect* addAnEffect(CCPoint pos, EEffectType type, CCPoint target_pos);

	/// Find Entity Begin
	////////////////////////
	
	/** 
	 * 寻找范围内第一个Entity
	 * @param pMe	中心点
	 * @param range 范围
	 * @param type	类型
	 */
	BaseEntity* findEntityInRange(BaseEntity* pMe, float range, EEntityType type);

	BaseEntity* findEntityInRange(CCPoint MyPos, BaseEntity* pMe, float range, EEntityType type);


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

	CCArray* getArrayByType(EEntityType type) const;

protected:

	CCArray* m_pAllHeros;
	CCArray* m_pAllMonsters;
	CCArray* m_pAllGoods;
	CCArray* m_pAllEffects;
};

#endif