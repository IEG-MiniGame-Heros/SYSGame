#include "ResultScrene.h"
#include "StartScrene.h"
#include "FirstStage.h"


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
		btnBack->addPushDownEvent(this, coco_releaseselector(ResultScrene::btnBackCallback));

		// ���¿�ʼ��ť
		btnRestart = dynamic_cast<UIButton*>(ul->getWidgetByName("btn_restart"));
		btnRestart->addPushDownEvent(this, coco_releaseselector(ResultScrene::btnRestartCallback));

		ul->setTouchEnabled(true);
		bRef = true;
	}while(0);
	return bRef;
}

CCScene* ResultScrene::scene()
{
	CCScene *scene = CCScene::create();
	CCLayer *layer = ResultScrene::create();
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