#ifndef SYS_GUIDESCRENE
#define SYS_GUIDESCRENE

#include "cocos2d.h"
#include "cocos-ext.h"
#include "CocoGUILIB/System/CocosGUI.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define READY_FRAMES 1100
#define ALL_FRAMES 1460

class GuideScrene : public cocos2d::CCLayer
{
public :
	virtual bool init();
	static cocos2d::CCScene* scene();

	void btnSkipCallback(CCObject *pSender);
	void playReadyGo(float dt);

	CREATE_FUNC(GuideScrene);

private:
	UILayer *ul;
	UIButton *btnSkip;
	CCArmature* armLoad;
};
#endif