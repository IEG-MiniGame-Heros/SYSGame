#include "SoundScrene.h"


bool SoundScrene::init()
{
	bool bRef = true;
	do{
		CC_BREAK_IF(! CCLayer::init());
		ul = UILayer::create();

		this->addChild(ul);
		ul->addWidget(CCUIHELPER->createWidgetFromJsonFile("ui/screne_sound/screne_sound_1.json"));

		ul->setTouchEnabled(true);
		bRef = true;
	}while(0);
	return bRef;
}

CCScene* SoundScrene::scene()
{
	CCScene *scene = CCScene::create();
	CCLayer *layer = SoundScrene::create();
	scene->addChild(layer);
	return scene;
}