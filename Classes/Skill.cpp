#include "Skill.h"
#include "Hero.h"
#include "Monster.h"
#include "Effect.h"
#include "EntityManager.h"

void Skill::onEnter()
{
	CCNode::onEnter();

	// �趨˭ӵ�����Character
	m_pOwner = (Character*)(getParent());
	m_bIsAttacking = false;
	m_fElapseTime = 0;
}

void Skill::onExit()
{
	CCNode::onExit();
}

bool Skill::shouldAttack()
{
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
				pEnemy->getHarmed(m_iDamage);
				m_pEffect->kill();
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
