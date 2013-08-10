#include "LoginScrene.h"
#include "IntroduceScrene.h"

bool LoginScrene::init()
{
	bool bRef = true;
	do{
		CC_BREAK_IF(! CCLayer::init());
		ul = UILayer::create();
		// ���� UI ���tag
		this->addChild(ul, 0, 100);
		ul->addWidget(CCUIHELPER->createWidgetFromJsonFile("ui/login/LoginUI_1.ExportJson"));

		// �û��������
		tfName = dynamic_cast<UITextField*>(ul->getWidgetByName("TextField_username"));

		// ���������
		tfPsw = dynamic_cast<UITextField*>(ul->getWidgetByName("TextField_password"));

		// ��¼��ť
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