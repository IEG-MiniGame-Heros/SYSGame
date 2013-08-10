#include "LoginScrene.h"
#include "IntroduceScrene.h"

bool LoginScrene::init()
{
	bool bRef = true;
	do{
		CC_BREAK_IF(! CCLayer::init());
		ul = UILayer::create();
		// 设置 UI 层的tag
		this->addChild(ul, 0, 100);
		ul->addWidget(CCUIHELPER->createWidgetFromJsonFile("ui/login/LoginUI_1.ExportJson"));

		// 用户名输入框
		tfName = dynamic_cast<UITextField*>(ul->getWidgetByName("TextField_username"));

		// 密码输入框
		tfPsw = dynamic_cast<UITextField*>(ul->getWidgetByName("TextField_password"));

		// 登录按钮
		tbLogin = dynamic_cast<UITextButton*>(ul->getWidgetByName("Btn_login"));
		tbLogin->addReleaseEvent(this, coco_releaseselector(LoginScrene::tbLoginCallback));
		tbLogin->setTextColor(0, 0, 0);

		ul->setTouchEnabled(true);
		bRef = true;
	}while(0);
	return bRef;
}

CCScene* LoginScrene::scene()
{
	CCScene *scene = CCScene::create();
	CCLayer *layer = LoginScrene::create();
	scene->addChild(layer);
	return scene;
}

void LoginScrene::tbLoginCallback(cocos2d::CCObject *pSender)
{
	CCDirector::sharedDirector()->replaceScene(IntroduceScrene::scene());
}