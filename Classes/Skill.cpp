#include "Skill.h"
#include "Hero.h"
#include "Monster.h"
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
