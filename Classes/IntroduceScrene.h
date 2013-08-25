#ifndef SYS_INTRODUCESCRENE
#define SYS_INTRODUCESCRENE


#include "cocos2d.h"
#include "cocos-ext.h"
#include <vector>
#include <string>
#include "CocoGUILIB/System/CocosGUI.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;


#define CHANGE_DIALOG_INTERVAL 4.0f
#define CHANEGE_ANIMATION_INTERVAL 1.0f
#define ANIMATION_FRAMES 2


class IntroduceScrene : public cocos2d::CCLayer
{
public :
	virtual bool init();
	void initData();
	static cocos2d::CCScene* scene();

	void tbContinueCallback(cocos2d::CCObject *pSender);
	void changeScrene(float dt);
	void update(float time);
	CREATE_FUNC(IntroduceScrene);

private:
	UILayer *ul;
	UIButton *btnSkip;
	UIImageView *ivAnimation;

	vector<string> vFrames;
	int iFramePos;
	float fTotalTime;
};

#endif