#ifndef SYS_SKILL_FIRE_ATTACK
#define SYS_SKILL_FIRE_ATTACK

#include "Skill.h"

/** 
 * 释放火球技能
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
 * 释放冰球技能
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
 * 释放子弹技能
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

/** 
 * 释放便便技能(拉屎？）
 */
class SkillShitAttack : public Skill
{
public:
	CREATE_FUNC(SkillShitAttack);

	void onEnter();
	void onExit();

	void attack();
};

#endif