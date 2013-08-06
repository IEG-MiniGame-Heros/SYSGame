#include "Skill.h"
#include "Hero.h"
#include "Monster.h"
#include "EntityManager.h"

void Skill::onEnter()
{
	CCNode::onEnter();

	// 设定谁拥有这个Character
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
	// 如果正在攻击中
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
