#include "Character.h"
#include "Queue.h"
#include "GameInfo.h"

void Character::onEnter()
{
	MovingEntity::onEnter();

	m_vCurMoveVector = ccp(0, 0);
	m_bIsMoving = false;
	m_pQueue = NULL;
}

void Character::onExit()
{
	MovingEntity::onExit();
}

bool Character::onMove()
{
	// 正在移动中，请勿打扰>_<
	if (m_bIsMoving)
	{
		return false;
	}

	CCPoint moveDelta = m_vCurMoveVector * GI.GridSize;
	CCPoint targetPosition = getPosition() + moveDelta;

	// 如果这个不是队首
	if (m_pQueue && (this != m_pQueue->getHead()))
	{
		targetPosition = m_pQueue->getPrivousCharacter(this)->getPosition();
		setMoveVector(m_pQueue->getPrivousCharacter(this)->getMoveVector());
	}

	// 移动到目标位置之后，调用onMoveDone将m_bIsMoving置为false	
	CCAction* action = CCSequence::create(
		CCSpawn::create(
			CCMoveTo::create(1.f / getCurSpeed(), targetPosition),
			CCAnimate::create(m_pWalkAnim[0]),			
			NULL),
		CCCallFunc::create(this, callfunc_selector(Character::onMoveDone)),
		NULL
		);

	this->runAction(action);

	return (m_bIsMoving = true);
}

// 已经移动到目标格子
void Character::onMoveDone()
{
	m_bIsMoving = false;
}

void Character::kill() 
{
}

Queue* Character::getQueue() const 
{
	return m_pQueue;
}

void Character::setQueue(Queue* pQ) 
{
	if (pQ != NULL)
	{
		m_pQueue = pQ;
	}
}