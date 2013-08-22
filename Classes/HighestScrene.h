#ifndef SYS_HIGHESTSCRENE
#define SYS_HIGHESTSCRENE

#include "cocos2d.h"
#include "cocos-ext.h"
#include "CocoGUILIB/System/CocosGUI.h"

USING_NS_CC;
USING_NS_CC_EXT;

class HighestScrene : public cocos2d::CCLayer
{
public :
	virtual bool init();
	static cocos2d::CCScene* scene();

	void btnBackMenuCallback(cocos2d::CCObject *pSender);
	void setData();

	CREATE_FUNC(HighestScrene);

private:
	UILayer *ul;
	UIButton *btnBack;

	// 分数
	UILabelAtlas *laScore;
	// 分
	UILabelAtlas *laMin;
	// 秒
	UILabelAtlas *laSec;
	// 杀怪数
	UILabelAtlas *laMonsterNum;
	// 金币数
	UILabelAtlas *laCoinNum;
};

#endif