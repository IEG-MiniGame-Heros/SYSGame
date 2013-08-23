#include "ResultScrene.h"
#include "StartScrene.h"
#include "FirstStage.h"
#include "Util.h"
#include "Database.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

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
	isNewRecord = false;
}

bool ResultScrene::init()
{
	bool bRef = true;
	do{
		CC_BREAK_IF(! CCLayer::init());
		CCNode *pNode = CCJsonReader::sharedJsonReader()->createNodeWithJsonFile("ui/screne_result_final/screne_result_final.json");
		this->addChild(pNode);

		CCComRender *pUIRender = (CCComRender*)(pNode->getChildByTag(1)->getChildByTag(3)->getComponent("GUIComponent"));
		ul = (UILayer*)(pUIRender->getRender()); 

		CCComRender *pArmRender = (CCComRender*)(pNode->getChildByTag(1)->getChildByTag(2)->getComponent("CCArmature"));
		CCArmature* armLoad = (CCArmature*)(pArmRender->getRender());
		armLoad->getAnimation()->playByIndex(0);

		// ���� UI ���tag
		//this->addChild(ul, 0, 100);
		//ul->addWidget(CCUIHELPER->createWidgetFromJsonFile("ui/screne_result/screne_result_1.ExportJson"));

		// �������˵���ť
		btnBack = dynamic_cast<UIButton*>(ul->getWidgetByName("btn_back_main"));
		btnBack->addReleaseEvent(this, coco_releaseselector(ResultScrene::btnBackCallback));

		// ���¿�ʼ��ť
		btnRestart = dynamic_cast<UIButton*>(ul->getWidgetByName("btn_restart"));
		btnRestart->addReleaseEvent(this, coco_releaseselector(ResultScrene::btnRestartCallback));

		// �¼�¼ͼƬ
		iv_newRecord = dynamic_cast<UIImageView*>(ul->getWidgetByName("iv_new_record"));

		laScore = dynamic_cast<UILabelAtlas*>(ul->getWidgetByName("la_score"));
		laMin = dynamic_cast<UILabelAtlas*>(ul->getWidgetByName("la_min"));
		laSec = dynamic_cast<UILabelAtlas*>(ul->getWidgetByName("la_sec"));
		laMonsterNum = dynamic_cast<UILabelAtlas*>(ul->getWidgetByName("la_monster"));
		laCoinNum = dynamic_cast<UILabelAtlas*>(ul->getWidgetByName("la_coin"));
		laScore->setVisible(false);

		// ���浽���ݿ�
		save2DataBase();

		schedule(schedule_selector(ResultScrene::update));

		ul->setTouchEnabled(true);
		bRef = true;
	}while(0);
	return bRef;
}

void ResultScrene::save2DataBase()
{
	TUser stUser;
	// ��ȡ���ݿ��е�ǰ�û�������
	int ret = SQLITE_ERROR;
	do 
	{
		ret = Database::getUserInfo(stUser);
		if (ret != SQLITE_OK)
			break;
		int nowTime = iMin * 60 + iSec;
		int nowScore = iScore;
		int nowKill = iMonsterNum;
		int nowCoin = iCoinNum;

		CCLog("%d, %d", nowTime, stUser.iTime);
		if (nowTime > stUser.iTime)
		{
			stUser.iTime = nowTime;
			isNewRecord = true;
		}
		if (nowScore > stUser.iScore)
		{
			stUser.iScore = nowScore;
			isNewRecord = true;
		}
		if (nowKill > stUser.iKillNum)
		{
			stUser.iKillNum = nowKill;
			isNewRecord = true;
		}
		if (nowCoin > stUser.iMoney)
		{
			stUser.iMoney = nowCoin;
			isNewRecord = true;
		}

		string updateSQL = "update t_user set money = " + N2S(stUser.iMoney) + " , kill_num = " + 
			N2S(stUser.iKillNum) + " , score = " + N2S(stUser.iScore) + " , time = " + N2S(stUser.iTime) + 
			" where id = 1";
		CCLog(updateSQL.c_str());
		ret = Database::execute(updateSQL);
		if (ret != SQLITE_OK)
			break;
	} while (0);
	CCLog("save result : %d", ret);
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
		if (isNewRecord)
			iv_newRecord->setVisible(true);
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
	SimpleAudioEngine::sharedEngine()->playEffect("music/btn.mp3");
	CCDirector::sharedDirector()->replaceScene(StartScrene::scene());
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("music/background.mp3", true);
}

void ResultScrene::btnRestartCallback(CCObject *pSender)
{
	SimpleAudioEngine::sharedEngine()->playEffect("music/btn.mp3");
		
	CCDirector::sharedDirector()->replaceScene(FirstStage::scene());
}