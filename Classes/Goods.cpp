#include "Goods.h"
#include "Queue.h"
#include "FirstStage.h"
#include "EntityManager.h"
#include "GameInfo.h"
#include "Character.h"

class Character;
class Queue;
Goods::Goods()
{
	setType(ET_Goods);
}

void Goods::onEnter()
{
	//CCDirector *pDirector= CCDirector::sharedDirector();
	//pDirector->getTouchDispatcher()->addTargetedDelegate(this,0,true);
	CCSprite::onEnter();
}

void Goods::onExit()
{
//	CCDirector *pDirector= CCDirector::sharedDirector();
//	pDirector->getTouchDispatcher()->removeDelegate(this);
	CCSprite::onEnter();
}

void Goods::use()
{
	//道具号：1->血包,吃一个血包+30
	GameInfo info;
	vector<TItem> tem_config=info.getItemConfig();
		vector<TItem>::iterator iter;
		for(iter = tem_config.begin(); iter!= tem_config.end(); iter++) 
		{
			if (iter->eType==2){
				if(m_iID==EGT_BloodSupply){					
					Character* pHead=pHead->getQueue()->getHead();
					int bloods=pHead->getCurHealth();
					bloods+=30;
					pHead->setCurHealth(bloods);
					//加血后删除此条道具
					std:string sql = "delete from t_item where id=i+1 from t_item order by id asc";					
					vector<map<string, string> > temp;
					Database::query(sql,temp);
					break;
				}			
			}
		}

	
}