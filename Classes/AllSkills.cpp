#include "AllSkills.h"
#include "Monster.h"
#include "Hero.h"
#include "Effect.h"
#include "EntityManager.h"
#include "GameInfo.h"
#include "Comm.h"


////////////////////////////////////////////////////
/*----------------- �ͷŻ����� -------------------*/
void SkillFireAttack::onEnter()
{
	Skill::onEnter();

	//m_iDamage = 50;
	//m_fCoolTime = 5.f;
	//m_fElapseTime = 5.5f;
	//m_fAttackRange = 120.f;
	//m_fHitRange = 40.f;

	// Ӣ�۵�ID
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
/*----------------- �ͷű����� -------------------*/
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
/*----------------- �ͷ��ӵ����� -------------------*/
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