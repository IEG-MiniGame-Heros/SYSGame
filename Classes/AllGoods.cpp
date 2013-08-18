#include "AllGoods.h"
#include "Queue.h"
#include "Character.h"
#include "Monster.h"
#include "EntityManager.h"
#include "GameInfo.h"


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

void Coin::use()
{
	if (GI.Me)
	{
		// 增加个人金币
		///////////////////
		GI.Coin += m_iValue;
		GI.Score += GI.getSystemConfig().fCoinCoefficient * m_iValue;
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

void BloodSupply::use()
{
	if (GI.Me && GI.Me->getQueueNum() > 0)
	{
		CCArray* members = GI.Me->getAllMembers();
		CCObject* object = NULL;
		CCARRAY_FOREACH(members, object)
		{
			((Character*)(object))->getHeal(m_iSupplyAmount);
		}

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

void IceCube::use()
{
	CCArray* pAllMonsters = EM.getArrayByType(ET_Monster);
	CCObject* obj;

	CCARRAY_FOREACH(pAllMonsters, obj)
	{
		Monster* monst = (Monster*)(obj);
		monst->setFrozen(true);
	}

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