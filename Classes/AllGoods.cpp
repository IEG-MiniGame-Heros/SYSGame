#include "AllGoods.h"
#include "Queue.h"
#include "Character.h"
#include "Monster.h"
#include "EntityManager.h"
#include "GameInfo.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;


////////////////////////////////////////////
/*---------------- 金币 -------------------*/
void Coin::onEnter()
{
	Goods::onEnter();

	// 设置金币价值
	m_iValue = GI.getItemConfig()[EGT_Coin - 1].iValue;
}

void Coin::onExit()
{
	Goods::onExit();
}

void Coin::use(Hero* pHero)
{
	if (GI.Me)
	{
		// 增加个人金币
		///////////////////
		GI.Coin += m_iValue;
		GI.Score += GI.getSystemConfig().fCoinCoefficient * m_iValue;

		// 播放星星闪烁特效
		EM.addAnEffectOnCharacter(EET_Twinkle, (Character*)(pHero));
			
		SimpleAudioEngine::sharedEngine()->playEffect("music/coin.mp3");
	}

	Goods::use();
}

Coin* Coin::create(const char *pszFileName)
{
	Coin *pobSprite = new Coin();
	if (pobSprite && pobSprite->initWithFile(pszFileName))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}


////////////////////////////////////////////
/*---------------- 血包 -------------------*/
void BloodSupply::onEnter()
{
	Goods::onEnter();

	m_iSupplyAmount = GI.getItemConfig()[EGT_BloodSupply - 1].iValue;
}

void BloodSupply::onExit()
{
	Goods::onExit();
}

void BloodSupply::use(Hero* pHero)
{
	if (GI.Me && GI.Me->getQueueNum() > 0)
	{
		CCArray* members = GI.Me->getAllMembers();
		CCObject* object = NULL;
		CCARRAY_FOREACH(members, object)
		{
			((Character*)(object))->getHeal(m_iSupplyAmount);
		}
		
		SimpleAudioEngine::sharedEngine()->playEffect("music/blood.mp3");
	}

	Goods::use();
}

BloodSupply* BloodSupply::create(const char *pszFileName)
{
	BloodSupply *pobSprite = new BloodSupply();
	if (pobSprite && pobSprite->initWithFile(pszFileName))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}


////////////////////////////////////////////
/*---------------- 冰块 -------------------*/
void IceCube::onEnter()
{
	Goods::onEnter();
}

void IceCube::onExit()
{
	Goods::onExit();
}

void IceCube::use(Hero* pHero)
{
	CCArray* pAllMonsters = EM.getArrayByType(ET_Monster);
	CCObject* obj;

	CCARRAY_FOREACH(pAllMonsters, obj)
	{
		Monster* monst = (Monster*)(obj);
		monst->setFrozen(true);
	}
	
	SimpleAudioEngine::sharedEngine()->playEffect("music/glass.mp3");
	Goods::use();
}

IceCube* IceCube::create(const char *pszFileName)
{
	IceCube *pobSprite = new IceCube();
	if (pobSprite && pobSprite->initWithFile(pszFileName))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}