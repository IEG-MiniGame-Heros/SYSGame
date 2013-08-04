#include "SkillFireAttack.h"
#include "Monster.h"
#include "Hero.h"
#include "Effect.h"
#include "EntityManager.h"
#include "Comm.h"

void SkillFireAttack::onEnter()
{
	Skill::onEnter();

	m_iDamage = 50;
	m_fCoolTime = 5.f;
	m_fElapseTime = 5.5f;
	m_fAttackRange = 120.f;
	m_fHitRange = 40.f;

	m_fAttackSpeed = 2.f;

	schedule(schedule_selector(SkillFireAttack::onUpdate));
}

void SkillFireAttack::onExit()
{
	unschedule(schedule_selector(SkillFireAttack::onUpdate));

	Skill::onExit();
}

void SkillFireAttack::attack()
{
	m_bIsAttacking = true;
	m_fElapseTime = 0;
	m_pEffect = EM.addAnEffect(m_pOwner->getPosition(), EET_FireBall, m_pTarget->getPosition());
	//CCLog("Attack!!!! Length is %f", m_pOwner->getPosition().getDistance(m_pTarget->getPosition()));
}

void SkillFireAttack::onUpdate(float dt)
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
		if (!m_pEffect)
		{
			m_bIsAttacking = false;
		}
		else 
		{
			Character* pEnemy = (Character*)EM.findEntityInRange(m_pEffect, m_fHitRange, m_pOwner->getEnemyType());
			if (pEnemy)
			{
				// �ж��˺�
				/////////////////////////////////
				pEnemy->getHarmed(m_iDamage);
				/////////////////////////////////
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

