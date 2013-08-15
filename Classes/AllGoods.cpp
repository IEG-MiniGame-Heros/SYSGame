#include "AllGoods.h"
#include "Queue.h"
#include "Character.h"
#include "GameInfo.h"


////////////////////////////////////////////
/*---------------- 金币 -------------------*/
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

	m_iSupplyAmount = 30;
}

void BloodSupply::onExit()
{
	Goods::onExit();
}

void BloodSupply::use()
{
	//道具号：1->血包,吃一个血包+30
	//GameInfo info;
	//vector<TItem> tem_config=info.getItemConfig();
	//vector<TItem>::iterator iter;
	//for(iter = tem_config.begin(); iter!= tem_config.end(); iter++) 
	//{
	//	if (iter->eType==2){
	//		if(m_iID==EGT_BloodSupply){		
	//			Character* pHead = NULL;
	//			pHead = pHead->getQueue()->getHead();
	//			int bloods=pHead->getCurHealth();
	//			bloods+=30;
	//			pHead->setCurHealth(bloods);
	//			break;
	//		}			
	//	}
	//}

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