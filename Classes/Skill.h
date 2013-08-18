#ifndef SYS_SKILL
#define SYS_SKILL

#include "cocos2d.h"

USING_NS_CC;

class Character;
class Effect;

/** 
 * 统一改成了远程攻击
 */
class Skill : public CCNode
{
public:
	Skill() {}
	Skill(int id);

	static Skill* create(int SkillID);

	virtual void onEnter();
	virtual void onExit();

	/** 
	 * @brief 检测到是否有人在攻击范围内
	 */
	bool shouldAttack();

	virtual void attack();
	virtual void onUpdate(float dt);

	bool isEnable() const;
	void setEnable(bool flag);

protected:

	int			m_iSkillID;			// 技能ID，对应EffectID
	bool		m_bIsEnable;		// 是否开启此技能
	int			m_iDamage;			// 伤害
	float		m_fAttackRange;		// 判定应该攻击范围
	float		m_fHitRange;		// 判定命中范围	
	float		m_fCoolTime;		// 冷却时间
	float		m_fElapseTime;		// 已经过去的时间
	float		m_bIsAttacking;		// 是否正在攻击中

	Character*	m_pOwner;			// 这个技能的所有者
	Character*	m_pTarget;			// 攻击对象的指针缓存
	Effect*		m_pEffect;			// 特效指针

	float		m_fAttackSpeed;		// 攻击速度

};
#endif