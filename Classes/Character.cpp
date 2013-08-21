#include "Character.h"
#include "Queue.h"
#include "EntityManager.h"
#include "GameHelper.h"
#include "GameInfo.h"

void Character::onEnter()
{
	MovingEntity::onEnter();

	// 初始化血条
	initHPStrip();

	// 显示血条3秒后消失
	m_pShowHPAct = CCSequence::create(
			CCDelayTime::create(3.f),
			CCCallFunc::create(this, callfunc_selector(Character::stopShowHPCallback)),
			NULL
		);
	m_pShowHPAct->setTag(ECAT_BloodFade);
	m_pShowHPAct->retain();

	// 默认不显示血条
	m_bEnableShowHP = false;
	setShowHP(false);

	m_bIsPendingKill = false;
	m_vCurMoveVector = ccp(0, 0);
	m_bIsMoving = false;
	m_pQueue = NULL;
	m_pSkill = NULL;
}


bool Character::initHPStrip(){
	bool isRet=false;
	do 
	{
		m_pBloodBlack = new CCSprite();
		m_pBloodBlack->initWithFile("spirit/bloodbar/blood_frame.png");
		CC_BREAK_IF(!m_pBloodBlack);	
		m_pBloodBlack->setPosition(ccp(this->getContentSize().width/2,this->getContentSize().height+2));
		this->addChild(m_pBloodBlack, 2000);

		CCSprite* blood = new CCSprite();
		blood->initWithFile("spirit/bloodbar/blood.png");
		CC_BREAK_IF(!blood);
		this->m_pBloodBar=CCProgressTimer::create(blood);
		CC_BREAK_IF(!m_pBloodBar);
		m_pBloodBar->setType(kCCProgressTimerTypeBar);
		m_pBloodBar->setMidpoint(ccp(0,0)); 
		m_pBloodBar->setBarChangeRate(ccp(1,0));

		m_pBloodBar->setPosition(ccp(this->getContentSize().width/2,this->getContentSize().height+2));
		// TODO :: 用setPercentage方法设置百分比 Emily
		m_pBloodBar->setPercentage(100);
		this->addChild(m_pBloodBar,2);
		// TODO :: 通过setVisible方法控制血条是否可见 Emily
		//m_pBloodBlack->setVisible(false);
		//bloodBwlid->setVisible(false);
		isRet=true;
	} while (0);
	return isRet;

}

void Character::setShowHP(bool bShow)
{
	if (m_pBloodBar)
	{
		m_pBloodBar->setVisible(bShow);
		m_pBloodBlack->setVisible(bShow);
	}
}

void Character::stopShowHPCallback()
{
	setShowHP(false);
}

void Character::onExit()
{
	m_pShowHPAct->release();

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

/** 
 * 只处理动画相关的
 */ 
bool Character::onMove()
{
	// 正在移动中，请勿打扰>_<
	if (m_bIsMoving)
	{
		return false;
	}

	CCPoint moveDelta = m_vCurMoveVector * GI.GridSize;
	CCPoint targetPosition = getPosition() + moveDelta;
	

	if (m_pQueue)
	{
		// 移动成功
		m_pQueue->setUpdateSuccess();

		// 如果这个不是队首
		if (this != m_pQueue->getHead())
		{
			CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();  

			targetPosition = m_pQueue->getPrivousCharacter(this)->getPosition();
			CCPoint mv = getMoveVectorByPosition(getPosition(), targetPosition);
			setMoveVector(mv);
		}		
	}

	int index = getIndexByMoveVector(getMoveVector());

	// 移动到目标位置之后，调用onMoveDone将m_bIsMoving置为false		
	CCAction*  action = CCSequence::create(
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

void Character::onUpdate(float dt) {}

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
	if (health != m_iCurHealth)
	{
		m_iCurHealth = health;
		if (m_iCurHealth < 0)
		{
			m_iCurHealth = 0;
		}
		if (m_iCurHealth > m_iMaxHealth)
		{
			m_iCurHealth = m_iMaxHealth;
		}

		// 如果需要显示血条
		if (m_bEnableShowHP)
		{
			stopActionByTag(ECAT_BloodFade);

			setShowHP(true);
			m_pBloodBar->setPercentage(100.0 * m_iCurHealth / m_iMaxHealth);

			if (m_iCurHealth > int(m_iMaxHealth * 0.5))
			{
				// 血量小于50%，一定会显示血条
				runAction(m_pShowHPAct);
			}
		}
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

void Character::getHarmed(int damage, bool bHeroToMonster /* = false */)
{
	if (damage > 0)
	{
		setCurHealth(m_iCurHealth - damage);
		// 如果挂了
		if (m_iCurHealth <= 0)
		{
			if (getType() == ET_Hero && m_pQueue && m_pQueue->getHead() == this)
			{
				//CCLOG("Alll Go to Die!!!!!!!!!!!");
				m_pQueue->allGotoDie();
			}
			else 
			{
				if (bHeroToMonster)
				{
					// 如果是英雄打怪,死了的话，计分
					GI.MonsterKillNum += 1;
					GI.Score += GI.getSystemConfig().fMonsterCoefficient;
				}

				kill();
			}
		}
	}
}

void Character::getHeal(int amount)
{
	if (amount > 0)
	{
		setCurHealth(m_iCurHealth + amount);
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