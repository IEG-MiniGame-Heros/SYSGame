#ifndef SYS_EFFECT
#define SYS_EFFECT

#include "MovingEntity.h"

class Effect : public MovingEntity
{
public:
	Effect();
	virtual void onEnter();
	virtual void onExit();

	//void setLifeTime(float time);
	///** 
	// * @brief 播放特效
	// */
	//void play();

	/** 
	 * @brief 移除特效
	 */
	void kill();

	void setTarget(CCPoint target);

protected:
	float			m_fLifeTime;		// 存活时间
	bool			m_bShouldMove;		// 特效需要移动
	CCPoint			m_vTargetPos;		// 如果需要移动，移动的终点
};
#endif