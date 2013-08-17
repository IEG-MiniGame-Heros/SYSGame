#ifndef SYS_CHARACTER
#define SYS_CHARACTER

#include "MovingEntity.h"

class Queue;
class Skill;

enum ECharacterActionTag
{
	ECAT_HeroFade,		// 英雄消失的Tag
	ECAT_BloodFade		// 血条消失的Tag
};


const CCPoint WalkVec[4] = 
{
	CCPoint(1, 0),		// 右
	CCPoint(0, -1),		// 下
	CCPoint(-1, 0),		// 左
	CCPoint(0, 1)		// 上
};

class Character : public MovingEntity
{
public:

	virtual void onEnter();

	virtual void onExit();

	virtual bool onMove();

	virtual void onMoveDone();

	virtual void kill();

	virtual void onUpdate(float dt);

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

	/** 
	 * 吃血包，得到治疗
	 */
	void getHeal(int amount);

    /* 
	 * 将像素坐标转换为地图格子坐标
	 */
    CCPoint tileCoordForPosition(CCPoint pos);

	// 设置血条
	bool initHPStrip();

	// 是否显示血条
	void setShowHP(bool bShow);

	void stopShowHPCallback();

protected: 

	int				m_iCurHealth;		// 当前生命值
	int				m_iMaxHealth;		// 最大生命值
	Queue*			m_pQueue;			// 属于哪个队伍
	CCAnimation*	m_pWalkAnim[4];		// 行走动画

	bool			m_bIsPendingKill;	// 即将被kill掉
	
	CCProgressTimer* m_pBloodBar;		// 血条
	CCSprite*		m_pBloodBlack;		// 血条外围的一层黑
	CCAction*		m_pShowHPAct;		// 显示血条Action
	bool			m_bEnableShowHP;	// 显示血条开关

	Skill*			m_pSkill;			// 技能指针
};
#endif