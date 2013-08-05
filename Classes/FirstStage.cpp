#include "FirstStage.h"
#include "Hero.h"
#include "Queue.h"
#include "FireBall.h"
#include "SkillFireAttack.h"
#include "EntityManager.h"
#include "GameInfo.h"

#include "cocos2d.h"

USING_NS_CC;

cocos2d::CCScene* FirstStage::scene()
{
	CCScene * scene = NULL;

	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		FirstStage *layer = FirstStage::create();
		GI.currentLayer = layer;
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}

void FirstStage::onEnter()
{
	MainGame::onEnter();
	GI.Game = this;


	// 获取屏幕宽度和高度
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	CCPoint center = ccp(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);

	CCTMXTiledMap *map = CCTMXTiledMap::create("Map04.tmx");
	addChild(map, 0, 1);
	map->setPosition(ccp(0, 0));
	GI.Map = map;
	


	Queue* pQueue = Queue::create();
	addChild(pQueue);
	CCAssert((GI.Me == NULL), "Me is not null");
	GI.Me = pQueue;
	GI.Me->retain();

	Hero* p1 = EM.addAHero(ccp(0, 0));
	Hero* p2 = EM.addAHero(ccp(0, 0));
	Hero* p3 = EM.addAHero(ccp(0, 0));
	Hero* p4 = EM.addAHero(ccp(0, 0));
	Hero* p5 = EM.addAHero(ccp(0, 0));

	p5->setPosition(ccp(center.x + GI.GridSize * 3, center.y + GI.GridSize * 3));


	// 把这几个人加进队伍里面吧
	GI.Me->appendCharacter(p1);
	GI.Me->appendCharacter(p2);
	GI.Me->appendCharacter(p3);
	GI.Me->appendCharacter(p4);

	Monster* m1 = EM.addAMonster(ccp(0, 0) + ccp(GI.GridSize * 3, GI.GridSize * 12));
	//FireBall* b1 = (FireBall*)EM.addAnEffect(ccp(0, 0) + ccp(GI.GridSize * 2, GI.GridSize * 10), EET_FireBall);
	p1->addChild(SkillFireAttack::create());

	// 更新Layer，让Layer跟随精灵移动
	this->schedule(schedule_selector(FirstStage::updateLayer), 0.01);
}

void FirstStage::onExit()
{
	GI.Me->release();
	GI.Me = NULL;
	MainGame::onExit();
}

/*
void FirstStage::updateLayer(float dt){
	CCLog("UPdate2");
	char m[256];

	CCTMXTiledMap *map = GI.Map;

	if(GI.Me != NULL && GI.Map != NULL){
		CCPoint hero = GI.Me->getHead()->getPosition();
		int mapWidth = GI.Map->getMapSize().width * GI.Map->getTileSize().width;
		float x = hero.x - mapWidth/2;
		float y = hero.y;
		CCSize s = GI.Map->getContentSize();
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		GI.currentLayer->setPosition(ccp(-s.width/2+winSize.width/2-x, -y));
	}
}
*/

void FirstStage::updateLayer(float dt){
	if(GI.Me->getHead() == NULL) {  
        return;  
    }  
    //CCLayer* parent = (CCLayer* )GI.Me->getHead()->getParent();  
  
	/* 地图方块数量 */      
	CCSize mapTiledNum = GI.Map->getMapSize();  
  
    /* 地图单个格子大小 */  
	CCSize tiledSize = GI.Map->getTileSize();  
      
	/* 地图大小 */  
    CCSize mapSize = CCSize::CCSize(  
        mapTiledNum.width * tiledSize.width,   
        mapTiledNum.height * tiledSize.height
	);  
  
    /* 屏幕大小 */  
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();  
  
    /* 精灵的坐标，取第一个精灵 */  
    CCPoint spritePos = GI.Me->getHead()->getPosition();  
  
    /* 如果精灵坐标小于屏幕的一半，则取屏幕中点坐标，否则取精灵的坐标 */  
    float x = max(spritePos.x, visibleSize.width / 2);  
    float y = max(spritePos.y, visibleSize.height / 2);  
  
    /* 如果x、y的坐标大于右上角的极限值，则取极限值的坐标（极限值是指不让地图超出屏幕造成出现黑边的极限坐标） */  
    x = min(x, mapSize.width - visibleSize.width / 2);  
    y = min(y, mapSize.height - visibleSize.height / 2);  

    CCPoint destPos = CCPoint::CCPoint(x, y);  
    CCPoint centerPos = CCPoint::CCPoint(visibleSize.width / 2, visibleSize.height / 2);  

    /* 计算屏幕中点和所要移动的目的点之间的距离 */  
    CCPoint viewPos = ccpSub(centerPos, destPos);  

	GI.currentLayer->setPosition(viewPos);  
}