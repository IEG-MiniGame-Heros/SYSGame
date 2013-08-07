#include "Effect.h"
#include "EntityManager.h"

Effect::Effect()
{
	setType(ET_Effect);
}

void Effect::onEnter()
{
	MovingEntity::onEnter();

	m_bShouldMove = false;
}

void Effect::onExit()
{
	MovingEntity::onExit();
}

void Effect::setTarget(CCPoint target)
{
	m_vTargetPos = target;
}