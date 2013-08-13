#include "LogoScrene.h"
#include "LoginScrene.h"

CCScene* LogoScrene::scene()
{
	CCScene *scene = CCScene::create();
	CCLayer *layer = LogoScrene::create();
	scene->addChild(layer);
	return scene;
}

bool LogoScrene::init()
{
	bool bRef = true;
	do{
		CC_BREAK_IF(! CCLayer::init());
		UILayer *ul = UILayer::create();
		this->addChild(ul);
		ul->addWidget(CCUIHELPER->createWidgetFromJsonFile("ui/screne_logo/screne_logo_1.ExportJson"));
		bRef = true;
	}while(0);
	return bRef;
}

// 切换到登录场景 
void LogoScrene::replaceScrene(float dt)
{
	this->unschedule(schedule_selector(LogoScrene::replaceScrene));  
	CCDirector::sharedDirector()->replaceScene(LoginScrene::scene());
}

// 两秒之后切换场景
void LogoScrene::onEnter()
{
	CCLayer::onEnter();
	this->schedule(schedule_selector(LogoScrene::replaceScrene), 2.0f);  
}
