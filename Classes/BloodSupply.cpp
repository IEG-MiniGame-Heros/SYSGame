#include "BloodSupply.h"
#include "Queue.h"
#include "FirstStage.h"
#include "EntityManager.h"
#include "GameInfo.h"
#include "Character.h"


//BloodSupply::BloodSupply()
//{
//	setType(ET_Goods);
//}

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

		// 吃完了，不要你了。。。ByeBye
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


////绘制血条
//void BloodSupply::draw() 
//{
//	CCLayer *layer = NULL;
//	layer->draw();
//	CCSize s =CCDirector::sharedDirector()->getWinSize();
//	ccDrawColor4F(0.0, 0.0, 0.0, 1.0);
//	glLineWidth(10);    //  instead of glColor4f
//	cocos2d::ccDrawLine(CCPointMake(5, s.height - 10), CCPointMake(115, s.height - 10));
//	glLineWidth(5);
//	cocos2d::ccDrawColor4F(1, 0, 0, 0);  
//	Character* pHead = NULL;
//	pHead = pHead->getQueue()->getHead();
//	int bloods=pHead->getCurHealth();
//	cocos2d::ccDrawLine(CCPointMake(10, s.height - 11), CCPointMake(10 + bloods, s.height - 11));
//}