#ifndef __SYS_SKILL_BULLET_ATTACK
#define __SYS_SKILL_BULLET_ATTACK
#include "Skill.h"

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
