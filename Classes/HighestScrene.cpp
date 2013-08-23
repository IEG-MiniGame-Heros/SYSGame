#include "HighestScrene.h"
#include "Database.h"
#include "StartScrene.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

CCScene* HighestScrene::scene()
{
	CCScene *scene = CCScene::create();
	CCLayer *layer = HighestScrene::create();
	scene->addChild(layer);
	return scene;
}

bool HighestScrene::init()
{
	bool bRef = true;
	do{
		CC_BREAK_IF(! CCLayer::init());
		ul = UILayer::create();
		// 设置 UI 层的tag
		this->addChild(ul, 0, 100);
		ul->addWidget(CCUIHELPER->createWidgetFromJsonFile("ui/screne_highest/screne_highest_1.ExportJson"));

		laScore = dynamic_cast<UILabelAtlas*>(ul->getWidgetByName("la_score"));
		laMin = dynamic_cast<UILabelAtlas*>(ul->getWidgetByName("la_min"));
		laSec = dynamic_cast<UILabelAtlas*>(ul->getWidgetByName("la_sec"));
		laMonsterNum = dynamic_cast<UILabelAtlas*>(ul->getWidgetByName("la_monster"));
		laCoinNum = dynamic_cast<UILabelAtlas*>(ul->getWidgetByName("la_money"));

		// 返回按钮
		btnBack = dynamic_cast<UIButton*>(ul->getWidgetByName("btn_back"));
		btnBack->addReleaseEvent(this, coco_releaseselector(HighestScrene::btnBackMenuCallback));

		setData();

		ul->setTouchEnabled(true);
		bRef = true;
	}while(0);
	return bRef;
}

void HighestScrene::setData()
{
	TUser stUser;
	int ret = Database::getUserInfo(stUser);
	if (ret != SQLITE_OK)
		return ;
	int iMin = (int)(stUser.iTime) / 60;
	int iSec = (int)(stUser.iTime) % 60;
	laScore->setStringValue(N2C(stUser.iScore));
	laMin->setStringValue(N2C(iMin));
	laSec->setStringValue(N2C(iSec));
	laMonsterNum->setStringValue(N2C(stUser.iKillNum));
	laCoinNum->setStringValue(N2C(stUser.iMoney));
}

void HighestScrene::btnBackMenuCallback(cocos2d::CCObject *pSender)
{
	SimpleAudioEngine::sharedEngine()->playEffect("music/btn.mp3");
	CCDirector::sharedDirector()->replaceScene(StartScrene::scene());
}