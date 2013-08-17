#ifndef SYS_EFFECT
#define SYS_EFFECT

#include "MovingEntity.h"

enum EEffectActionType
{
	EEAT_Frozenning,		// 冰冻特效Tag
};

class Effect : public MovingEntity
{
public:
	Effect();
	virtual void onEnter();
	virtual void onExit();

	/** 
	 * @brief 移除特效
	 */
	virtual void kill();

	bool isKilled() const;

	void setTarget(CCPoint target);

protected:
	float			m_fLifeTime;		// 存活时间
	bool			m_bShouldMove;		// 特效需要移动
	CCPoint			m_vTargetPos;		// 如果需要移动，移动的终点
	bool			m_bIsKilled;		// 已经被Kill了
};
#endif