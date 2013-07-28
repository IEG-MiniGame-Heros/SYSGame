#include "MovingEntity.h"

USING_NS_CC;

void MovingEntity::onEnter()
{
	CCNode::onEnter();
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