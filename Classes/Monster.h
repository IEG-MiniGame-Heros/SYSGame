#ifndef SYS_MONSTER
#define SYS_MONSTER

#include "Character.h"

class Monster : public Character
{
public:
	Monster();

	virtual void onEnter();

	virtual void onExit();

	virtual void onUpdate(float dt);

	void setForceToStop(bool isStop);

	void kill();

	static Monster* create(const char *pszFileName);

protected:

	int		m_iWalkLoopCount;		// Monster AI走路时候的计数
	int		m_iWalkDir;				// Monster AI走路的方向
	int		m_bIsClockWise;			// 是否顺时针走路
	bool	m_bForceToStop;			// 强制停止
};

#endif