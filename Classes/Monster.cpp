#include "Monster.h"
#include "Queue.h"
#include "EntityManager.h"
#include "Skill.h"
#include "AllEffects.h"
#include "GameHelper.h"
#include "GameInfo.h"

#include <cstdlib>

Monster::Monster() : m_iMonsterID(1)
{
	setType(ET_Monster);
}

Monster::Monster(int ID) : m_iMonsterID(ID) 
{
	setType(ET_Monster);
}

char CMonster[25];

void Monster::onEnter()
{
	Character::onEnter();

	schedule(schedule_selector(Monster::onUpdate));

	int MonsterIdx = m_iMonsterID - 1;

	setCurSpeed(GI.getMonsterConfig()[MonsterIdx].fMoveSpeed);
	setMaxSpeed(GI.getMonsterConfig()[MonsterIdx].fMoveSpeed);
	setMaxHealth(GI.getMonsterConfig()[MonsterIdx].iHP);
	setCurHealth(GI.getMonsterConfig()[MonsterIdx].iHP);

	setMoveVector(ccp(1, 0));

	sprintf(CMonster, "spirit/monster/Monster%d", m_iMonsterID);
	std::string StrMonster(CMonster);

	// 设置动画
	// 0.右 1.下 2.左 3.上 
	m_pWalkAnim[0] = CCAnimation::create();
	m_pWalkAnim[0]->retain();
	m_pWalkAnim[0]->addSpriteFrameWithFileName( (StrMonster + std::string("_R_1.png")).c_str() );
	m_pWalkAnim[0]->addSpriteFrameWithFileName( (StrMonster + std::string("_R_2.png")).c_str() );
	m_pWalkAnim[0]->setDelayPerUnit(0.5f / getCurSpeed());

	m_pWalkAnim[1] = CCAnimation::create();
	m_pWalkAnim[1]->retain();
	m_pWalkAnim[1]->addSpriteFrameWithFileName( (StrMonster + std::string("_D_1.png")).c_str() );
	m_pWalkAnim[1]->addSpriteFrameWithFileName( (StrMonster + std::string("_D_2.png")).c_str() );
	m_pWalkAnim[1]->setDelayPerUnit(0.5f / getCurSpeed());

	m_pWalkAnim[2] = CCAnimation::create();
	m_pWalkAnim[2]->retain();
	m_pWalkAnim[2]->addSpriteFrameWithFileName( (StrMonster + std::string("_L_1.png")).c_str() );
	m_pWalkAnim[2]->addSpriteFrameWithFileName( (StrMonster + std::string("_L_2.png")).c_str() );
	m_pWalkAnim[2]->setDelayPerUnit(0.5f / getCurSpeed());

	m_pWalkAnim[3] = CCAnimation::create();
	m_pWalkAnim[3]->retain();
	m_pWalkAnim[3]->addSpriteFrameWithFileName( (StrMonster + std::string("_U_1.png")).c_str() );
	m_pWalkAnim[3]->addSpriteFrameWithFileName( (StrMonster + std::string("_U_2.png")).c_str() );
	m_pWalkAnim[3]->setDelayPerUnit(0.5f / getCurSpeed());

	// 设置技能
	m_pSkill = Skill::create(GI.getMonsterConfig()[MonsterIdx].iSkillID);
	addChild(m_pSkill);

	// 冰冻
	m_bIsFrozen = false;
	m_bForceToStop = false;
	m_bDropItemAfterDeath = true;
}

void Monster::onExit()
{
	unschedule(schedule_selector(Monster::onUpdate));

	removeChild(m_pSkill, true);

	// 释放动画
	m_pWalkAnim[0]->release();
	m_pWalkAnim[1]->release();
	m_pWalkAnim[2]->release();
	m_pWalkAnim[3]->release();

	Character::onExit();
}

bool IsReverseDir(const CCPoint& dir1, const CCPoint& dir2)
{
	return  (dir1.x == (dir2.x * -1)) && (dir1.y == (dir2.y * -1));
}

/** 
 * p2是否在p1的前景方向上
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
 * 在这里简单实现怪物的AI
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

	// 先判断是否可达
	for (int i = 0; i < 4; ++i)
	{
		// 跟现在的方向相反
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

	// 是否存在敌人
	CCPoint enemyPos(0, 0);
	bool enemyExist = (GI.Me != NULL && GI.Me->getQueueNum() > 0);
	if (enemyExist)
	{
		enemyPos = GI.Me->getHead()->getPosition();
	}

	// 如果可达，判断最优方向
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
				// 同向
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
		setMoveVector(WalkVec[index]);
	}

	return Character::onMove();
}

const int WALK_LOOPS = 3;

void Monster::onUpdate(float dt)
{
	if (m_bIsFrozen)
	{
		//if (m_pFrozenEft && m_pFrozenEft->retainCount() > 1 && !m_pFrozenEft->isKilled() )
		//{
		//	m_pFrozenEft->setPosition(getPosition());
		//}
		
		return;
	}

	bool moveSuccess = onMove();

	// 假如快与其他怪撞车了
	Monster* other = (Monster*)EM.findEntityInRange(this, 20.f, ET_Monster);
	if (other)
	{
		// 如果怪自己撞到死的话，是不会掉落装备的
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
	// 随机生成英雄或者物品
	if (m_bDropItemAfterDeath)
	{
		CCPoint gridCenter = GI.Helper->getNearestGridCenter(getPosition());
		GI.Helper->randomGenHeroOrGoods(gridCenter);
	}

	// 如果正结冰
	if (m_bIsFrozen)
	{
		CCNode* pFrozChild = getChildByTag(EEAT_FrozenChildTag);
		if (pFrozChild != NULL)
		{
			((Frozen*)(pFrozChild))->kill();
		}
	}

	Character::kill();
}

Monster* Monster::create(const char *pszFileName, int MonsID)
{
	Monster *pobSprite = new Monster(MonsID);
	if (pobSprite && pobSprite->initWithFile(pszFileName))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

/** 
 * 死后是否要掉落物品
 */
void Monster::setDropItemAfterDeath(bool shouldDrop)
{
	m_bDropItemAfterDeath = shouldDrop;
}

/** 
 * 设置冰冻
 */
void Monster::setFrozen(bool frozen)
{
	if (frozen)
	{
		// 本身已经结冰了
		if (m_bIsFrozen)
		{
			CCNode* pFrozChild = getChildByTag(EEAT_FrozenChildTag);
			if (pFrozChild != NULL)
			{
				((Frozen*)(pFrozChild))->kill();
			}
		}
		
		Frozen* pFroz = (Frozen*)(EM.addAnEffectOnCharacter(EET_Frozen, this));
		pFroz->setTag(EEAT_FrozenChildTag);
		pFroz->frozenStart(this);
		m_bIsFrozen = true;

		// 冰冻之后，技能也要冻结掉
		m_pSkill->setEnable(false);
	}
	else 
	{
		m_bIsFrozen = false;
		m_pSkill->setEnable(true);
	}
}