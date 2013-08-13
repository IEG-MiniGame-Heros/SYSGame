#ifndef SYS_LOGINSCRENE
#define SYS_LOGINSCRENE

#include "cocos2d.h"
#include "cocos-ext.h"
#include "CocoGUILIB/System/CocosGUI.h"

USING_NS_CC;
USING_NS_CC_EXT;

class LoginScrene : public cocos2d::CCLayer
{
public :
	virtual bool init();
	static cocos2d::CCScene* scene();

	// 登录按钮响应事件
	void tbLoginCallback(cocos2d::CCObject *pSender);

	CREATE_FUNC(LoginScrene);

private:
	UILayer *ul;
	UITextField *tfName;
	UITextField *tfPsw;
	UIButton *tbLogin;
	UICheckBox *cbPsw;
	UICheckBox *cbAuto;
};

#endif