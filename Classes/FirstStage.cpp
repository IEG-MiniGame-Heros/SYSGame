#include "FirstStage.h"
#include "Hero.h"
#include "Queue.h"
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

	CCLOG("begin Database!!");
	map<string, string> m;
	int result = Database::update("123", m);
	CCLOG("end Database!!  %d", result);

	GI.Game = this;

	Queue* pQueue = Queue::create();
	addChild(pQueue);
	CCAssert((GI.Me == NULL), "Me is not null");
	GI.Me = pQueue;
	GI.Me->retain();

	Hero* pHero = Hero::create(GI.PathOfHero.c_str());
	addChild(pHero);

	Hero* pHero2 = Hero::create(GI.PathOfHero.c_str());
	addChild(pHero2);

	Hero* pHero3 = Hero::create(GI.PathOfHero.c_str());
	addChild(pHero3);

	Hero* pHero4 = Hero::create(GI.PathOfHero.c_str());
	addChild(pHero4);

	Hero* pHero5 = Hero::create(GI.PathOfHero.c_str());
	addChild(pHero5);
	pHero5->setPosition(ccp(GI.ScreenCenter.x + GI.GridSize * 3, GI.ScreenCenter.y + GI.GridSize * 3));


	// 把这几个人加进队伍里面吧
	GI.Me->appendCharacter(pHero);
	GI.Me->appendCharacter(pHero2);
	GI.Me->appendCharacter(pHero3);
	GI.Me->appendCharacter(pHero4);
}

void FirstStage::onExit()
{
	GI.Me->release();
	GI.Me = NULL;

	MainGame::onExit();
}

