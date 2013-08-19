#include "ResultScrene.h"
#include "StartScrene.h"
#include "FirstStage.h"
#include "Util.h"
#include "Database.h"

ResultScrene::ResultScrene(int score, int min, int sec, int monsterNum, int coinNum)
{
	this->iNowMin = 0;
	this->iNowSec = 0;
	this->iNowMonsterNum = 0;
	this->iNowCoinNum = 0;

	this->iScore = score;
	this->iMin = min;
	this->iSec = sec;
	this->iMonsterNum = monsterNum;
	this->iCoinNum = coinNum;
	//string sql = "insert into t_user values(2, 0, 0, 'b', 'b')";
	//Database::execute(sql);
}

bool ResultScrene::init()
{
	bool bRef = true;
	do{
		CC_BREAK_IF(! CCLayer::init());
		ul = UILayer::create();
		// ���� UI ���tag
		this->addChild(ul, 0, 100);
		ul->addWidget(CCUIHELPER->createWidgetFromJsonFile("ui/screne_result/screne_result_1.ExportJson"));

		// �������˵���ť
		btnBack = dynamic_cast<UIButton*>(ul->getWidgetByName("btn_back"));
		btnBack->addReleaseEvent(this, coco_releaseselector(ResultScrene::btnBackCallback));
		btnBack->setPressedTexture("ui/screne_result/big_back.png");

		// ���¿�ʼ��ť
		btnRestart = dynamic_cast<UIButton*>(ul->getWidgetByName("btn_restart"));
		btnRestart->addReleaseEvent(this, coco_releaseselector(ResultScrene::btnRestartCallback));
		btnRestart->setPressedTexture("ui/screne_result/big_restart.png");

		laScore = dynamic_cast<UILabelAtlas*>(ul->getWidgetByName("la_score"));
		laMin = dynamic_cast<UILabelAtlas*>(ul->getWidgetByName("la_min"));
		laSec = dynamic_cast<UILabelAtlas*>(ul->getWidgetByName("la_sec"));
		laMonsterNum = dynamic_cast<UILabelAtlas*>(ul->getWidgetByName("la_monster"));
		laCoinNum = dynamic_cast<UILabelAtlas*>(ul->getWidgetByName("la_coin"));
		laScore->setVisible(false);

		schedule(schedule_selector(ResultScrene::update));

		ul->setTouchEnabled(true);
		bRef = true;
	}while(0);
	return bRef;
}

// ��ʾ������...
void ResultScrene::update(float dt)
{
	if (iNowMin < iMin)
		iNowMin++;
	else if (iNowSec < iSec)
		iNowSec++;
	else if (iNowMonsterNum < iMonsterNum)
		iNowMonsterNum++;
	else if (iNowCoinNum < iCoinNum)
	{
		iNowCoinNum += 10;
		if (iNowCoinNum > iCoinNum)
			iNowCoinNum = iCoinNum;
	}
	else
	{
		CCLog("show result finish");
		laScore->setVisible(true);
		laScore->setStringValue(N2C(iScore));
		unschedule(schedule_selector(ResultScrene::update));
	}
	laMin->setStringValue(N2C(iNowMin));
	laSec->setStringValue(N2C(iNowSec));
	laMonsterNum->setStringValue(N2C(iNowMonsterNum));
	laCoinNum->setStringValue(N2C(iNowCoinNum));
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