#include "MovingEntity.h"

USING_NS_CC;

void MovingEntity::onEnter()
{
	CCNode::onEnter();

	m_bIsMoving = false;
}

void MovingEntity::onExit()
{

	CCNode::onExit();
}

bool MovingEntity::onMove(CCPoint direction)
{
	return true;
}

void MovingEntity::setMoveVector(CCPoint move_vector)
{
	m_vCurMoveVector = move_vector;
}

CCPoint MovingEntity::getMoveVector() const 
{
	return m_vCurMoveVector;
}

bool MovingEntity::isMoving() const
{
	return m_bIsMoving;
}

float MovingEntity::getCurSpeed() const
{
	return m_fCurSpeed;
}

void MovingEntity::setCurSpeed(float speed)
{
	if (speed > 0)
	{
		m_fCurSpeed = speed;
	}
}

float MovingEntity::getMaxSpeed() const
{
	return m_fMaxSpeed;
}

void MovingEntity::setMaxSpeed(float speed)
{
	if (speed > 0)
	{
		m_fMaxSpeed = speed;
	}
}