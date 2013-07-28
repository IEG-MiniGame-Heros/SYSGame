#ifndef SYS_CHARACTER
#define SYS_CHARACTER

#include "MovingEntity.h"

class Character : public MovingEntity
{
public:

	virtual void onEnter();

	virtual void onExit();

	virtual bool onMove();

	virtual void onMoveDone();

	virtual void kill();

protected: 

	int			m_iCurHealth;		// 当前生命值
	int			m_iMaxHealth;		// 最大生命值
	bool		m_bIsMoving;		// 正在移动
	
};
#endif