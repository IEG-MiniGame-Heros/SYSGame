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
	//void onUpdate(float dt);
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
	//void onUpdate(float dt);
};

#endif