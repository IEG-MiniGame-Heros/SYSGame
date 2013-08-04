#ifndef SYS_SKILL_FIRE_ATTACK
#define SYS_SKILL_FIRE_ATTACK

#include "Skill.h"

class SkillFireAttack : public Skill
{
public:
	CREATE_FUNC(SkillFireAttack);

	void onEnter();
	void onExit();

	void attack();
	void onUpdate(float dt);
};

#endif