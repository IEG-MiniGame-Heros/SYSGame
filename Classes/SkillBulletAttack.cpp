#include "SkillBulletAttack.h"
#include "Monster.h"
#include "Hero.h"
#include "Effect.h"
#include "EntityManager.h"
#include "Comm.h"

void SkillBulletAttack::onEnter()
{
	Skill::onEnter();

	//����Ҫ�ĳɶ�ȡ����
	m_iDamage = 30;  //������
	m_fCoolTime = 3.f; //��ȴʱ��
	m_fElapseTime = 4.f;
	m_fAttackRange = 300.f;  //��������
	m_fHitRange = 40.f;  //������Χ

	m_fAttackSpeed = 4.f;

	schedule(schedule_selector(SkillBulletAttack::onUpdate));
}

void SkillBulletAttack::onExit()
{
	unschedule(schedule_selector(SkillBulletAttack::onUpdate));

	Skill::onExit();
}

void SkillBulletAttack::attack()
{
	m_bIsAttacking = true;
	m_fElapseTime = 0;
	m_pEffect = EM.addAnEffect(m_pOwner->getPosition(), EET_Bullet, m_pTarget->getPosition());
	//CCLog("Attack!!!! Length is %f", m_pOwner->getPosition().getDistance(m_pTarget->getPosition()));
}

void SkillBulletAttack::onUpdate(float dt)
{
	if (dt < 0.5f)
	{
		m_fElapseTime += dt;
	}

	if (m_bIsAttacking)
	{
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

