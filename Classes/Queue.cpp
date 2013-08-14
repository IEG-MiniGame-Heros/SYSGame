#include "Queue.h"
#include "Character.h"
#include "FirstStage.h"
#include "EntityManager.h"
#include "Hero.h"
#include "GameHelper.h"
#include "GameInfo.h"

void Queue::onEnter()
{
	CCNode::onEnter();

	m_pCharacters = CCArray::create();
	m_pCharacters->retain();

	m_pPendingAddPool = CCArray::create();
	m_pPendingAddPool->retain();

	m_pPendingKillPool = CCArray::create();
	m_pPendingKillPool->retain();

	m_bPendingChangeSpeed = false;
	m_iUpdateFlag = 0;

	schedule(schedule_selector(Queue::onUpdate));
}

void Queue::onUpdate(float dt)
{
	CCObject* object;

	// 检测队伍的速度
	checkChaningSpeed();

	clearUpdateFlag();
	CCARRAY_FOREACH(m_pCharacters, object)
	{
		Character* pCha = (Character*)(object);
		pCha->onUpdate(dt);
	}

	// 更新Members
	if (isQueueUpdateFinished())
	{
		refreshMembers();
	}	
}

void Queue::onExit()
{
	m_pCharacters->release();
	m_pPendingAddPool->release();
	m_pPendingKillPool->release();

	unschedule(schedule_selector(Queue::onUpdate));

	CCNode::onExit();
}

Character* Queue::getHead() const 
{
	CCAssert((m_pCharacters->count() > 0), "Count of queue must larger than 0!!!");
	return (Character*)(m_pCharacters->objectAtIndex(0));	
}

int Queue::getQueueNum() const 
{
	return m_pCharacters->count();
}

CCArray* Queue::getCharacters() const 
{
	return m_pCharacters;
}

void Queue::setMoveVector(CCPoint move_vector)
{
	int size = m_pCharacters->count();
	if (size <= 0)
	{
		return;
	}
	//CCAssert((size > 0), "Count of queue must larger than 0!!!");

	CCPoint newVector = ccpMult(move_vector, -1);
	Character* pHead = getHead();
	// 如果跟队首反方向，则不处理
	if (newVector.x == pHead->getMoveVector().x && newVector.y == pHead->getMoveVector().y)
	{
		return;
	}

	//for (int i = size - 1; i > 0; --i)
	//{
	//	Character* character = (Character*)(m_pCharacters->objectAtIndex(i));
	//	Character* characterInFront = (Character*)(m_pCharacters->objectAtIndex(i - 1));
	//	character->setMoveVector(characterInFront->getMoveVector());
	//}
	pHead->setMoveVector(move_vector);
}

void Queue::appendCharacter(Character* character)
{
	if (character != NULL)
	{
		if (m_pCharacters->count() == 0)
		{
			GI.Game->removeChild(character);
			addChild(character);
			// 针对英雄刚出生的时候特殊处理一下
			if (character->getType())
			{
				character->setPosition(GI.Helper->getGridCenter(21, 11));
				character->setMoveVector(ccp(0, -1));
			}
			m_pCharacters->addObject(character);
			character->setQueue(this);
		}
		else 
		{
			// 加在队伍后面
			Character* lastCharacter = (Character*)(m_pCharacters->lastObject());			
			GI.Game->removeChild(character);
			addChild(character);
			character->setPosition(getPositionBehindTail());
			character->setMoveVector(lastCharacter->getMoveVector());
			character->setCurSpeed(lastCharacter->getCurSpeed());
			m_pCharacters->addObject(character);
			character->setQueue(this);
		}

		// 如果这是英雄
		if (character->getType() == ET_Hero)
		{
			((Hero*)(character))->setIsPickedUp(true);
			((Hero*)(character))->setAnimFreq();
		}
	}
}

CCPoint Queue::getPositionBehindTail() const 
{
	CCAssert((m_pCharacters->count() > 0), "The queue is empty!!!");

	Character* tail = (Character*)(m_pCharacters->lastObject());
	CCPoint tailPos = tail->getPosition() + ccpMult(tail->getMoveVector(), -1 * GI.GridSize);
	return tailPos;
}

Character* Queue::getPrivousCharacter(Character* pCha) const 
{
	if (pCha != getHead())
	{
		int index = m_pCharacters->indexOfObject(pCha);
		return (Character*)(m_pCharacters->objectAtIndex(index - 1));
	}

	return NULL;
}

bool Queue::isInQueue(Character* pCha) const 
{
	return (m_pCharacters->indexOfObject(pCha) != CC_INVALID_INDEX);
}

bool Queue::removeFromQueue(Character* character)
{
	if (!isInQueue(character))
	{
		return false;
	}

	//m_pCharacters->removeObject(character);
	int idx = m_pCharacters->indexOfObject(character);
	int size = m_pCharacters->count();
	for (int i = size - 1; i > idx; --i)
	{
		Character* character = (Character*)(m_pCharacters->objectAtIndex(i));
		Character* characterInFront = (Character*)(m_pCharacters->objectAtIndex(i - 1));
		character->setMoveVector(characterInFront->getMoveVector());
		character->setPosition(characterInFront->getPosition());
	}

	m_pCharacters->removeObject(character);
	//removeChild(character);
	EM.removeAnEntity(character, character->getType());

	return true;
}

bool Queue::isLastMember(Character* pCha) const 
{
	if (isInQueue(pCha))
	{
		return (m_pCharacters->lastObject() == pCha);
	}
	return false;
}

void Queue::addAMember(Character* pCha)
{
	m_pPendingAddPool->addObject(pCha);
	pCha->setQueue(this);
	GI.Game->removeChild(pCha);
}

void Queue::removeAMember(Character* pCha)
{
	m_pPendingKillPool->addObject(pCha);
	pCha->setVisible(false);	
}

void Queue::refreshMembers()
{
	while (m_pPendingAddPool->count() > 0)
	{
		Character* pCha = (Character*)m_pPendingAddPool->lastObject();
		appendCharacter(pCha);
		m_pPendingAddPool->removeLastObject();
		pCha->onUpdate(0.f);
	}

	while (m_pPendingKillPool->count() > 0)
	{
		Character* pCha = (Character*)m_pPendingKillPool->lastObject();
		removeFromQueue(pCha);
		m_pPendingKillPool->removeLastObject();
	}
}

/** 
 * @brief 是否即将被kill
 */
bool Queue::isPendingKill(Character* pCha) const 
{
	CCAssert(pCha != NULL, "");
	return (m_pPendingKillPool->indexOfObject(pCha) != CC_INVALID_INDEX);
}

CCArray* Queue::getAllMembers() const 
{
	return m_pCharacters;
}

void Queue::setCurSpeed(float speed)
{
	m_bPendingChangeSpeed = true;
	m_fNextSpeed = speed;
}

void Queue::checkChaningSpeed()
{
	if (m_bPendingChangeSpeed)
	{
		m_bPendingChangeSpeed = false;
		if (m_fNextSpeed >= 0 && getQueueNum() > 0)
		{
			CCObject* object;

			CCARRAY_FOREACH(m_pCharacters, object)
			{
				Character* pCha = (Character*)(object);
				pCha->setCurSpeed(m_fNextSpeed);
				if (pCha->getType() == ET_Hero)
				{
					((Hero*)(pCha))->setAnimFreq();
				}
			}
		}
	}
}

void Queue::clearUpdateFlag()
{
	m_iUpdateFlag = 0;
}

void Queue::setUpdateSuccess()
{
	++m_iUpdateFlag;
}

bool Queue::isQueueUpdateFinished() const 
{
	return (m_iUpdateFlag >= getQueueNum());
}

void Queue::allGotoDie()
{
	CCObject* object;
	CCARRAY_FOREACH(m_pCharacters, object)
	{
		((Character*)(object))->kill();
	}
}