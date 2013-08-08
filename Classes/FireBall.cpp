#include "FireBall.h"
#include "EntityManager.h"

#include <math.h>

void FireBall::onEnter()
{
	Effect::onEnter();

	m_fLifeTime = 2.f;
	m_bShouldMove = true;

	float length = max(600.f, getPosition().getDistance(m_vTargetPos));
	CCPoint move_delta((m_vTargetPos - getPosition()).normalize() * length);

	CCAction* act = CCSequence::create(
		CCMoveBy::create(m_fLifeTime, move_delta),
		CCCallFunc::create(this, callfunc_selector(Effect::kill)),
		NULL
		);


	runAction(act);
}

void FireBall::onExit()
{
	Effect::onExit();
}

FireBall* FireBall::create(const char *pszFileName)
{
	FireBall *pobSprite = new FireBall();
	if (pobSprite && pobSprite->initWithFile(pszFileName))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}