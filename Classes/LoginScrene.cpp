#include "LoginScrene.h"
#include "StartScrene.h"

bool LoginScrene::init()
{
	bool bRef = true;
	do{
		CC_BREAK_IF(! CCLayer::init());
		ul = UILayer::create();
		// 设置 UI 层的tag
		this->addChild(ul, 0, 100);
		ul->addWidget(CCUIHELPER->createWidgetFromJsonFile("ui/screne_login/screne_login_1.ExportJson"));

		// 用户名输入框
		tfName = dynamic_cast<UITextField*>(ul->getWidgetByName("tf_name"));
		tfName->setColor(ccc3(0, 0, 0));
		tfName->setText("10000");

		// 密码输入框
		tfPsw = dynamic_cast<UITextField*>(ul->getWidgetByName("tf_psw"));
		tfPsw->setColor(ccc3(0, 0, 0));
		tfPsw->setText("******");

		// 记住密码复选框
		cbPsw = dynamic_cast<UICheckBox*>(ul->getWidgetByName("cb_psw"));
		cbPsw->setSelectedState(true);

		// 自动登录复选狂
		cbAuto = dynamic_cast<UICheckBox*>(ul->getWidgetByName("cb_auto"));
		cbAuto->setSelectedState(false);

		// 登录按钮
		tbLogin = dynamic_cast<UIButton*>(ul->getWidgetByName("btn_login"));
		tbLogin->addPushDownEvent(this, coco_releaseselector(LoginScrene::tbLoginCallback));

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
	CCDirector::sharedDirector()->replaceScene(StartScrene::scene());
}