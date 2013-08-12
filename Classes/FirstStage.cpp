#include "FirstStage.h"
#include "Hero.h"
#include "Queue.h"
#include "FireBall.h"
#include "SkillFireAttack.h"
#include "SkillBulletAttack.h"
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


	// ��ȡ��Ļ���Ⱥ͸߶�
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


	// ���⼸���˼ӽ�����������
	GI.Me->addAMember(p1);
	GI.Me->addAMember(p2);
	GI.Me->addAMember(p3);
	GI.Me->addAMember(p4);
	GI.Me->refreshMembers();

	Monster* m1 = EM.addAMonster(ccp(0, 0) + ccp(GI.GridSize * 3, GI.GridSize * 12));
	Monster* m2 = EM.addAMonster(ccp(0, 0) + ccp(GI.GridSize * 7, GI.GridSize * 13));
	Monster* m3 = EM.addAMonster(ccp(0, 0) + ccp(GI.GridSize * 12, GI.GridSize * 5));
	//
	/// ���ԣ�����һ��Ӣ������һ������
	p1->addChild(SkillFireAttack::create());
	p2->addChild(SkillBulletAttack::create());

	// ����Layer����Layer���澫���ƶ�
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
	if(GI.Me->getHead() == NULL) {  
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
  
    /* ���������꣬ȡ��һ������ */  
    CCPoint spritePos = GI.Me->getHead()->getPosition();  
  
    /* ������������С����Ļ��һ�룬��ȡ��Ļ�е����꣬����ȡ���������� */  
    float x = max(spritePos.x, visibleSize.width / 2);  
    float y = max(spritePos.y, visibleSize.height / 2);  
  
    /* ����x��y�������������Ͻǵļ���ֵ����ȡ����ֵ�����꣨����ֵ��ָ���õ�ͼ������Ļ���ɳ��ֺڱߵļ������꣩ */  
    x = min(x, mapSize.width - visibleSize.width / 2);  
    y = min(y, mapSize.height - visibleSize.height / 2);  

    CCPoint destPos = CCPoint(x, y);  
    CCPoint centerPos = CCPoint(visibleSize.width / 2, visibleSize.height / 2);  

    /* ������Ļ�е�����Ҫ�ƶ���Ŀ�ĵ�֮���ľ��� */  
    CCPoint viewPos = ccpSub(centerPos, destPos);  

	GI.currentLayer->setPosition(viewPos);  
}
