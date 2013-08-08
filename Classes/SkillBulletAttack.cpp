#include "SkillBulletAttack.h"
#include "Monster.h"
#include "Hero.h"
#include "Effect.h"
#include "EntityManager.h"
#include "Comm.h"

void SkillBulletAttack::onEnter()
{
	Skill::onEnter();

	//ºóÃæÒª¸Ä³É¶ÁÈ¡ÅäÖÃ
	m_iDamage = 30;  //¹¥»÷Á¦
	m_fCoolTime = 3.f; //ÀäÈ´Ê±¼ä
	m_fElapseTime = 4.f;
	m_fAttackRange = 300.f;  //¹¥»÷¾àÀë
	m_fHitRange = 40.f;  //¹¥»÷·¶Î§

	m_fAttackSpeed = 4.f;

	schedule(schedule_selector(Skill::onUpdate));
}

void SkillBulletAttack::onExit()
{
	unschedule(schedule_selector(Skill::onUpdate));

	Skill::onExit();
}

void SkillBulletAttack::attack()
{
	m_bIsAttacking = true;
	m_fElapseTime = 0;
	m_pEffect = EM.addAnEffect(m_pOwner->getPosition(), EET_Bullet, m_pTarget->getPosition());
	
}

