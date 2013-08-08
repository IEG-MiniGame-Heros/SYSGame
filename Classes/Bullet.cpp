#include "Bullet.h"

void Bullet::onEnter()
{
	Effect::onEnter();

	m_fLifeTime = 1.0f;
	m_bShouldMove = true;

	CCAnimation* anim = CCAnimation::create();
	anim->addSpriteFrameWithFileName("Bullet_1.png");
	anim->setDelayPerUnit(m_fLifeTime);

	CCLog("Target = %f, %f", m_vTargetPos.x, m_vTargetPos.y);
	CCAction* act = CCSequence::create(
		CCSpawn::create(
			CCAnimate::create(anim),
			CCMoveTo::create(m_fLifeTime, m_vTargetPos),
			NULL),
		CCCallFunc::create(this, callfunc_selector(Effect::kill)),
		NULL
		);

	runAction(act);
}

void Bullet::onExit()
{
	Effect::onExit();
}

Bullet* Bullet::create(const char *pszFileName)
{
	Bullet *pobSprite = new Bullet();
	if (pobSprite && pobSprite->initWithFile(pszFileName))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}