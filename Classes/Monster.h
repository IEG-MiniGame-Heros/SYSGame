#ifndef SYS_MONSTER
#define SYS_MONSTER

#include "Character.h"

const CCPoint WalkVec[4] = 
{
	CCPoint(1, 0),
	CCPoint(0, -1),
	CCPoint(-1, 0),
	CCPoint(0, 1)
};

class Monster : public Character
{
public:
	Monster();

	virtual void onEnter();

	virtual void onExit();

	virtual void onUpdate(float dt);

	static Monster* create(const char *pszFileName);

protected:

	int		m_iWalkLoopCount;		// Monster AI走路时候的计数
	int		m_iWalkDir;				// Monster AI走路的方向
	int		m_bIsClockWise;			// 是否顺时针走路
};

#endif