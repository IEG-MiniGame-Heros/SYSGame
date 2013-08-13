#include "StartScrene.h"
#include "SoundScrene.h"


bool StartScrene::init()
{
	bool bRef = true;
	do{
		CC_BREAK_IF(! CCLayer::init());
		ul = UILayer::create();

		this->addChild(ul);
		ul->addWidget(CCUIHELPER->createWidgetFromJsonFile("ui/screne_main/screne_main_1.ExportJson"));

		tbStartGame = dynamic_cast<UIButton*>(ul->getWidgetByName("btn_startgame"));
		tbStartGame->addPushDownEvent(this, coco_releaseselector(StartScrene::tbStartGameCallback));

		tbSetting = dynamic_cast<UIButton*>(ul->getWidgetByName("btn_setting"));
		tbSetting->addPushDownEvent(this, coco_releaseselector(StartScrene::tbSettingCallback));

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

}

CCScene* StartScrene::scene()
{
	CCScene *scene = CCScene::create();
	CCLayer *layer = StartScrene::create();
	scene->addChild(layer);
	return scene;
}