#ifndef SYS_CHARACTER
#define SYS_CHARACTER

#include "MovingEntity.h"

class Queue;

class Character : public MovingEntity
{
public:

	virtual void onEnter();

	virtual void onExit();

	virtual bool onMove();

	virtual void onMoveDone();

	virtual void kill();

	/** 
	 * �����ĸ�����&&���ö���
	 */
	Queue* getQueue() const;
	void setQueue(Queue* pQ);

protected: 

	int			m_iCurHealth;		// ��ǰ����ֵ
	int			m_iMaxHealth;		// �������ֵ
	bool		m_bIsMoving;		// �����ƶ�
	Queue*		m_pQueue;			// �����ĸ�����
	
};
#endif