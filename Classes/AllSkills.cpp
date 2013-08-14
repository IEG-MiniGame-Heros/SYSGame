#include "AllSkills.h"
#include "Monster.h"
#include "Hero.h"
#include "Effect.h"
#include "EntityManager.h"
#include "GameInfo.h"
#include "Comm.h"


////////////////////////////////////////////////////
/*----------------- 释放火球技能 -------------------*/
void SkillFireAttack::onEnter()
{
	Skill::onEnter();

	//m_iDamage = 50;
	//m_fCoolTime = 5.f;
	//m_fElapseTime = 5.5f;
	//m_fAttackRange = 120.f;
	//m_fHitRange = 40.f;

	// 英雄的ID
	int heroId = 0;

	TSkill mySkill = GI.getHeroConfig()[heroId].stSkill;
	m_iDamage = mySkill.iDamage;
	m_fCoolTime = float(mySkill.iSkillCD);
	m_fElapseTime = 5.5f;
	m_fAttackRange = GI.getHeroConfig()[heroId].fAttackRange;
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

////////////////////////////////////////////////////
/*----------------- 释放冰球技能 -------------------*/
void SkillIceAttack::onEnter()
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

void SkillIceAttack::onExit()
{
	unschedule(schedule_selector(Skill::onUpdate));
	Skill::onExit();
}

void SkillIceAttack::attack()
{
	m_bIsAttacking = true;
	m_fElapseTime = 0;
	m_pEffect = EM.addAnEffect(m_pOwner->getPosition(), EET_IceBall, m_pTarget->getPosition());
}


////////////////////////////////////////////////////
/*----------------- 释放子弹技能 -------------------*/
void SkillBulletAttack::onEnter()
{
	Skill::onEnter();

	//后面要改成读取配置
	m_iDamage = 30;  //攻击力
	m_fCoolTime = 3.f; //冷却时间
	m_fElapseTime = 4.f;
	m_fAttackRange = 300.f;  //攻击距离
	m_fHitRange = 40.f;  //攻击范围

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