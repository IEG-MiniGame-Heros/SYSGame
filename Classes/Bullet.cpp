#include "Bullet.h"
#include "EntityManager.h"
#include <math.h>

void Bullet::onEnter()
{
	Effect::onEnter();

	m_fLifeTime = 1.0f;
	m_bShouldMove = true;

	CCAnimation* anim = CCAnimation::create();
	anim->addSpriteFrameWithFileName("spirit/skill/Bullet_1.png");
	anim->setDelayPerUnit(m_fLifeTime);

	float length = max(600.f, getPosition().getDistance(m_vTargetPos));
	CCPoint move_delta((m_vTargetPos - getPosition()).normalize() * length);

	CCAction* act = CCSequence::create(
		CCSpawn::create(
			CCMoveBy::create(m_fLifeTime, move_delta),
			CCAnimate::create(anim),
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