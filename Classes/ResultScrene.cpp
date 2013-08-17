#include "ResultScrene.h"
#include "StartScrene.h"
#include "FirstStage.h"
#include "Util.h"

ResultScrene::ResultScrene(int score, int min, int sec, int monsterNum, int coinNum)
{
	this->iScore = score;
	this->iMin = min;
	this->iSec = sec;
	this->iMonsterNum = monsterNum;
	this->iCoinNum = coinNum;
}

bool ResultScrene::init()
{
	bool bRef = true;
	do{
		CC_BREAK_IF(! CCLayer::init());
		ul = UILayer::create();
		// 设置 UI 层的tag
		this->addChild(ul, 0, 100);
		ul->addWidget(CCUIHELPER->createWidgetFromJsonFile("ui/screne_result/screne_result_1.ExportJson"));

		// 返回主菜单按钮
		btnBack = dynamic_cast<UIButton*>(ul->getWidgetByName("btn_back"));
		btnBack->addPushDownEvent(this, coco_releaseselector(ResultScrene::btnBackCallback));

		// 重新开始按钮
		btnRestart = dynamic_cast<UIButton*>(ul->getWidgetByName("btn_restart"));
		btnRestart->addPushDownEvent(this, coco_releaseselector(ResultScrene::btnRestartCallback));

		laScore = dynamic_cast<UILabelAtlas*>(ul->getWidgetByName("la_score"));
		laMin = dynamic_cast<UILabelAtlas*>(ul->getWidgetByName("la_min"));
		laSec = dynamic_cast<UILabelAtlas*>(ul->getWidgetByName("la_sec"));
		laMonsterNum = dynamic_cast<UILabelAtlas*>(ul->getWidgetByName("la_monster"));
		laCoinNum = dynamic_cast<UILabelAtlas*>(ul->getWidgetByName("la_coin"));

		schedule(schedule_selector(ResultScrene::update));

		ul->setTouchEnabled(true);
		bRef = true;
	}while(0);
	return bRef;
}

void ResultScrene::update(float dt)
{
	CCLog("%s", N2C(iScore));
	laScore->setStringValue(N2C(iScore));
	laMin->setStringValue(N2C(iMin));
	laSec->setStringValue(N2C(iSec));
	laMonsterNum->setStringValue(N2C(iMonsterNum));
	laCoinNum->setStringValue(N2C(iCoinNum));
}

ResultScrene* ResultScrene::create(int score, int min, int sec, int monsterNum, int coinNum)
{
	ResultScrene *p = new ResultScrene(score, min, sec, monsterNum, coinNum);
	if (p && p->init())
	{
		p->autorelease();
		return p;
	} else
	{
		delete p;
		p = NULL;
		return p;
	}
}

CCScene* ResultScrene::scene()
{
	CCScene *scene = CCScene::create();
	CCLayer *layer = ResultScrene::create();
	scene->addChild(layer);
	return scene;
}

CCScene* ResultScrene::scene(int score, int min, int sec, int monsterNum, int coinNum)
{
	CCScene *scene = CCScene::create();
	CCLayer *layer = ResultScrene::create(score, min, sec, monsterNum, coinNum);

	scene->addChild(layer);
	return scene;
}


void ResultScrene::btnBackCallback(CCObject *pSender)
{
	CCDirector::sharedDirector()->replaceScene(StartScrene::scene());
}

void ResultScrene::btnRestartCallback(CCObject *pSender)
{
	CCDirector::sharedDirector()->replaceScene(FirstStage::scene());
}