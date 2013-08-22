#include "IntroduceScrene.h"
#include "FirstStage.h"

CCScene* IntroduceScrene::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		IntroduceScrene *layer = IntroduceScrene::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}

void IntroduceScrene::initData()
{
	vFrames.push_back("ui/screne_introduce/1.png");
	vFrames.push_back("ui/screne_introduce/2.png");
	vFrames.push_back("ui/screne_introduce/3.png");
	vFrames.push_back("ui/screne_introduce/4.png");
	vFrames.push_back("ui/screne_introduce/5.png");
	vFrames.push_back("ui/screne_introduce/6.png");
	iFramePos = 0;
	fTotalTime = 0.f;
}

bool IntroduceScrene::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(! CCLayer::init());
		initData();
		ul = UILayer::create();

		this->addChild(ul);
		ul->addWidget(CCUIHELPER->createWidgetFromJsonFile("ui/screne_introduce/screne_introduce_1.json"));

		ivAnimation = dynamic_cast<UIImageView*>(ul->getWidgetByName("iv_intro"));

		btnSkip = dynamic_cast<UIButton*>(ul->getWidgetByName("btn_skip"));
		btnSkip->addPushDownEvent(this, coco_releaseselector(IntroduceScrene::tbContinueCallback));

		schedule(schedule_selector(IntroduceScrene::update), CHANEGE_ANIMATION_INTERVAL);

		ul->setTouchEnabled(true);
		bRet = true;
	} while (0);

	return bRet;
}

void IntroduceScrene::tbContinueCallback(cocos2d::CCObject *pSender)
{
	CCDirector::sharedDirector()->replaceScene(FirstStage::scene());
}

void IntroduceScrene::update(float time)  
{
	fTotalTime += time;
	if (fTotalTime < CHANGE_DIALOG_INTERVAL && iFramePos % ANIMATION_FRAMES != 0)
	{
		return ;
	}
	iFramePos++;
	if (iFramePos == (int)(vFrames.size() - 1))
	{
		unschedule(schedule_selector(IntroduceScrene::update));
	}
	ivAnimation->setTexture(vFrames[iFramePos].c_str());
	if (fTotalTime >= CHANGE_DIALOG_INTERVAL)
	{
		fTotalTime = 0.f;
	}
}  