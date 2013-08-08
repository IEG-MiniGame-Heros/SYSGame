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
		CCDelayTime::create(2),
		CCBlink::create(2, 5),
		CCCallFunc::create(this, callfunc_selector(Character::kill)),
		NULL
		);
	fadeAway->setTag(EHAT_Fade);
	runAction(fadeAway);

	// �����ٶ�
	setCurSpeed(GI.HeroInitSpeed);
	setMaxSpeed(GI.HeroMaxSpeed);

	// ���ö���
	// 0.�� 1.�� 2.�� 3.��
	m_pWalkAnim[0] = CCAnimation::create();
	m_pWalkAnim[0]->retain();
	m_pWalkAnim[0]->addSpriteFrameWithFileName("Hero1_1.png");
	m_pWalkAnim[0]->addSpriteFrameWithFileName("Hero1_2.png");
	m_pWalkAnim[0]->setDelayPerUnit(0.5 / getCurSpeed());
	
	
}

void Hero::onExit()
{
	unschedule(schedule_selector(Hero::onUpdate));

	// �ͷŶ�����Դ
	m_pWalkAnim[0]->release();

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
			m_pQueue->appendCharacter((Character*)(entity));
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
	}
}