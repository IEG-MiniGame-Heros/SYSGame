#include "Character.h"
#include "Queue.h"
#include "EntityManager.h"
#include "GameHelper.h"
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
	// 正在移动中，请勿打扰>_<
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
	//	/* -----------------判断是否不可通行---------------- */  
	//	/* 获得当前主角在地图中的格子位置 */  
	//	CCPoint tiledPos = tileCoordForPosition(ccp(x, y));  
 // 
	//	/* 获取地图格子的唯一标识 */  
	//	int tiledGid = GI.Meta->tileGIDAt(tiledPos);  
 // 
	//	/* 不为0，代表存在这个格子,如果存在，那么碰撞到啦~ 结束咯*/  
	//	if(tiledGid != 0) {  
	//		CCLog("collision detection");
	//		return (m_bIsMoving = false); 
	//	}  
	//}
	
	//bool flag = false;
	if (m_pQueue)
	{
		// 如果这个不是队首
		if (this != m_pQueue->getHead())
		{
			CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();  

			targetPosition = m_pQueue->getPrivousCharacter(this)->getPosition();
			CCPoint mv = getMoveVectorByPosition(getPosition(), targetPosition);
			setMoveVector(mv);
		}

		// 检测队伍速度是否要改变
		if (this == m_pQueue->getHead())
		{
			m_pQueue->checkChaningSpeed();
		}
		
		// 刷完队尾，看看有没有需要添加的
		if (m_pQueue->isLastMember(this)) 
		{
			bool isPendingKill = m_pQueue->isPendingKill(this);

			m_pQueue->refreshMembers();
			
			// 如果这是最后一个，而且被kill了，那么，直接退出吧, 为了避免程序挂掉
			if (isPendingKill)
			{
				return false;
			}
		}
	}

	int index = getIndexByMoveVector(getMoveVector());

	// 额。。。这个只是没有资源罢了
	if (getType() == ET_Monster)
	{
		index = 0;
	}

	CCAction*  action;
	// 移动到目标位置之后，调用onMoveDone将m_bIsMoving置为false	
	
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

// 已经移动到目标格子
void Character::onMoveDone()
{
	m_bIsMoving = false;
}

void Character::kill() 
{
	// 播放死亡动画
	EM.addAnEffect(getPosition(), EET_Explosion, ccp(0, 0));

	// 在队列之中
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
		// 如果挂了
		if (m_iCurHealth <= 0)
		{
			kill();
		}
	}
}

void Character::getHeal(int amount)
{
	if (amount > 0)
	{
		m_iCurHealth += amount;
		if (m_iCurHealth > m_iMaxHealth)
		{
			m_iCurHealth = m_iMaxHealth;
		}
	}
}


CCPoint Character::tileCoordForPosition( CCPoint pos )
{
	CCSize mapTiledNum = GI.Map->getMapSize();
    CCSize tiledSize = GI.Map->getTileSize();

    int x = pos.x / tiledSize.width;
    int y = pos.y / tiledSize.height;

    /* Cocos2d-x的默认Y坐标是由下至上的，所以要做一个相减操作 */
    y = mapTiledNum.height - y;

    return ccp(x, y);
}