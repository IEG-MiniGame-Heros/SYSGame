#ifndef SYS_SKILL_FIRE_ATTACK
#define SYS_SKILL_FIRE_ATTACK

#include "Skill.h"

/** 
 * �ͷŻ�����
 * @see ThrowableObj
 */
class SkillFireAttack : public Skill
{
public:
	CREATE_FUNC(SkillFireAttack);

	void onEnter();
	void onExit();

	void attack();
};

/** 
 * �ͷű�����
 */
class SkillIceAttack : public Skill
{
public:
	CREATE_FUNC(SkillIceAttack);

	void onEnter();
	void onExit();

	void attack();
};

/** 
 * �ͷ��ӵ�����
 */
class SkillBulletAttack :
	public Skill
{
public:
	CREATE_FUNC(SkillBulletAttack);

	void onEnter();
	void onExit();

	void attack();
};

#endif