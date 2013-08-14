#include "Hero.h"
#include "Queue.h"
#include "Goods.h"
#include "EntityManager.h"
#include "SkillFireAttack.h"
#include "GameHelper.h"
#include "GameInfo.h"

void Hero::onEnter()
{
	Character::onEnter();

	schedule(schedule_selector(Hero::onUpdate));


	m_bIsPickedUp = false;

	// 倒计时，一定时间后消失
	CCAction* fadeAway = CCSequence::create(
		CCDelayTime::create(6),
		CCBlink::create(6, 15),
		CCDelayTime::create(0.2f),
		CCCallFunc::create(this, callfunc_selector(Character::kill)),
		NULL
		);
	fadeAway->setTag(EHAT_Fade);
	runAction(fadeAway);

	// 设置速度
	setCurSpeed(GI.getHeroConfig()[0].fMoveSpeed);
	setMaxSpeed(GI.getSystemConfig().fMaxMoveSpeed);
	m_fSpeedIncrement = GI.getSystemConfig().fSpeedIncrement;

	// 设置生命
	setCurHealth(GI.getHeroConfig()[0].iHP);
	setMaxHealth(GI.getHeroConfig()[0].iHP);

	// 设置技能
	addChild(SkillFireAttack::create());

	// 设置动画
	// 0.右 1.下 2.左 3.上 

	m_pWalkAnim[0] = CCAnimation::create();
	m_pWalkAnim[0]->retain();
	m_pWalkAnim[0]->addSpriteFrameWithFileName("spirit/hero/Hero1_R_1.png");
	m_pWalkAnim[0]->addSpriteFrameWithFileName("spirit/hero/Hero1_R_2.png");
	m_pWalkAnim[0]->addSpriteFrameWithFileName("spirit/hero/Hero1_R_3.png");
	m_pWalkAnim[0]->setDelayPerUnit(1.f / getCurSpeed() / 3);

	m_pWalkAnim[1] = CCAnimation::create();
	m_pWalkAnim[1]->retain();
	m_pWalkAnim[1]->addSpriteFrameWithFileName("spirit/hero/Hero1_D_1.png");
	m_pWalkAnim[1]->addSpriteFrameWithFileName("spirit/hero/Hero1_D_2.png");
	m_pWalkAnim[1]->setDelayPerUnit(0.5 / getCurSpeed());
	
	m_pWalkAnim[2] = CCAnimation::create();
	m_pWalkAnim[2]->retain();
	m_pWalkAnim[2]->addSpriteFrameWithFileName("spirit/hero/Hero1_L_1.png");
	m_pWalkAnim[2]->addSpriteFrameWithFileName("spirit/hero/Hero1_L_2.png");
	m_pWalkAnim[2]->addSpriteFrameWithFileName("spirit/hero/Hero1_L_3.png");
	m_pWalkAnim[2]->setDelayPerUnit(1.f / getCurSpeed() / 3);

	m_pWalkAnim[3] = CCAnimation::create();
	m_pWalkAnim[3]->retain();
	m_pWalkAnim[3]->addSpriteFrameWithFileName("spirit/hero/Hero1_U_1.png");
	m_pWalkAnim[3]->addSpriteFrameWithFileName("spirit/hero/Hero1_U_2.png");
	m_pWalkAnim[3]->setDelayPerUnit(0.5 / getCurSpeed());	
}

void Hero::setAnimFreq()
{
	m_pWalkAnim[0]->setDelayPerUnit(1.f / getCurSpeed() / 3);
	m_pWalkAnim[1]->setDelayPerUnit(0.5 / getCurSpeed());
	m_pWalkAnim[2]->setDelayPerUnit(1.f / getCurSpeed() / 3);
	m_pWalkAnim[3]->setDelayPerUnit(0.5 / getCurSpeed());
}

void Hero::onExit()
{
	unschedule(schedule_selector(Hero::onUpdate));

	// 释放动画资源
	m_pWalkAnim[0]->release();
	m_pWalkAnim[1]->release();
	m_pWalkAnim[2]->release();
	m_pWalkAnim[3]->release();

	Character::onExit();
}

void Hero::onUpdate(float dt)
{
	// 如果这个英雄还没被拾取
	if (!m_bIsPickedUp)
	{
		return;
	}

	// 检查有没有英雄要“吃”
	if (m_pQueue && m_pQueue->getHead() == this)
	{
		BaseEntity* entity = EM.findHeroNotInQueue(this, GI.RangeToPickupHero);
		if (entity != NULL)
		{
			m_pQueue->addAMember((Character*)(entity));

			// 吃了之后，增加速度
			float speed = min(m_fMaxSpeed, m_fCurSpeed + m_fSpeedIncrement);
			m_pQueue->setCurSpeed(speed);
			CCLog("After Adding, Speed: %f", getCurSpeed());
		}
	}

	if (!onMove())
	{
		return;
	}	

	// 检查有没有物品可以使用
	Goods* pGood = (Goods*)(EM.findEntityInRange(this, 60.f, ET_Goods));
	if (pGood)
	{
		pGood->use();
	}

	// 检测是否撞到小怪了
	BaseEntity* entity = EM.findEntityInRange(this, 35.f, ET_Monster);
	if (entity)
	{
		// 这个怪死了
		((Character*)(entity))->kill();

		// 我也死了，呜呜呜>_<
		kill();
	}
}

Hero* Hero::create(const char *pszFileName)
{
	Hero *pobSprite = new Hero();
	if (pobSprite && pobSprite->initWithFile(pszFileName))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

Hero::Hero()
{
	setType(ET_Hero);
}

void Hero::setIsPickedUp(bool is_picked_up)
{
	m_bIsPickedUp = is_picked_up;
	
	// 英雄被获取了，就把闪烁动画给停了
	if (m_bIsPickedUp)
	{
		stopActionByTag(EHAT_Fade);
		setVisible(true);
	}
}