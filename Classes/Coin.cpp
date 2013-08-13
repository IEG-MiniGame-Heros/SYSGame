#include "Coin.h"
#include "GameInfo.h"

void Coin::onEnter()
{
	Goods::onEnter();

	// ���ý�Ҽ�ֵ
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
		// ���Ӹ��˽��
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