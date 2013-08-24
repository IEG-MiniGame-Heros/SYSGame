#include "AllEffects.h"
#include "Monster.h"
#include "EntityManager.h"
#include "GameInfo.h"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

#include <math.h>

#define PI (acos(-1.0))

//////////////////////////////////////////
/*------------- 可抛掷物 ----------------*/
void ThrowableObj::onEnter()
{
	Effect::onEnter();

	// 设置旋转
	CCPoint curPos = getPosition();
	float rot = ccpAngle(ccp(0, 1), (m_vTargetPos - curPos));
	if (m_vTargetPos.x < curPos.x)
	{
		rot *= -1;
	}
	setRotation(rot *  180 / PI);

	float slideLength = GI.getSystemConfig().fSkillSlideLen;
	slideLength = max(slideLength, getPosition().getDistance(m_vTargetPos));
	m_fLifeTime = slideLength / GI.getSkillConfig()[m_EffectType - 1].fSpeed * 0.01;
	CCPoint move_delta((m_vTargetPos - getPosition()).normalize() * slideLength);

	CCAction* act = CCSequence::create(
		CCMoveBy::create(m_fLifeTime, move_delta),
		CCCallFunc::create(this, callfunc_selector(Effect::kill)),
		NULL
		);

	// JQ_effect
	SimpleAudioEngine::sharedEngine()->playEffect("music/fire.mp3");
	runAction(act);

	// 命中范围
	m_fHitRange = GI.getSystemConfig().fHitRange;

	schedule(schedule_selector(ThrowableObj::onUpdate));
}

void ThrowableObj::onUpdate(float dt)
{
	if (!m_bIsKilled && isVisible())
	{
		Character* pEnemy = NULL;
		
		pEnemy = (Character*)EM.findNearestEntityInRange(this, m_fHitRange, m_iEnemyType);

		if (pEnemy)
		{
			// 判定伤害
			bool IsMonster = false;
			if (pEnemy->getType() == ET_Monster)
			{
				IsMonster = true;
			}
			pEnemy->getHarmed(m_iDamage, (pEnemy->getType() == ET_Monster));
			setVisible(false);
		}
	}
}

void ThrowableObj::onExit()
{
	unschedule(schedule_selector(ThrowableObj::onUpdate));

	Effect::onExit();
}

ThrowableObj* ThrowableObj::create(const char *pszFileName, EEffectType eft, EEntityType enemy_type, int damage)
{
	ThrowableObj *pobSprite = new ThrowableObj(eft, enemy_type, damage);
	if (pobSprite && pobSprite->initWithFile(pszFileName))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}


///////////////////////////////////////////////
/*--------------- 死亡爆炸动画 ----------------*/
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
/*---------------  冰冻特效   ----------------*/
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
	float frozenTime = GI.getSystemConfig().fFrozenTime;

	setOpacity(155);

	m_pMonster = pMonster;
	CCAction* act = CCSequence::create(
		CCDelayTime::create(frozenTime),
		CCCallFunc::create(this, callfunc_selector(Frozen::frozenEnd)),
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

///////////////////////////////////////////////
/*---------------  闪光特效   ----------------*/
void Flash::onEnter()
{
	Effect::onEnter();

	m_fLifeTime = 0.6f;

	CCAnimation* anim = CCAnimation::create();
	anim->addSpriteFrameWithFileName("spirit/effect/Flash_1.png");
	anim->addSpriteFrameWithFileName("spirit/effect/Flash_2.png");
	anim->addSpriteFrameWithFileName("spirit/effect/Flash_3.png");
	anim->addSpriteFrameWithFileName("spirit/effect/Flash_4.png");
	anim->addSpriteFrameWithFileName("spirit/effect/Flash_5.png");
	anim->addSpriteFrameWithFileName("spirit/effect/Flash_6.png");
	anim->addSpriteFrameWithFileName("spirit/effect/Flash_7.png");
	anim->addSpriteFrameWithFileName("spirit/effect/Flash_8.png");
	anim->addSpriteFrameWithFileName("spirit/effect/Flash_9.png");
	anim->addSpriteFrameWithFileName("spirit/effect/Flash_10.png");
	anim->addSpriteFrameWithFileName("spirit/effect/Flash_11.png");
	anim->setDelayPerUnit(m_fLifeTime / 11);

	CCAction* act = CCSequence::create(
		CCAnimate::create(anim),
		CCCallFunc::create(this, callfunc_selector(Effect::kill)),
		NULL
		);

	runAction(act);

}

void Flash::onExit()
{
	Effect::onExit();
}

Flash* Flash::create(const char *pszFileName)
{
	Flash *pobSprite = new Flash();
	if (pobSprite && pobSprite->initWithFile(pszFileName))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

///////////////////////////////////////////////
/*---------------  烟雾特效   ----------------*/
void Smog::onEnter()
{
	Effect::onEnter();

	m_fLifeTime = 0.5f;

	CCAnimation* anim = CCAnimation::create();
	anim->addSpriteFrameWithFileName("spirit/effect/Smog_1.png");
	anim->addSpriteFrameWithFileName("spirit/effect/Smog_2.png");
	anim->addSpriteFrameWithFileName("spirit/effect/Smog_3.png");
	anim->addSpriteFrameWithFileName("spirit/effect/Smog_4.png");
	anim->addSpriteFrameWithFileName("spirit/effect/Smog_5.png");
	anim->addSpriteFrameWithFileName("spirit/effect/Smog_6.png");
	anim->addSpriteFrameWithFileName("spirit/effect/Smog_7.png");
	anim->addSpriteFrameWithFileName("spirit/effect/Smog_8.png");
	anim->setDelayPerUnit(m_fLifeTime / 8);

	CCAction* act = CCSequence::create(
		CCAnimate::create(anim),
		CCCallFunc::create(this, callfunc_selector(Effect::kill)),
		NULL
		);

	runAction(act);

}

void Smog::onExit()
{
	Effect::onExit();
}

Smog* Smog::create(const char *pszFileName)
{
	Smog *pobSprite = new Smog();
	if (pobSprite && pobSprite->initWithFile(pszFileName))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

///////////////////////////////////////////////
/*---------------  星星特效   ----------------*/
void Twinkle::onEnter()
{
	Effect::onEnter();

	m_fLifeTime = 0.6f;

	CCAnimation* anim = CCAnimation::create();
	anim->addSpriteFrameWithFileName("spirit/effect/Tk_1.png");
	anim->addSpriteFrameWithFileName("spirit/effect/Tk_2.png");
	anim->addSpriteFrameWithFileName("spirit/effect/Tk_3.png");
	anim->addSpriteFrameWithFileName("spirit/effect/Tk_4.png");
	anim->addSpriteFrameWithFileName("spirit/effect/Tk_5.png");
	anim->addSpriteFrameWithFileName("spirit/effect/Tk_6.png");
	anim->addSpriteFrameWithFileName("spirit/effect/Tk_7.png");
	anim->addSpriteFrameWithFileName("spirit/effect/Tk_8.png");
	anim->addSpriteFrameWithFileName("spirit/effect/Tk_9.png");
	anim->addSpriteFrameWithFileName("spirit/effect/Tk_10.png");
	anim->addSpriteFrameWithFileName("spirit/effect/Tk_11.png");
	anim->addSpriteFrameWithFileName("spirit/effect/Tk_12.png");
	anim->setDelayPerUnit(m_fLifeTime / 12);

	CCAction* act = CCSequence::create(
		CCAnimate::create(anim),
		CCCallFunc::create(this, callfunc_selector(Effect::kill)),
		NULL
		);

	runAction(act);
}

void Twinkle::onExit()
{
	Effect::onExit();
}

Twinkle* Twinkle::create(const char *pszFileName)
{
	Twinkle *pobSprite = new Twinkle();
	if (pobSprite && pobSprite->initWithFile(pszFileName))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

void ShowNum::onEnter()
{
	Effect::onEnter();

	m_fLifeTime = 2.0f;

	setScale(0.2f);

	CCAction* act = CCSequence::create(
		CCScaleTo::create(0.2f, 1.5f, 1.5f),
		CCDelayTime::create(m_fLifeTime),
		CCCallFunc::create(this, callfunc_selector(Effect::kill)),
		NULL
		);
	runAction(act);
}

void ShowNum::onExit()
{
	Effect::onExit();
}

ShowNum* ShowNum::create(const char *pszFileName)
{
	ShowNum *pobSprite = new ShowNum();
	if (pobSprite && pobSprite->initWithFile(pszFileName))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}
