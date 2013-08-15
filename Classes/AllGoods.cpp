#include "AllGoods.h"
#include "Queue.h"
#include "Character.h"
#include "GameInfo.h"


////////////////////////////////////////////
/*---------------- ��� -------------------*/
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


////////////////////////////////////////////
/*---------------- Ѫ�� -------------------*/
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
	//���ߺţ�1->Ѫ��,��һ��Ѫ��+30
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

		// �����ˣ���Ҫ���ˡ�����ByeBye
		kill();
	}
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