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
	 * �Ƴ�һ������
	 */
	void removeAnEntity(BaseEntity* entity, EEntityType);

	Hero* addAHero(CCPoint pos);
	Monster* addAMonster(CCPoint pos);
	Effect* addAnEffect(CCPoint pos, EEffectType type, CCPoint target_pos);

	/// Find Entity Begin
	////////////////////////
	
	/** 
	 * Ѱ�ҷ�Χ�ڵ�һ��Entity
	 * @param pMe	���ĵ�
	 * @param range ��Χ
	 * @param type	����
	 */
	BaseEntity* findEntityInRange(BaseEntity* pMe, float range, EEntityType type);

	BaseEntity* findEntityInRange(CCPoint MyPos, BaseEntity* pMe, float range, EEntityType type);


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

	CCArray* getArrayByType(EEntityType type) const;

protected:

	CCArray* m_pAllHeros;
	CCArray* m_pAllMonsters;
	CCArray* m_pAllGoods;
	CCArray* m_pAllEffects;
};

#endif