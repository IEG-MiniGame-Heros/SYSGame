#include "Hero.h"
#include "Queue.h"
#include "EntityManager.h"
#include "GameInfo.h"

void Hero::onEnter()
{
	Character::onEnter();

	schedule(schedule_selector(Hero::onUpdate));


	m_bIsPickedUp = false;

	// ����ʱ��һ��ʱ�����ʧ
	CCAction* fadeAway = CCSequence::create(
		CCDelayTime::create(6),
		CCBlink::create(6, 15),
		CCDelayTime::create(0.2f),
		CCCallFunc::create(this, callfunc_selector(Character::kill)),
		NULL
		);
	fadeAway->setTag(EHAT_Fade);
	runAction(fadeAway);

	// �����ٶ�
	//setCurSpeed(GI.HeroInitSpeed);
	setCurSpeed(GI.getHeroConfig()[0].fMoveSpeed);

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

void Hero::onExit()
{
	unschedule(schedule_selector(Hero::onUpdate));

	// �ͷŶ�����Դ
	m_pWalkAnim[0]->release();
	m_pWalkAnim[1]->release();
	m_pWalkAnim[2]->release();
	m_pWalkAnim[3]->release();

	Character::onExit();
}

void Hero::onUpdate(float dt)
{
	if (!m_bIsPickedUp)
	{
		return;
	}

	onMove();

	// �����û��Ӣ��Ҫ���ԡ�
	if (m_pQueue && m_pQueue->getHead() == this)
	{
		BaseEntity* entity = EM.findHeroNotInQueue(this, GI.RangeToPickupHero);
		if (entity != NULL)
		{
			m_pQueue->addAMember((Character*)(entity));
		}
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
		stopActionByTag(EHAT_Fade);
		setVisible(true);
	}
}