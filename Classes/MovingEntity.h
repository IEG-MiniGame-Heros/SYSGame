#ifndef SYS_MOVING_ENTITY
#define SYS_MOVING_ENTITY

#include "BaseEntity.h"
#include "cocos2d.h"

USING_NS_CC;

class MovingEntity : public BaseEntity
{
public:

	virtual void onEnter();

	virtual void onExit();

	virtual bool onMove(CCPoint direction);

	void setMoveVector(CCPoint move_vector);
	CCPoint getMoveVector() const;

	CCPoint getPostionBehindMe() const;

	CCSprite* getSprite() const;


protected:

	CCPoint			m_vCurDirection;		// 当前的朝向
	float			m_fMaxSpeed;			// 最大速度
	float			m_fCurSpeed;			// 当前速度
	CCPoint			m_vCurMoveVector;		// 移动向量
	CCPoint			m_vLastMoveVector;      // 上一个移动向量
};
#endif