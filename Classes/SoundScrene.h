#ifndef SYS_SOUNDSCRENE
#define SYS_SOUNDSCRENE

#include "cocos2d.h"
#include "cocos-ext.h"
#include "CocoGUILIB/System/CocosGUI.h"

USING_NS_CC;
USING_NS_CC_EXT;

class SoundScrene : public cocos2d::CCLayer
{
public :
	virtual bool init();
	static cocos2d::CCScene* scene();

	// ���ذ�ť��Ӧ�¼�
	void btnBackCallback(cocos2d::CCObject *pSender);

	// Sound��������Ӧ�¼�
	void sliderSoundCallback(cocos2d::CCObject *pSender);

	// Music��������Ӧ�¼�
	void sliderMusicCallback(cocos2d::CCObject *pSender);

	void updateSlider(UISlider *slider);

	CREATE_FUNC(SoundScrene);

private:
	UILayer *ul;
	UIButton *btnBack;
	UISlider *slMusic;
	UISlider *slSound;
};

#endif