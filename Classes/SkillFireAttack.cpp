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

	schedule(schedule_selector(Skill::onUpdate));
}

void SkillFireAttack::onExit()
{
	unschedule(schedule_selector(Skill::onUpdate));

	Skill::onExit();
}

void SkillFireAttack::attack()
{
	m_bIsAttacking = true;
	m_fElapseTime = 0;
	m_pEffect = EM.addAnEffect(m_pOwner->getPosition(), EET_FireBall, m_pTarget->getPosition());
}
