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
	 * 属于哪个队列&&设置队列
	 */
	Queue* getQueue() const;
	void setQueue(Queue* pQ);

protected: 

	int				m_iCurHealth;		// 当前生命值
	int				m_iMaxHealth;		// 最大生命值
	Queue*			m_pQueue;			// 属于哪个队伍
	CCAnimation*	m_pWalkAnim[4];		// 行走动画
	
};
#endif