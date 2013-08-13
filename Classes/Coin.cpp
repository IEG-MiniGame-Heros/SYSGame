#include "Coin.h"
#include "GameInfo.h"

void Coin::onEnter()
{
	Goods::onEnter();

	// 设置金币价值
	m_iValue = 20; 
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

		kill();
	}
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