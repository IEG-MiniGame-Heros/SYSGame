#ifndef SYS_INTRODUCESCRENE
#define SYS_INTRODUCESCRENE


#include "cocos2d.h"
#include "cocos-ext.h"
#include "CocoGUILIB/System/CocosGUI.h"

USING_NS_CC;
USING_NS_CC_EXT;

class IntroduceScrene : public cocos2d::CCLayerColor
{
public :
	virtual bool init();
	static cocos2d::CCScene* scene();
	// init scene
	cocos2d::CCNode* createGameScene();
	void tbContinueCallback(cocos2d::CCObject *pSender);
	void update(float time);
	CREATE_FUNC(IntroduceScrene);

private:
	cocos2d::CCNode *m_pCurNode;

	// UI¿Ø¼þ
	UILayer *ul;
	UIButton *btnContinue;

	float isOver;  
};

#endif