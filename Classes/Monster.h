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

	void kill();

protected:

	int		m_iWalkLoopCount;		// Monster AI��·ʱ��ļ���
	int		m_iWalkDir;				// Monster AI��·�ķ���
	int		m_bIsClockWise;			// �Ƿ�˳ʱ����·
};

#endif