#include "Skill.h"
#include "Hero.h"
#include "Monster.h"
#include "Effect.h"
#include "GameInfo.h"
#include "EntityManager.h"

Skill::Skill(int id) : m_iSkillID(id) 
{
}

void Skill::onEnter()
{
	CCNode::onEnter();	

	// �趨˭ӵ�����Character
	m_pOwner = (Character*)(getParent());
	m_bIsAttacking = false;
	m_fElapseTime = 100000.f;
	m_bIsEnable = true;

	// ���ü��ܸ�������
	int SkillIdx = m_iSkillID - 1;
	m_iDamage = GI.getSkillConfig()[SkillIdx].iDamage;
	m_fCoolTime = GI.getSkillConfig()[SkillIdx].iSkillCD;
	m_fAttackSpeed = GI.getSkillConfig()[SkillIdx].fSpeed;
	m_fAttackRange = GI.getSkillConfig()[SkillIdx].fAttackRange;
	m_fHitRange = GI.getSystemConfig().fHitRange;

	schedule(schedule_selector(Skill::onUpdate));
}

void Skill::onExit()
{
	unschedule(schedule_selector(Skill::onUpdate));

	CCNode::onExit();
}

void Skill::attack()
{
	m_bIsAttacking = true;
	m_fElapseTime = 0;
	m_pEffect = EM.addAnEffect(m_pOwner->getPosition(), EEffectType(m_iSkillID), m_pTarget->getPosition());
}

bool Skill::shouldAttack()
{
	if (!m_bIsEnable)
	{
		return false;
	}

	// ������ڹ�����
	if (m_bIsAttacking) 
	{
		return false;
	}

	if (m_fElapseTime < m_fCoolTime)
	{
		return false;
	}

	Character* pCha = (Character*)EM.findEntityInRange(m_pOwner, m_fAttackRange, m_pOwner->getEnemyType());
	if (pCha)
	{
		m_pTarget = pCha;
		return true;
	}

	return false;
}

void Skill::onUpdate(float dt)
{
	// �����Ҳ��֪����ô���ͣ��ӵ���dt��Ȼ�д���100��ʱ�̣�����
	// >_<���ԣ������Ű�~~~
	if (dt < 0.5f)
	{
		m_fElapseTime += dt;
	}

	if (m_bIsAttacking)
	{
		// ��Ч�Ѿ�����
		if (!m_pEffect || m_pEffect->isKilled())
		{
			m_bIsAttacking = false;
		}
		else 
		{
			Character* pEnemy = NULL;
			if (m_pEffect && m_pEffect->retainCount() > 1)
			{
				//CCLog("Fire, Count = %d", m_pEffect->retainCount());
				pEnemy = (Character*)EM.findEntityInRange(m_pEffect, m_fHitRange, m_pOwner->getEnemyType());
			}
			if (pEnemy)
			{
				// �ж��˺�
				bool IsMonster = false;
				if (pEnemy->getType() == ET_Monster)
				{
					IsMonster = true;
				}
				pEnemy->getHarmed(m_iDamage, IsMonster);
				m_pEffect->setVisible(false);
				m_pEffect = NULL;
				m_bIsAttacking = false;
			}
		}
	}

	if (shouldAttack())
	{
		attack();
	}
}

bool Skill::isEnable() const 
{
	return m_bIsEnable;
}

void Skill::setEnable(bool flag)
{
	m_bIsEnable = flag;
}

Skill* Skill::create(int SkillID)
{
	Skill *pRet = new Skill(SkillID); 
	if (pRet && pRet->init()) 
	{ 
		pRet->autorelease(); 
		return pRet; 
	} 
	else 
	{ 
		delete pRet; 
		pRet = NULL; 
		return NULL; 
	} 
}