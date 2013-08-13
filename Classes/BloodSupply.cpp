#include "BloodSupply.h"
#include "Queue.h"
#include "FirstStage.h"
#include "EntityManager.h"
#include "GameInfo.h"
#include "Character.h"


class Character;
class Queue;
BloodSupply::BloodSupply()
{
	setType(ET_Goods);
}

void BloodSupply::onEnter()
{
	//CCDirector *pDirector= CCDirector::sharedDirector();
	//pDirector->getTouchDispatcher()->addTargetedDelegate(this,0,true);
	CCSprite::onEnter();
}

void BloodSupply::onExit()
{
	//	CCDirector *pDirector= CCDirector::sharedDirector();
	//	pDirector->getTouchDispatcher()->removeDelegate(this);
	CCSprite::onEnter();
}

void BloodSupply::use()
{
	//道具号：1->血包,吃一个血包+30
	GameInfo info;
	vector<TItem> tem_config=info.getItemConfig();
	vector<TItem>::iterator iter;
	for(iter = tem_config.begin(); iter!= tem_config.end(); iter++) 
	{
		if (iter->eType==2){
			if(m_iID==EGT_BloodSupply){		
				Character* pHead = NULL;
				pHead = pHead->getQueue()->getHead();
				int bloods=pHead->getCurHealth();
				bloods+=30;
				pHead->setCurHealth(bloods);
				break;
			}			
		}
	}


}
//绘制血条
void BloodSupply::draw() 
{
	CCLayer *layer;
	layer->draw();
	CCSize s =CCDirector::sharedDirector()->getWinSize();
	ccDrawColor4F(0.0, 0.0, 0.0, 1.0);
	glLineWidth(10);    //  instead of glColor4f
	cocos2d::ccDrawLine(CCPointMake(5, s.height - 10), CCPointMake(115, s.height - 10));
	glLineWidth(5);
	cocos2d::ccDrawColor4F(1, 0, 0, 0);  
	Character* pHead = NULL;
	pHead = pHead->getQueue()->getHead();
	int bloods=pHead->getCurHealth();
	cocos2d::ccDrawLine(CCPointMake(10, s.height - 11), CCPointMake(10 + bloods, s.height - 11));
}