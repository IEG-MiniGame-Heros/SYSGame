#ifndef SYS_MONSTER
#define SYS_MONSTER

#include "Character.h"

class Frozen;

class Monster : public Character
{
public:
	Monster();
	Monster(int ID);

	virtual void onEnter();

	virtual void onExit();

	bool onMove();

	virtual void onUpdate(float dt);

	void setForceToStop(bool isStop);

	void setDropItemAfterDeath(bool shouldDrop);

	void kill();

	void setFrozen(bool frozen);

	static Monster* create(const char *pszFileName, int MonsID);

protected:

	int		m_iMonsterID;			// ����ID
	int		m_iWalkLoopCount;		// Monster AI��·ʱ��ļ���
	int		m_iWalkDir;				// Monster AI��·�ķ���
	int		m_bIsClockWise;			// �Ƿ�˳ʱ����·
	bool	m_bForceToStop;			// ǿ��ֹͣ
	bool	m_bDropItemAfterDeath;	// �������Ʒ
	bool	m_bIsFrozen;			// �Ƿ񱻱�����
	Frozen*	m_pFrozenEft;			// ������Чָ��
};

#endif