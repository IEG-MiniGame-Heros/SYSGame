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
	// �����ƶ��У��������>_<
	if (m_bIsMoving)
	{
		return false;
	}

	CCPoint moveDelta = m_vCurMoveVector * GI.GridSize;
	CCPoint targetPosition = getPosition() + moveDelta;

	// ���������Ƕ���
	if (m_pQueue && (this != m_pQueue->getHead()))
	{
		targetPosition = m_pQueue->getPrivousCharacter(this)->getPosition();
	}

	// �ƶ���Ŀ��λ��֮�󣬵���onMoveDone��m_bIsMoving��Ϊfalse
	CCAction* action = CCSequence::create(
		CCMoveTo::create(1.f / getCurSpeed(), targetPosition),
		CCCallFunc::create(this, callfunc_selector(Character::onMoveDone)),
		NULL
		);

	this->runAction(action);

	return (m_bIsMoving = true);
}

// �Ѿ��ƶ���Ŀ�����
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