#include "FireBall.h"
#include "EntityManager.h"

void FireBall::onEnter()
{
	Effect::onEnter();

	m_fLifeTime = 1.0f;
	m_bShouldMove = true;

	CCAnimation* anim = CCAnimation::create();
	anim->addSpriteFrameWithFileName("FireBall_1.png");
	anim->setDelayPerUnit(m_fLifeTime);

	//CCLog("Target = %f, %f", m_vTargetPos.x, m_vTargetPos.y);
	CCAction* act = CCSequence::create(
		//CCSpawn::create(
			//CCAnimate::create(anim),
			CCMoveTo::create(m_fLifeTime, m_vTargetPos),
			//NULL),
		CCCallFunc::create(this, callfunc_selector(Effect::kill)),
		NULL
		);


	runAction(act);
}

void FireBall::kill()
{
	EM.removeAnEntity(this, ET_Effect);
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

void FireBall::removeFunc()
{
	///unschedule(schedule_selector(removeFunc));
	kill();
}