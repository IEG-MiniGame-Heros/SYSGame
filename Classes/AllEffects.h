#ifndef SYS_FIRE_BALL
#define SYS_FIRE_BALL

#include "Effect.h"

/** 
 * ��������, ���������ӵ������ǵ�Զ�̹�����Ч
 * ���Ի�һ����ͼ
 */
class ThrowableObj : public Effect
{
public:
	void onEnter();
	void onExit();

	static ThrowableObj* create(const char *pszFileName);

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

/** 
 * ������Ч
 */
class Frozen : public Effect
{
public:

	void onEnter();
	void onExit();
	static Frozen* create(const char *pszFileName);
};