#include "Monster.h"
#include "Queue.h"
#include "EntityManager.h"
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

	// ���ö���
	// 0.�� 1.�� 2.�� 3.��
	m_pWalkAnim[0] = CCAnimation::create();
	m_pWalkAnim[0]->retain();
	m_pWalkAnim[0]->addSpriteFrameWithFileName("spirit/monster/m1.png");
	m_pWalkAnim[0]->addSpriteFrameWithFileName("spirit/monster/m1.png");
	m_pWalkAnim[0]->setDelayPerUnit(0.5 / getCurSpeed());

	setCurSpeed(GI.getMonsterConfig()[0].fMoveSpeed);
	setMaxSpeed(GI.getMonsterConfig()[0].fMoveSpeed);
	setCurHealth(GI.getMonsterConfig()[0].iHP);
	setMaxHealth(GI.getMonsterConfig()[0].iHP);

	m_iWalkLoopCount = 0;
	m_iWalkDir = 0;
	m_bIsClockWise = std::rand() % 2;
}

void Monster::onExit()
{
	unschedule(schedule_selector(Monster::onUpdate));

	// ʩ�Ŷ���
	m_pWalkAnim[0]->release();

	Character::onExit();
}

const int WALK_LOOPS = 3;

void Monster::onUpdate(float dt)
{
	if (0 /* �ȵ�ͼ��ײ�����Ժ󣬰�������ϣ���Ҫ�ù�̫ɵB */)
	{
		m_iWalkDir += (m_bIsClockWise ? 1 : -1);
		m_iWalkDir = (m_iWalkDir + 4) % 4;
		m_iWalkLoopCount = 0;
	}

	setMoveVector(WalkVec[m_iWalkDir]);

	bool moveSuccess = onMove();

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