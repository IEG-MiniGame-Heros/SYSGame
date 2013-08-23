#ifndef SYS_FIRE_BALL
#define SYS_FIRE_BALL

#include "Effect.h"
#include "Comm.h"

/** 
 * ��������, ���������ӵ������ǵ�Զ�̹�����Ч
 * ���Ի�һ����ͼ
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
 * ������ը����
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
 * ������Ч
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
 * ������Ч
 */
class Flash : public Effect
{
public:

	void onEnter();
	void onExit();
	static Flash* create(const char *pszFileName);
};

/** 
 * ������Ч
 */
class Smog : public Effect
{
public:
	void onEnter();
	void onExit();
	static Smog* create(const char *pszFileName);
};

/** 
 * ������˸��Ч
 */
class Twinkle : public Effect
{
public:
	void onEnter();
	void onExit();
	static Twinkle* create(const char *pszFileName);
};

/** 
 * ��ʾX1, X2, X3������Ч
 */
class ShowNum : public Effect
{
public:
	void onEnter();
	void onExit();

	// ���num == -1, ����X
	static ShowNum* create(const char *pszFileName);

private:
	int m_iNum;
};