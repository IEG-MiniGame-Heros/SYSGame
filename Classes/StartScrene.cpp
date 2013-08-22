#include "StartScrene.h"
#include "SoundScrene.h"
#include "IntroduceScrene.h"
#include "FirstStage.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;


bool StartScrene::init()
{
	bool bRef = true;
	do{
		CC_BREAK_IF(! CCLayer::init());
		ul = UILayer::create();

		this->addChild(ul);
		ul->addWidget(CCUIHELPER->createWidgetFromJsonFile("ui/screne_main/screne_main_1.ExportJson"));

		tbStartGame = dynamic_cast<UIButton*>(ul->getWidgetByName("btn_startgame"));
		tbStartGame->addReleaseEvent(this, coco_releaseselector(StartScrene::tbStartGameCallback));

		tbSetting = dynamic_cast<UIButton*>(ul->getWidgetByName("btn_setting"));
		tbSetting->addReleaseEvent(this, coco_releaseselector(StartScrene::tbSettingCallback));

		tbRank = dynamic_cast<UIButton*>(ul->getWidgetByName("btn_rank"));
		tbRank->addReleaseEvent(this, coco_releaseselector(StartScrene::tbRankdCallback));

		ul->setTouchEnabled(true);
		bRef = true;
	}while(0);
	return bRef;
}

void StartScrene::tbSettingCallback(cocos2d::CCObject *pSender)
{
	CCDirector::sharedDirector()->replaceScene(SoundScrene::scene());
}

void StartScrene::tbStartGameCallback(cocos2d::CCObject *pSender)
{
	CCDirector::sharedDirector()->replaceScene(IntroduceScrene::scene());
}

void StartScrene::tbRankdCallback(cocos2d::CCObject *pSender)
{
	CCLog("1111111");
}

CCScene* StartScrene::scene()
{
	CCScene *scene = CCScene::create();
	CCLayer *layer = StartScrene::create();
	scene->addChild(layer);
	return scene;
}