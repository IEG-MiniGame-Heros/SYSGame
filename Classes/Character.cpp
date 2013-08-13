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

//const CCPoint WalkVec[4] = 
//{
//	CCPoint(1, 0),
//	CCPoint(0, -1),
//	CCPoint(-1, 0),
//	CCPoint(0, 1)
//};

#define ccpEqual(a, b) (a.x == b.x && a.y == b.y)

int getIndexByMoveVector(CCPoint vec)
{
	for (int i = 0; i < 4; ++i)
	{
		if (ccpEqual(vec, WalkVec[i]))
		{
			return i;
		}
	}

	CCLog("Can't match vector");
	return 0;
}

CCPoint getMoveVectorByPosition(CCPoint A, CCPoint B)
{
	CCPoint ret = B - A;
	if (fabs(ret.x) > 2.0)
	{
		ret.x = (ret.x > 0 ? 1.f : -1.f);
	}
	else 
	{
		ret.x = 0.f;
	}

	if (fabs(ret.y) > 2.f)
	{
		ret.y = (ret.y > 0 ? 1.f : -1.f);
	}
	else 
	{
		ret.y = 0.f;
	}
	return ret;
}

bool Character::onMove()
{
	//this->runAction((GI.Me->getHead()));
	// �����ƶ��У��������>_<
	if (m_bIsMoving)
	{
		return false;
	}

	CCPoint moveDelta = m_vCurMoveVector * GI.GridSize;
	CCPoint targetPosition = getPosition() + moveDelta;
	
	//if(GI.Map != NULL && GI.Meta != NULL){
	//	float x = 0;
	//	float y = 0;
	//	x = getPosition().x;
	//	y = getPosition().y;
	//	/* -----------------�ж��Ƿ񲻿�ͨ��---------------- */  
	//	/* ��õ�ǰ�����ڵ�ͼ�еĸ���λ�� */  
	//	CCPoint tiledPos = tileCoordForPosition(ccp(x, y));  
 // 
	//	/* ��ȡ��ͼ���ӵ�Ψһ��ʶ */  
	//	int tiledGid = GI.Meta->tileGIDAt(tiledPos);  
 // 
	//	/* ��Ϊ0����������������,������ڣ���ô��ײ����~ ������*/  
	//	if(tiledGid != 0) {  
	//		CCLog("collision detection");
	//		return (m_bIsMoving = false); 
	//	}  
	//}
	
	//bool flag = false;
	if (m_pQueue)
	{
		// ���������Ƕ���
		if (this != m_pQueue->getHead())
		{
			CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();  
			/* �߽��⣨�ȽϿӵ�
			if(targetPosition.x < 0 || targetPosition.x > visibleSize.width
				|| targetPosition.y < 0 || targetPosition.y > visibleSize.height){
				flag = true;
			}
			*/
			targetPosition = m_pQueue->getPrivousCharacter(this)->getPosition();
			CCPoint mv = getMoveVectorByPosition(getPosition(), targetPosition);
			setMoveVector(mv);
		}

		//if (this == m_pQueue->getHead())
		//{
		//	CCPoint pos0 = m_pQueue->getHead()->getPosition();
		//	CCLog("Position: %f, %f", pos0.x, pos0.y);
		//}
		
		// ˢ���β��������û����Ҫ��ӵ�
		if (m_pQueue->isLastMember(this)) 
		{
			m_pQueue->refreshMembers();
		}
	}

	int index = getIndexByMoveVector(getMoveVector());
	// ��������ֻ��û����Դ����
	if (getType() == ET_Monster)
	{
		index = 0;
	}

	CCAction*  action;
	// �ƶ���Ŀ��λ��֮�󣬵���onMoveDone��m_bIsMoving��Ϊfalse	
	
	action = CCSequence::create(
		CCSpawn::create(
			CCMoveTo::create(1.f / getCurSpeed(), targetPosition),
			CCAnimate::create(m_pWalkAnim[index]),			
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
	// ������������
	EM.addAnEffect(getPosition(), EET_Explosion, ccp(0, 0));

	// �ڶ���֮��
	if (m_pQueue)
	{
		m_pQueue->removeAMember(this);
	}
	else
	{
		EM.removeAnEntity(this, getType());
	}
	CCLog("Character killed");
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


CCPoint Character::tileCoordForPosition( CCPoint pos )
{
	CCSize mapTiledNum = GI.Map->getMapSize();
    CCSize tiledSize = GI.Map->getTileSize();

    int x = pos.x / tiledSize.width;
    int y = pos.y / tiledSize.height;

    /* Cocos2d-x��Ĭ��Y�������������ϵģ�����Ҫ��һ��������� */
    y = mapTiledNum.height - y;

    return ccp(x, y);
}