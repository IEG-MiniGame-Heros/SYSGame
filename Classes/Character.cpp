#include "Character.h"
#include "Queue.h"
#include "EntityManager.h"
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
		setMoveVector(m_pQueue->getPrivousCharacter(this)->getMoveVector());
	}

	// �ƶ���Ŀ��λ��֮�󣬵���onMoveDone��m_bIsMoving��Ϊfalse	
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

// �Ѿ��ƶ���Ŀ�����
void Character::onMoveDone()
{
	m_bIsMoving = false;
}

void Character::kill() 
{
	// �ڶ���֮��
	if (m_pQueue)
	{
		m_pQueue->removeFromQueue(this);
	}
	else
	{
		EM.removeAnEntity(this, getType());
	}

	// Ȼ�󣬲�����������
	////////////////////////////
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

EEntityType Character::getEnemyType() const 
{
	return (getType() == ET_Hero ? ET_Monster : ET_Hero);
}

int Character::getCurHealth() const 
{
	return m_iCurHealth;
}

void Character::setCurHealth(int health)
{
	m_iCurHealth = health;
	if (m_iCurHealth < 0)
	{
		m_iCurHealth = 0;
	}
}

int Character::getMaxHealth() const 
{
	return m_iMaxHealth;
}

void Character::setMaxHealth(int max_health)
{
	m_iMaxHealth = max_health;
}

void Character::getHarmed(int damage)
{
	if (damage > 0)
	{
		m_iCurHealth -= damage;
		// �������
		if (m_iCurHealth <= 0)
		{
			kill();
		}
	}
}