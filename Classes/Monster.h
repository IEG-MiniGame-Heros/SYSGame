#ifndef SYS_MONSTER
#define SYS_MONSTER

#include "Character.h"

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

	static Monster* create(const char *pszFileName);

protected:

	int		m_iWalkLoopCount;		// Monster AI��·ʱ��ļ���
	int		m_iWalkDir;				// Monster AI��·�ķ���
	int		m_bIsClockWise;			// �Ƿ�˳ʱ����·
	bool	m_bForceToStop;			// ǿ��ֹͣ
	bool	m_bDropItemAfterDeath;	// �������Ʒ
	bool	m_bIsFrozen;			// �Ƿ񱻱�����
};

#endif