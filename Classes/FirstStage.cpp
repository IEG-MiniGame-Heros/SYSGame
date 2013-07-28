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

	GI.Game = this;

	setTouchEnabled(true);

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

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

