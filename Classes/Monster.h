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

	static Monster* create(const char *pszFileName);

protected:

	int		m_iWalkLoopCount;		// Monster AI��·ʱ��ļ���
	int		m_iWalkDir;				// Monster AI��·�ķ���
	int		m_bIsClockWise;			// �Ƿ�˳ʱ����·
};

#endif