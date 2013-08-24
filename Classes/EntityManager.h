#ifndef SYS_ENTITY_MANAGER
#define SYS_ENTITY_MANAGER

#include "cocos2d.h"
#include "BaseEntity.h"
#include "Comm.h"

#define EM (EntityManager::instance())

USING_NS_CC;

class Hero;
class Monster;
class Character;
class ThrowableObj;
class Effect;
class Goods;

class EntityManager
{
public:
	EntityManager();
	~EntityManager();

	static EntityManager& instance();

	//CCArray* getAllEntities() const;
	void removeAll();

	/** 
	 * 移除一个对象
	 */
	void removeAnEntity(BaseEntity* entity, EEntityType);

	Hero* addAHero(CCPoint pos);
	Monster* addAMonster(CCPoint pos);
	Effect* addAnEffect(CCPoint pos, EEffectType type, CCPoint target_pos);
	Effect* addAnEffectOnCharacter(EEffectType type, Character* pCha);
	Effect* addANumberOverCharacter(Character* pCha, int num);
	Goods* addAGoods(CCPoint pos, EGoodType type);

	// 增加一个进攻特效（重整一下进攻特效）
	Effect*	addAnAttackEffect(CCPoint pos, EEffectType type, EEntityType enemy_type, int damage, CCPoint target_pos);

	// 增加指定英雄 Add By super 20130824
	Hero* addAppointedHero(CCPoint pos);
	
	/** 
	 * 需要同时生成若干个金币
	 */
	void addCoins(CCPoint pos, int num);

	/// Find Entity Begin
	////////////////////////
	
	/** 
	 * 寻找范围内第一个Entity
	 * @param pMe	中心点
	 * @param range 范围
	 * @param type	类型
	 */
	BaseEntity* findEntityInRange(BaseEntity* pMe, float range, EEntityType type);

	BaseEntity* findNearestEntityInRange(BaseEntity* pMe, float range, EEntityType type);


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


	CCArray* getArrayByType(EEntityType type) const;

protected:

	CCArray* m_pAllHeros;
	CCArray* m_pAllMonsters;
	CCArray* m_pAllGoods;
	CCArray* m_pAllEffects;
};

#endif