#ifndef SYS_RESULTSCRENE
#define SYS_RESULTSCRENE

#include "cocos2d.h"
#include "cocos-ext.h"
#include "CocoGUILIB/System/CocosGUI.h"

USING_NS_CC;
USING_NS_CC_EXT;

class ResultScrene : public cocos2d::CCLayer
{
public :
	virtual bool init();
	static cocos2d::CCScene* scene();

	void btnBackCallback(CCObject *pSender);
	void btnRestartCallback(CCObject *pSender);

	CREATE_FUNC(ResultScrene);

private:
	UILayer *ul;
	UIButton *btnBack;
	UIButton *btnRestart;
};

#endif