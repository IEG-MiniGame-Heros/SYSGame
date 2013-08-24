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
	ThrowableObj(EEffectType eft, EEntityType enemy_type, int damage) 
		: m_EffectType(eft), m_iEnemyType(enemy_type), m_iDamage(damage) {}

	void onUpdate(float dt);

	void onEnter();
	void onExit();

	static ThrowableObj* create(const char *pszFileName, EEffectType eft, EEntityType enemy_type, int damage);

private:
	EEffectType			m_EffectType;
	int					m_iDamage;
	float				m_fHitRange;
	EEntityType			m_iEnemyType;
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

/** 
 * 闪光特效
 */
class Flash : public Effect
{
public:

	void onEnter();
	void onExit();
	static Flash* create(const char *pszFileName);
};

/** 
 * 烟雾特效
 */
class Smog : public Effect
{
public:
	void onEnter();
	void onExit();
	static Smog* create(const char *pszFileName);
};

/** 
 * 星星闪烁特效
 */
class Twinkle : public Effect
{
public:
	void onEnter();
	void onExit();
	static Twinkle* create(const char *pszFileName);
};

/** 
 * 显示X1, X2, X3数字特效
 */
class ShowNum : public Effect
{
public:
	void onEnter();
	void onExit();

	// 如果num == -1, 代表X
	static ShowNum* create(const char *pszFileName);

private:
	int m_iNum;
};