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


	// ��ȡ��Ļ��Ⱥ͸߶�
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	CCPoint center = ccp(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);

	CCTMXTiledMap *map = CCTMXTiledMap::create("TileMaps/orthogonal-test-zorder.tmx");
	addChild(map, 0, 1);
	map->setPosition(ccp(0, 0));
	


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


	// ���⼸���˼ӽ����������
	GI.Me->appendCharacter(p1);
	GI.Me->appendCharacter(p2);
	GI.Me->appendCharacter(p3);
	GI.Me->appendCharacter(p4);

	Monster* m1 = EM.addAMonster(ccp(0, 0) + ccp(GI.GridSize * 3, GI.GridSize * 12));
	//FireBall* b1 = (FireBall*)EM.addAnEffect(ccp(0, 0) + ccp(GI.GridSize * 2, GI.GridSize * 10), EET_FireBall);
	p1->addChild(SkillFireAttack::create());
}

void FirstStage::onExit()
{
	GI.Me->release();
	GI.Me = NULL;

	MainGame::onExit();
}

