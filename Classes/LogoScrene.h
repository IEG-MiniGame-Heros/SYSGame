#ifndef SYS_LOGOSCRENE
#define SYS_LOGOSCRENE

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class LogoScrene : public cocos2d::CCLayer
{
public :
	virtual bool init();
	static cocos2d::CCScene* scene();

	virtual void onEnter();

	void replaceScrene(float dt);
	CREATE_FUNC(LogoScrene);
};

#endif
