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

	bool isMoving() const;

	float getCurSpeed() const;
	void setCurSpeed(float speed);

	float getMaxSpeed() const;
	void setMaxSpeed(float speed);


protected:

	CCPoint			m_vCurDirection;		// ��ǰ�ĳ���
	float			m_fMaxSpeed;			// ����ٶ�
	float			m_fCurSpeed;			// ��ǰ�ٶ�
	CCPoint			m_vCurMoveVector;		// �ƶ�����
	CCPoint			m_vLastMoveVector;      // ��һ���ƶ�����
	bool			m_bIsMoving;			// �����ƶ�
};
#endif