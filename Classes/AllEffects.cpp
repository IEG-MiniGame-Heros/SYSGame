#include "AllEffects.h"
#include "Monster.h"
#include "EntityManager.h"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

#include <math.h>

//////////////////////////////////////////
/*------------- ¿ÉÅ×ÖÀÎï ----------------*/
void ThrowableObj::onEnter()
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

	// JQ_effect
	SimpleAudioEngine::sharedEngine()->playEffect("music/gun.mp3");
	runAction(act);
}

void ThrowableObj::onExit()
{
	Effect::onExit();
}

ThrowableObj* ThrowableObj::create(const char *pszFileName)
{
	ThrowableObj *pobSprite = new ThrowableObj();
	if (pobSprite && pobSprite->initWithFile(pszFileName))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}


///////////////////////////////////////////////
/*--------------- ËÀÍö±¬Õ¨¶¯»­ ----------------*/
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


///////////////////////////////////////////////
/*---------------  ±ù¶³ÌØÐ§   ----------------*/
void Frozen::onEnter()
{
	Effect::onEnter();


}

void Frozen::onExit()
{
	Effect::onExit();
}

void Frozen::frozenStart(Monster* pMonster)
{
	m_pMonster = pMonster;
	CCAction* act = CCSequence::create(
		CCDelayTime::create(20.f),
		CCCallFunc::create(this, callfunc_selector(Effect::kill)),
		NULL
		);
	act->setTag(EEAT_Frozenning);
	runAction(act);
}

void Frozen::frozenEnd()
{
	if (m_pMonster)
	{
		m_pMonster->setFrozen(false);
	}
}

void Frozen::stopFrozen()
{
	stopActionByTag(EEAT_Frozenning);
}

Frozen* Frozen::create(const char *pszFileName)
{
	Frozen *pobSprite = new Frozen();
	if (pobSprite && pobSprite->initWithFile(pszFileName))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}