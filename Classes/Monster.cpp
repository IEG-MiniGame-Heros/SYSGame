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

	setMoveVector(ccp(1, 0));

	// ���ö���
	// 0.�� 1.�� 2.�� 3.�� 
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

	//m_iWalkLoopCount = 0;
	//m_iWalkDir = 0;
	//m_bIsClockWise = std::rand() % 2; // ˳ʱ�뻹����ʱ���߶�
	m_bForceToStop = false;
	m_bDropItemAfterDeath = true;
}

void Monster::onExit()
{
	unschedule(schedule_selector(Monster::onUpdate));

	// ʩ�Ŷ���
	m_pWalkAnim[0]->release();

	Character::onExit();
}

bool IsReverseDir(const CCPoint& dir1, const CCPoint& dir2)
{
	return  (dir1.x == (dir2.x * -1)) && (dir1.y == (dir2.y * -1));
}

/** 
 * p2�Ƿ���p1��ǰ��������
 */
bool IsAheadOfMe(CCPoint p1, CCPoint dir, CCPoint p2)
{
	if (dir.x == 1)
	{
		return (p1.x < p2.x);
	}
	else if (dir.x == -1)
	{
		return (p1.x > p2.x);
	}
	else if (dir.y == 1)
	{
		return (p1.y < p2.y);
	}
	else 
	{
		return (p1.y > p2.y);
	}
}

int CanMove[4];

/** 
 * �������ʵ�ֹ����AI
 */
bool Monster::onMove()
{
	if (m_bIsMoving)
	{
		return false;
	}

	CCPoint curPos = getPosition();
	CCPoint curMoveVec = getMoveVector();
	
	memset(CanMove, 0, sizeof(CanMove));

	// ���ж��Ƿ�ɴ�
	for (int i = 0; i < 4; ++i)
	{
		// �����ڵķ����෴
		if (IsReverseDir(curMoveVec, WalkVec[i]))
		{
			continue;
		}
		if (!GI.Helper->isReachable(curPos, WalkVec[i], 1))
		{
			continue;
		}
		++CanMove[i];
	}

	// �Ƿ���ڵ���
	CCPoint enemyPos(0, 0);
	bool enemyExist = (GI.Me != NULL && GI.Me->getQueueNum() > 0);
	if (enemyExist)
	{
		enemyPos = GI.Me->getHead()->getPosition();
	}

	// ����ɴ�ж����ŷ���
	for (int i = 0; i < 4; ++i)
	{
		if (CanMove[i] > 0)
		{
			if (enemyExist)
			{
				if (IsAheadOfMe(curPos, WalkVec[i], enemyPos))
				{
					++CanMove[i];
				}
			}
			else 
			{
				// ͬ��
				if (GI.Helper->ccpEqual(curMoveVec, WalkVec[i]))
				{
					++CanMove[i];
				}
			}
		}
	}

	int index = -1, ret = 0;
	for (int i = 0; i < 4; ++i)
	{
		if (CanMove[i] > ret)
		{
			index = i;
			ret = CanMove[i];
		}
	}

	if (-1 == index)
	{
		return false;
	}
	else 
	{
		if (GI.Helper->ccpEqual(curMoveVec * (-1), WalkVec[index]))
		{
			CCLog("Oh, shit!!!!!!!!!!!!!!!");
		}
		setMoveVector(WalkVec[index]);
	}

	return Character::onMove();
}

const int WALK_LOOPS = 3;

void Monster::onUpdate(float dt)
{
	if (m_bForceToStop)
	{
		return;
	}

	bool moveSuccess = onMove();

	// �������������ײ����
	Monster* other = (Monster*)EM.findEntityInRange(this, 20.f, ET_Monster);
	if (other)
	{
		// ������Լ�ײ�����Ļ����ǲ������װ����
		other->setDropItemAfterDeath(false);
		other->kill();
	}
}

void Monster::setForceToStop(bool isStop)
{
	m_bForceToStop = isStop;
}

void Monster::kill()
{
	// �������Ӣ�ۻ�����Ʒ
	if (m_bDropItemAfterDeath)
	{
		CCPoint gridCenter = GI.Helper->getNearestGridCenter(getPosition());
		GI.Helper->randomGenHeroOrGoods(gridCenter);
	}

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

void Monster::setDropItemAfterDeath(bool shouldDrop)
{
	m_bDropItemAfterDeath = shouldDrop;
}