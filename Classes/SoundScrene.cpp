#include "SoundScrene.h"
#include "SimpleAudioEngine.h"
#include "GameInfo.h"
#include "StartScrene.h"


bool SoundScrene::init()
{
	bool bRef = true;
	do{
		CC_BREAK_IF(! CCLayer::init());
		ul = UILayer::create();

		this->addChild(ul);
		ul->addWidget(CCUIHELPER->createWidgetFromJsonFile("ui/screne_sound/screne_sound_1.json"));

		// 返回按钮
		btnBack = dynamic_cast<UIButton*>(ul->getWidgetByName("Button"));
		btnBack->addPushDownEvent(this, coco_releaseselector(SoundScrene::btnBackCallback));

		// music滑动条
		slMusic = dynamic_cast<UISlider*>(ul->getWidgetByName("Slider_music"));
		slMusic->setSlidBallPercent(GI.musicVolume);
		slMusic->setProgressBarScale(GI.musicVolume);
		slMusic->addPercentChangedEvent(this, coco_releaseselector(SoundScrene::sliderMusicCallback));
		updateSlider(slMusic);

		// sound滑动条
		slSound = dynamic_cast<UISlider*>(ul->getWidgetByName("Slider_sound"));
		slSound->setSlidBallPercent(GI.soundVolume);
		slSound->setProgressBarScale(GI.soundVolume);
		slSound->addPercentChangedEvent(this, coco_releaseselector(SoundScrene::sliderSoundCallback));
		updateSlider(slSound);

		ul->setTouchEnabled(true);
		bRef = true;
	}while(0);
	return bRef;
}

void SoundScrene::btnBackCallback(cocos2d::CCObject *pSender)
{
	CCDirector::sharedDirector()->replaceScene(StartScrene::scene());
}

CCScene* SoundScrene::scene()
{
	CCScene *scene = CCScene::create();
	CCLayer *layer = SoundScrene::create();
	scene->addChild(layer);
	return scene;
}

void SoundScrene::updateSlider(UISlider *slider)
{
	const char *sliderName = slider->getName();
	int percent = slider->getPercent();
	if (strcmp(sliderName, "Slider_music") == 0)
	{
		if (percent == 0)
			slider->setSlidBallNormalTexture("ui/screne_sound/pink_close.png");
		else
			slider->setSlidBallNormalTexture("ui/screne_sound/pink_open.png");
	}
	else if (strcmp(sliderName, "Slider_sound") == 0)
	{
		if (percent == 0)
			slider->setSlidBallNormalTexture("ui/screne_sound/blue_close.png");
		else
			slider->setSlidBallNormalTexture("ui/screne_sound/blue_open.png");
	}
}

void SoundScrene::sliderMusicCallback(cocos2d::CCObject *pSender)
{
	// TODO :: junqiang
	GI.musicVolume = slMusic->getPercent();
	float volume = (float)slMusic->getPercent() / 100;
	updateSlider(slMusic);
}

void SoundScrene::sliderSoundCallback(cocos2d::CCObject *pSender)
{
	// TODO :: junqiang
	GI.soundVolume = slSound->getPercent();
	float volume = (float)slSound->getPercent() / 100;
	updateSlider(slSound);
}

