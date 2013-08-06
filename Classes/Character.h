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

	/** 
	 * 返回敌人的类型，如果这是Hero,返回Monster，
	 * 反之亦然
	 */
	EEntityType	getEnemyType() const;

	int getCurHealth() const;
	void setCurHealth(int health);

	int getMaxHealth() const;
	void setMaxHealth(int max_health);

	/** 
	 * 受到伤害
	 * @param damage 伤害大小
	 */
	void getHarmed(int damage);

protected: 

	int				m_iCurHealth;		// 当前生命值
	int				m_iMaxHealth;		// 最大生命值
	Queue*			m_pQueue;			// 属于哪个队伍
	CCAnimation*	m_pWalkAnim[4];		// 行走动画
	
};
#endif