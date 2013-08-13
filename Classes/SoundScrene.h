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

	CREATE_FUNC(SoundScrene);

private:
	UILayer *ul;
};

#endif