#include "Hero.h"
#include "Queue.h"
#include "Goods.h"
#include "EntityManager.h"
#include "AllSkills.h"
#include "GameHelper.h"
#include "GameInfo.h"

#define HERO_UNBEATABLE 0

void Hero::onEnter()
{
	Character::onEnter();

	//schedule(schedule_selector(Hero::onUpdate));


	m_bIsPickedUp = false;

	// ����ʱ��һ��ʱ�����ʧ
	int flashTimes = int(/*GI.getSystemConfig().fFlashingTime*/ 5 * 2.5);
	CCAction* fadeAway = CCSequence::create(
		CCDelayTime::create(/*float(GI.getItemConfig()[2].iExistTime)*/ 5.f),
		CCBlink::create(float(GI.getSystemConfig().fFlashingTime), flashTimes),
		CCDelayTime::create(0.2f),
		CCCallFunc::create(this, callfunc_selector(Character::kill)),
		NULL
		);
	fadeAway->setTag(ECAT_HeroFade);
	runAction(fadeAway);

	// �����ٶ�
	setCurSpeed(GI.getHeroConfig()[0].fMoveSpeed); 
	setMaxSpeed(GI.getSystemConfig().fMaxMoveSpeed);
	m_fSpeedIncrement = GI.getSystemConfig().fSpeedIncrement;

	// ��������
	setCurHealth(GI.getHeroConfig()[0].iHP);
	setMaxHealth(GI.getHeroConfig()[0].iHP);

	// ��ʾѪ�����ش�
	m_bEnableShowHP = true;

	// ���ü���
	//addChild(SkillFireAttack::create());

	// ���ö���
	// 0.�� 1.�� 2.�� 3.�� 

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
	//unschedule(schedule_selector(Hero::onUpdate));

	// �ͷŶ�����Դ
	m_pWalkAnim[0]->release();
	m_pWalkAnim[1]->release();
	m_pWalkAnim[2]->release();
	m_pWalkAnim[3]->release();

	Character::onExit();
}

void Hero::onUpdate(float dt)
{
	// ������Ӣ�ۻ�û��ʰȡ
	if (!m_bIsPickedUp)
	{
		return;
	}

	// �����û��Ӣ��Ҫ���ԡ�
	if (m_pQueue && m_pQueue->getHead() == this)
	{
		BaseEntity* entity = EM.findHeroNotInQueue(this, GI.RangeToPickupHero);
		if (entity != NULL)
		{
			m_pQueue->addAMember((Character*)(entity));

			// ����֮�������ٶ�
			float speed = min(m_fMaxSpeed, m_fCurSpeed + m_fSpeedIncrement);
			m_pQueue->setCurSpeed(speed);
			CCLog("After Adding, Speed: %f", getCurSpeed());
		}
	}

	if (!onMove())
	{
		return;
	}	

	// �����û����Ʒ����ʹ��
	Goods* pGood = (Goods*)(EM.findEntityInRange(this, 60.f, ET_Goods));
	if (pGood)
	{
		pGood->use();
	}

	// ����Ƿ�ײ��С����
	BaseEntity* entity = EM.findEntityInRange(this, 35.f, ET_Monster);
	if (entity)
	{
		// ���������
		((Character*)(entity))->kill();

		// ��Ҳ���ˣ�������>_<
#if !HERO_UNBEATABLE
		kill();
#endif
	}

	// ���ײ��ǽ��
	// ��ͼ��ײ����������� @��ǿ
	if (!GI.Helper->isWithinMap(getPosition(), 20.f))
	{
		// ȫ������ȥ���ɣ�������
		m_pQueue->allGotoDie();
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
	
	// Ӣ�۱���ȡ�ˣ��Ͱ���˸������ͣ��
	if (m_bIsPickedUp)
	{
		stopActionByTag(ECAT_HeroFade);
		setVisible(true);
	}
}