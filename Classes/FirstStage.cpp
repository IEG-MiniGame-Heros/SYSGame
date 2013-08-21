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


	// ��ȡ��Ļ��Ⱥ͸߶�
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
	
    /* ���ض��������ж��� */
    //CCTMXObjectGroup* objGroup = map->objectGroupNamed("objects");

    /* ����meta�� */
	CCTMXLayer*	meta = map->layerNamed("meta");
    GI.Meta = meta;
    GI.Meta->setVisible(false);

    /* �����ϰ���� */
    //GI.Barrier = map->layerNamed("barrier");

	// ��ʼ��GameHelper, һ��Ҫ���ڵ�ͼ����֮��
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

	// �������3ֻ��
	CCPoint posArr[3];	
	int curMonstNum = 0;
	while (curMonstNum < 3)
	{
		int needNum = 1;
		GI.Helper->getRandomFreeGrid(posArr, needNum);
		int i, j;
		GI.Helper->getGridIndexOfPos(posArr[0], i, j);
		if (i < 15)
		{
			++curMonstNum;
			EM.addAMonster(posArr[0]);
		}
	}

	// ����Layer����Layer���澫���ƶ�
	schedule(schedule_selector(FirstStage::updateLayer));
	updateLayer(0.f);

	// ��ʱˢ�½������������ɱ����
	schedule(schedule_selector(FirstStage::updateAllScores), UPDATE_CHECK_SCORE_TIME);

	// ��ʼ����������
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
  
	/* ��ͼ�������� */      
	CCSize mapTiledNum = GI.Map->getMapSize();  
  
    /* ��ͼ�������Ӵ�С */  
	CCSize tiledSize = GI.Map->getTileSize();  
      
	/* ��ͼ��С */  
    CCSize mapSize = CCSize(  
        mapTiledNum.width * tiledSize.width,   
        mapTiledNum.height * tiledSize.height
	);  
  
    /* ��Ļ��С */  
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();  
  
    /* ��������꣬ȡ��һ������ */  
    CCPoint spritePos = GI.Me->getHead()->getPosition();  
	float halfScreneWidth = visibleSize.width / 2;
	float halfScreneHeight = visibleSize.height / 2;
  
    /* �����������С����Ļ��һ�룬��ȡ��Ļ�е����꣬����ȡ��������� */  
    float x = max(spritePos.x, halfScreneWidth);  
    float y = max(spritePos.y, halfScreneHeight);  
  
    /* ���x��y������������Ͻǵļ���ֵ����ȡ����ֵ�����꣨����ֵ��ָ���õ�ͼ������Ļ��ɳ��ֺڱߵļ������꣩ */  
    x = min(x, mapSize.width - halfScreneWidth);  
    y = min(y, mapSize.height - halfScreneHeight);  

    CCPoint destPos = CCPoint(x, y);  
    CCPoint centerPos = CCPoint(halfScreneWidth, halfScreneHeight);  

    /* ������Ļ�е����Ҫ�ƶ���Ŀ�ĵ�֮��ľ��� */  
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