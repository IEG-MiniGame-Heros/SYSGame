#ifndef SYS_MONSTER
#define SYS_MONSTER

#include "Character.h"

class Frozen;

class Monster : public Character
{
public:
	Monster();

	virtual void onEnter();

	virtual void onExit();

	bool onMove();

	virtual void onUpdate(float dt);

	void setForceToStop(bool isStop);

	void setDropItemAfterDeath(bool shouldDrop);

	void kill();

	void setFrozen(bool frozen);

	static Monster* create(const char *pszFileName);

protected:

	int		m_iWalkLoopCount;		// Monster AI走路时候的计数
	int		m_iWalkDir;				// Monster AI走路的方向
	int		m_bIsClockWise;			// 是否顺时针走路
	bool	m_bForceToStop;			// 强制停止
	bool	m_bDropItemAfterDeath;	// 死后掉物品
	bool	m_bIsFrozen;			// 是否被冰冻了
	Frozen*	m_pFrozenEft;			// 冰冻特效指针
};

#endif