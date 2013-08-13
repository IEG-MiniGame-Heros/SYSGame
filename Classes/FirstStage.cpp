#include "FirstStage.h"
#include "Hero.h"
#include "Queue.h"
#include "FireBall.h"
#include "SkillFireAttack.h"
#include "SkillBulletAttack.h"
#include "EntityManager.h"
#include "GameHelper.h"
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

	CCTMXTiledMap *map = CCTMXTiledMap::create("map/Map06.tmx");
	addChild(map, 0, 1);
	map->setPosition(ccp(0, 0));
	GI.Map = map;
	GI.MapHeight = map->getContentSize().height;
	GI.MapWidth = map->getContentSize().width;
	CCLog("MapSize = %f, %f", GI.MapWidth, GI.MapHeight);
	
    /* 加载对象层的所有对象 */
    //CCTMXObjectGroup* objGroup = map->objectGroupNamed("objects");

    /* 加载meta层 */
	CCTMXLayer*	meta = map->layerNamed("meta");
    GI.Meta = meta;
    GI.Meta->setVisible(false);

    /* 加载障碍物层 */
    //GI.Barrier = map->layerNamed("barrier");

	// 初始化GameHelper, 一定要放在地图加载之后
	GI.Helper = GameHelper::create();
	addChild(GI.Helper);
	////////////////////////////////////////


	Queue* pQueue = Queue::create();
	addChild(pQueue);
	CCAssert((GI.Me == NULL), "Me is not null");
	GI.Me = pQueue;
	GI.Me->retain();

	Hero* p1 = EM.addAHero(ccp(100, 100));
	Hero* p2 = EM.addAHero(ccp(100, 100));
	Hero* p3 = EM.addAHero(ccp(100, 100));
	Hero* p4 = EM.addAHero(ccp(100, 100));
	Hero* p5 = EM.addAHero(ccp(100, 100));

	//p5->setPosition(GI.Helper->getGridCenter(11, 11));


	// 把这几个人加进队伍里面吧
	GI.Me->addAMember(p1);
	GI.Me->addAMember(p2);
	GI.Me->addAMember(p3);
	GI.Me->addAMember(p4);
	GI.Me->refreshMembers();

	/// 测试，给第一个英雄增加一个技能
	p1->addChild(SkillFireAttack::create());
	p2->addChild(SkillBulletAttack::create());

	Monster* m1 = EM.addAMonster(GI.Helper->getGridCenter(3, 12));
	Monster* m2 = EM.addAMonster(GI.Helper->getGridCenter(7, 13));
	Monster* m3 = EM.addAMonster(GI.Helper->getGridCenter(12, 5));
	
	// 测试，增加血包、金币
	EM.addAGoods(GI.Helper->getGridCenter(10, 10), EGT_BloodSupply);
	EM.addAGoods(GI.Helper->getGridCenter(15, 15), EGT_Coin);

	// 更新Layer，让Layer跟随精灵移动
	this->schedule(schedule_selector(FirstStage::updateLayer));
}

void FirstStage::onExit()
{
	unschedule(schedule_selector(FirstStage::updateLayer));

	GI.Me->release();
	GI.Me = NULL;
	MainGame::onExit();
}

void FirstStage::updateLayer(float dt){
	if (GI.Me && GI.Me->getQueueNum() <= 0) {  
        return;  
    }  
    //CCLayer* parent = (CCLayer* )GI.Me->getHead()->getParent();  
  
	/* 地图方块数量 */      
	CCSize mapTiledNum = GI.Map->getMapSize();  
  
    /* 地图单个格子大小 */  
	CCSize tiledSize = GI.Map->getTileSize();  
      
	/* 地图大小 */  
    CCSize mapSize = CCSize(  
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

    CCPoint destPos = CCPoint(x, y);  
    CCPoint centerPos = CCPoint(visibleSize.width / 2, visibleSize.height / 2);  

    /* 计算屏幕中点和所要移动的目的点之间的距离 */  
    CCPoint viewPos = ccpSub(centerPos, destPos);  

	GI.currentLayer->setPosition(viewPos);  
}