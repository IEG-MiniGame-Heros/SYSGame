#include "Queue.h"
#include "Character.h"
#include "FirstStage.h"
#include "EntityManager.h"
#include "Hero.h"
#include "GameHelper.h"
#include "GameInfo.h"

#define TEST_REMOVE_FROM_QUEUE 0

void Queue::onEnter()
{
	CCNode::onEnter();

	m_pCharacters = CCArray::create();
	m_pCharacters->retain();

	m_pPendingAddPool = CCArray::create();
	m_pPendingAddPool->retain();

	m_pPendingKillPool = CCArray::create();
	m_pPendingKillPool->retain();

#if TEST_REMOVE_FROM_QUEUE
	schedule(schedule_selector(Queue::onUpdate), 5, 5, 2);
#endif
}

void Queue::onUpdate(float dt)
{
	CCLog("///////////Queue Num: %d", m_pCharacters->count());		
	if (m_pCharacters && m_pCharacters->count() > 3)
	{		
		//removeAMember((Character*)m_pCharacters->objectAtIndex(0));
		removeAMember((Character*)m_pCharacters->objectAtIndex(1));
		removeAMember((Character*)m_pCharacters->objectAtIndex(2));
	}	
}

void Queue::onExit()
{
	m_pCharacters->release();
	m_pPendingAddPool->release();
	m_pPendingKillPool->release();

#if TEST_REMOVE_FROM_QUEUE
	unschedule(schedule_selector(Queue::onUpdate));
#endif

	CCNode::onExit();
}

Character* Queue::getHead() const 
{
	CCAssert((m_pCharacters->count() > 0), "Count of queue must larger than 0!!!");
	return (Character*)(m_pCharacters->objectAtIndex(0));	
}

CCArray* Queue::getCharacters() const 
{
	return m_pCharacters;
}

void Queue::setMoveVector(CCPoint move_vector)
{
	int size = m_pCharacters->count();
	CCAssert((size > 0), "Count of queue must larger than 0!!!");

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
	CCPoint pos;
	if (character != NULL)
	{
		if (m_pCharacters->count() == 0)
		{
			GI.Game->removeChild(character);
			addChild(character);
			pos = GI.Helper->getGridCenter(5, 5);
			character->setPosition(GI.Helper->getGridCenter(5, 5));
			character->setMoveVector(ccp(0, 1));
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
			m_pCharacters->addObject(character);
			character->setQueue(this);
		}

		// 如果这是英雄
		if (character->getType() == ET_Hero)
		{
			((Hero*)(character))->setIsPickedUp(true);
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
		pCha->onMove();
	}

	while (m_pPendingKillPool->count() > 0)
	{
		Character* pCha = (Character*)m_pPendingKillPool->lastObject();
		removeFromQueue(pCha);
		m_pPendingKillPool->removeLastObject();
	}
}