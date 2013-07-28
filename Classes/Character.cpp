#include "Character.h"
#include "Queue.h"
#include "GameInfo.h"

void Character::onEnter()
{
	MovingEntity::onEnter();

	m_bIsMoving = false;
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
	//CCPoint curPos = getPosition();
	CCPoint targetPosition = getPosition() + moveDelta;
	if (this != GI.Me->getHead())
	{
		targetPosition = GI.Me->getPrivousCharacter(this)->getPosition();
	}

	// 移动到目标位置之后，调用onMoveDone将m_bIsMoving置为false
	CCAction* action = CCSequence::create(
		CCMoveTo::create(1.f, targetPosition),
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


