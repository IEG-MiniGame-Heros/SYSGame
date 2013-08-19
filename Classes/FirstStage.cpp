#include "FirstStage.h"
#include "Hero.h"
#include "Queue.h"
#include "AllEffects.h"
#include "EntityManager.h"
#include "GameHelper.h"
#include "GameInfo.h"

#include "cocos2d.h"

#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

USING_NS_CC;

#define UPDATE_CHECK_SCORE_TIME 0.5f

cocos2d::CCScene* FirstStage::scene()
{
	CCScene * scene = NULL;

	do 
	{
		//JQ_effect
		//SimpleAudioEngine::sharedEngine()->playBackgroundMusic("music/playing2.mp3", true);

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
	GI.IsGameOver = false;


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

	Hero* p1 = EM.addAHero(GI.Helper->getGridCenter(21, 11));
	p1->setMoveVector(ccp(0, -1));
	GI.Me->addAMember(p1);
	GI.Me->refreshMembers();

	// 随机生成3只怪
	CCPoint posArr[3];
	int numOfMonster = 3;
	GI.Helper->getRandomFreeGrid(posArr, numOfMonster);
	for (int i = 0; i < numOfMonster; ++i)
	{
		EM.addAMonster(posArr[i]);
	}

	// 更新Layer，让Layer跟随精灵移动
	schedule(schedule_selector(FirstStage::updateLayer));
	updateLayer(0.f);

	// 定时刷新金币数、分数、杀怪数
	schedule(schedule_selector(FirstStage::updateAllScores), UPDATE_CHECK_SCORE_TIME);

	// 初始化结算数据
	GI.Coin = 0;
	GI.Score = 0;
	GI.ChallengeTime = 0;
	GI.MonsterKillNum = 0;
}

void FirstStage::onExit()
{
	unschedule(schedule_selector(FirstStage::updateLayer));
	unschedule(schedule_selector(FirstStage::updateAllScores));

	GI.Me->release();
	GI.Me = NULL;
	EM.removeAll();
	MainGame::onExit();
}

void FirstStage::updateLayer(float dt){
	if (GI.IsGameOver)
	{
		CCLog("Game Over");
		MainGame::createGameOverUI();
		unschedule(schedule_selector(FirstStage::updateLayer));
		//CCDirector::sharedDirector()->pause();
		return ;
	}
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
	float halfScreneWidth = visibleSize.width / 2;
	float halfScreneHeight = visibleSize.height / 2;
  
    /* 如果精灵坐标小于屏幕的一半，则取屏幕中点坐标，否则取精灵的坐标 */  
    float x = max(spritePos.x, halfScreneWidth);  
    float y = max(spritePos.y, halfScreneHeight);  
  
    /* 如果x、y的坐标大于右上角的极限值，则取极限值的坐标（极限值是指不让地图超出屏幕造成出现黑边的极限坐标） */  
    x = min(x, mapSize.width - halfScreneWidth);  
    y = min(y, mapSize.height - halfScreneHeight);  

    CCPoint destPos = CCPoint(x, y);  
    CCPoint centerPos = CCPoint(halfScreneWidth, halfScreneHeight);  

    /* 计算屏幕中点和所要移动的目的点之间的距离 */  
    CCPoint viewPos = ccpSub(centerPos, destPos);

	GI.currentLayer->setPosition(viewPos);  
	ulGameControl->setPosition(ccp(x - halfScreneWidth, y - halfScreneHeight));
}

void FirstStage::updateAllScores(float dt)
{
	if (!GI.IsGameOver)
	{
		GI.Score += GI.getSystemConfig().fTimeCoefficient * dt;
		GI.ChallengeTime += dt;

		setCoin(GI.Coin);
		setScore(int(GI.Score));
		setMonsterKillNum(GI.MonsterKillNum);
		setMin(int(GI.ChallengeTime) / 60);
		setSec(int(GI.ChallengeTime) % 60);

		if (GI.Me && GI.Me->getQueueNum() == 0)
		{
			GI.IsGameOver = true;
		}
	}
}