#ifndef SYS_CHARACTER
#define SYS_CHARACTER

#include "MovingEntity.h"

class Queue;

const CCPoint WalkVec[4] = 
{
	CCPoint(1, 0),		// ��
	CCPoint(0, -1),		// ��
	CCPoint(-1, 0),		// ��
	CCPoint(0, 1)		// ��
};

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

	/** 
	 * ���ص��˵����ͣ��������Hero,����Monster��
	 * ��֮��Ȼ
	 */
	EEntityType	getEnemyType() const;

	int getCurHealth() const;
	void setCurHealth(int health);

	int getMaxHealth() const;
	void setMaxHealth(int max_health);

	/** 
	 * �ܵ��˺�
	 * @param damage �˺���С
	 */
	void getHarmed(int damage);

    /* 
	 * ����������ת��Ϊ��ͼ��������
	 */
    CCPoint tileCoordForPosition(CCPoint pos);

protected: 

	int				m_iCurHealth;		// ��ǰ����ֵ
	int				m_iMaxHealth;		// �������ֵ
	Queue*			m_pQueue;			// �����ĸ�����
	CCAnimation*	m_pWalkAnim[4];		// ���߶���
	
};
#endif