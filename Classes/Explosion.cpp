#include "Explosion.h"

void Explosion::onEnter()
{
	Effect::onEnter();

	m_fLifeTime = 0.5f;

	CCAnimation* anim = CCAnimation::create();
	anim->addSpriteFrameWithFileName("spirit/effect/Explosion_1.png");
	anim->addSpriteFrameWithFileName("spirit/effect/Explosion_2.png");
	anim->addSpriteFrameWithFileName("spirit/effect/Explosion_3.png");
	anim->addSpriteFrameWithFileName("spirit/effect/Explosion_4.png");
	anim->addSpriteFrameWithFileName("spirit/effect/Explosion_5.png");
	anim->addSpriteFrameWithFileName("spirit/effect/Explosion_6.png");
	anim->addSpriteFrameWithFileName("spirit/effect/Explosion_7.png");
	anim->setDelayPerUnit(m_fLifeTime / 7);

	CCAction* act = CCSequence::create(
		CCAnimate::create(anim),
		CCCallFunc::create(this, callfunc_selector(Effect::kill)),
		NULL
		);


	runAction(act);
}

void Explosion::onExit()
{
	Effect::onExit();
}

Explosion* Explosion::create(const char *pszFileName)
{
	Explosion *pobSprite = new Explosion();
	if (pobSprite && pobSprite->initWithFile(pszFileName))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}