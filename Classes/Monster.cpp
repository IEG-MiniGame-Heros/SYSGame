#include "Monster.h"
#include "Queue.h"
#include "EntityManager.h"
#include "GameHelper.h"
#include "GameInfo.h"

#include <cstdlib>

Monster::Monster()
{
	setType(ET_Monster);
}

void Monster::onEnter()
{
	Character::onEnter();

	schedule(schedule_selector(Monster::onUpdate));

	setCurSpeed(GI.getMonsterConfig()[0].fMoveSpeed);
	setMaxSpeed(GI.getMonsterConfig()[0].fMoveSpeed);
	setCurHealth(GI.getMonsterConfig()[0].iHP);
	setMaxHealth(GI.getMonsterConfig()[0].iHP);

	// 设置动画
	// 0.右 1.下 2.左 3.上 
	m_pWalkAnim[0] = CCAnimation::create();
	m_pWalkAnim[0]->retain();
	m_pWalkAnim[0]->addSpriteFrameWithFileName("spirit/monster/Monster_R_1.png");
	m_pWalkAnim[0]->addSpriteFrameWithFileName("spirit/monster/Monster_R_2.png");
	m_pWalkAnim[0]->setDelayPerUnit(0.5f / getCurSpeed());

	m_pWalkAnim[1] = CCAnimation::create();
	m_pWalkAnim[1]->retain();
	m_pWalkAnim[1]->addSpriteFrameWithFileName("spirit/monster/Monster_D_1.png");
	m_pWalkAnim[1]->addSpriteFrameWithFileName("spirit/monster/Monster_D_2.png");
	m_pWalkAnim[1]->setDelayPerUnit(0.5f / getCurSpeed());

	m_pWalkAnim[2] = CCAnimation::create();
	m_pWalkAnim[2]->retain();
	m_pWalkAnim[2]->addSpriteFrameWithFileName("spirit/monster/Monster_L_1.png");
	m_pWalkAnim[2]->addSpriteFrameWithFileName("spirit/monster/Monster_L_2.png");
	m_pWalkAnim[2]->setDelayPerUnit(0.5f / getCurSpeed());

	m_pWalkAnim[3] = CCAnimation::create();
	m_pWalkAnim[3]->retain();
	m_pWalkAnim[3]->addSpriteFrameWithFileName("spirit/monster/Monster_U_1.png");
	m_pWalkAnim[3]->addSpriteFrameWithFileName("spirit/monster/Monster_U_2.png");
	m_pWalkAnim[3]->setDelayPerUnit(0.5f / getCurSpeed());

	m_iWalkLoopCount = 0;
	m_iWalkDir = 0;
	m_bIsClockWise = std::rand() % 2; // 顺时针还是逆时针走动
	m_bForceToStop = false;
}

void Monster::onExit()
{
	unschedule(schedule_selector(Monster::onUpdate));

	// 施放动画
	m_pWalkAnim[0]->release();

	Character::onExit();
}

const int WALK_LOOPS = 3;

void Monster::onUpdate(float dt)
{
	if (m_bForceToStop)
	{
		return;
	}

	setCurSpeed(m_fMaxSpeed);

	// 快撞到墙了，赶紧拐弯！！！
	CCPoint nextPos = GI.Helper->getNearestGridCenter(getPosition()) +
		WalkVec[m_iWalkDir] * GI.GridSize;
	if (0 && !GI.Helper->isWithinMap(nextPos) )
	{
		m_iWalkDir += (m_bIsClockWise ? 1 : -1);
		m_iWalkDir = (m_iWalkDir + 4) % 4;
		m_iWalkLoopCount = 0;
	}

	setMoveVector(WalkVec[m_iWalkDir]);

	bool moveSuccess = onMove();

	// 处理转弯问题
	if (moveSuccess && (!m_pQueue || m_pQueue->getHead() == this))
	{
		++m_iWalkLoopCount;

		if (m_iWalkLoopCount >= WALK_LOOPS)
		{
			m_iWalkDir += (m_bIsClockWise ? 1 : -1);
			m_iWalkDir = (m_iWalkDir + 4) % 4;
			m_iWalkLoopCount = 0;
			//CCLog("Dir = %d", m_iWalkDir);
		}
	}

	// 假如快与其他怪撞车了
	Monster* other = (Monster*)EM.findEntityInRange(this, 50.f, ET_Monster);
	if (other)
	{
		other->setForceToStop(true);
		setForceToStop(true);
	}
}

void Monster::setForceToStop(bool isStop)
{
	m_bForceToStop = isStop;
}

void Monster::kill()
{
	// 随机生成英雄或者物品
	CCPoint gridCenter = GI.Helper->getNearestGridCenter(getPosition());
	GI.Helper->randomGenHeroOrGoods(gridCenter);

	Character::kill();
}

Monster* Monster::create(const char *pszFileName)
{
	Monster *pobSprite = new Monster();
	if (pobSprite && pobSprite->initWithFile(pszFileName))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}