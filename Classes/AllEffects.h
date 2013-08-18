#ifndef SYS_FIRE_BALL
#define SYS_FIRE_BALL

#include "Effect.h"
#include "Comm.h"

/** 
 * 可抛掷物, 包括火球、子弹、星星等远程攻击特效
 * 可以换一下贴图
 */
class ThrowableObj : public Effect
{
public:
	ThrowableObj() {}
	ThrowableObj(EEffectType eft) : m_EffectType(eft) {}

	void onEnter();
	void onExit();

	static ThrowableObj* create(const char *pszFileName, EEffectType eft);

private:
	EEffectType			m_EffectType;
};
#endif


/** 
 * 死亡后爆炸动画
 */
class Explosion : public Effect
{
public:

	void onEnter();
	void onExit();

	static Explosion* create(const char *pszFileName);
};

class Monster;

/** 
 * 冰冻特效
 */
class Frozen : public Effect
{
public:

	void onEnter();
	void onExit();

	void frozenStart(Monster* pMonster);
	void frozenEnd();

	void stopFrozen();
	
	static Frozen* create(const char *pszFileName);

private:
	Monster*		m_pMonster;
};