#include "GuideScrene.h"
#include "StartScrene.h"
#include "FirstStage.h"
#include "Util.h"
#include "Database.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

CCScene* GuideScrene::scene()
{
	CCScene *scene = CCScene::create();
	CCLayer *layer = GuideScrene::create();
	scene->addChild(layer);
	return scene;
}


bool GuideScrene::init()
{
	bool bRef = true;
	do{
		CC_BREAK_IF(! CCLayer::init());
		CCNode *pNode = CCJsonReader::sharedJsonReader()->createNodeWithJsonFile("ui/screne_guide/screne_guide_final.json");
		this->addChild(pNode);
		

		CCComRender *pUIRender = (CCComRender*)(pNode->getChildByTag(3)->getComponent("GUIComponent"));
		ul = (UILayer*)(pUIRender->getRender()); 

		CCComRender *pArmRender = (CCComRender*)(pNode->getChildByTag(2)->getComponent("CCArmature"));
		armLoad = (CCArmature*)(pArmRender->getRender());
		armLoad->getAnimation()->playByIndex(0);

		// 跳过引导按钮
		btnSkip = dynamic_cast<UIButton*>(ul->getWidgetByName("btn_skip"));
		btnSkip->addReleaseEvent(this, coco_releaseselector(GuideScrene::btnSkipCallback));

		schedule(schedule_selector(GuideScrene::playReadyGo));

		ul->setTouchEnabled(true);
		bRef = true;
	}while(0);
	return bRef;
}

void GuideScrene::playReadyGo(float dt)
{
	int nowFrames = armLoad->getAnimation()->getCurrentFrameIndex();
	/*if (nowFrames == READY_FRAMES)
	{ 
		SimpleAudioEngine::sharedEngine()->playEffect("/music/ready_go.mp3");
	}*/
	if (nowFrames >= ALL_FRAMES)
	{
		unschedule(schedule_selector(GuideScrene::playReadyGo));
		CCDirector::sharedDirector()->replaceScene(FirstStage::scene());
	}
}

void GuideScrene::btnSkipCallback(CCObject *pSender)
{
	CCDirector::sharedDirector()->replaceScene(FirstStage::scene());
}