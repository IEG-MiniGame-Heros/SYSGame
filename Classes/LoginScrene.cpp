#include "LoginScrene.h"
#include "StartScrene.h"

bool LoginScrene::init()
{
	bool bRef = true;
	do{
		CC_BREAK_IF(! CCLayer::init());
		ul = UILayer::create();
		// ���� UI ���tag
		this->addChild(ul, 0, 100);
		ul->addWidget(CCUIHELPER->createWidgetFromJsonFile("ui/screne_login/screne_login_1.ExportJson"));

		// �û��������
		tfName = dynamic_cast<UITextField*>(ul->getWidgetByName("tf_name"));
		tfName->setColor(ccc3(0, 0, 0));
		tfName->setText("10000");

		// ���������
		tfPsw = dynamic_cast<UITextField*>(ul->getWidgetByName("tf_psw"));
		tfPsw->setColor(ccc3(0, 0, 0));
		tfPsw->setText("******");

		// ��ס���븴ѡ��
		cbPsw = dynamic_cast<UICheckBox*>(ul->getWidgetByName("cb_psw"));
		cbPsw->setSelectedState(true);

		// �Զ���¼��ѡ��
		cbAuto = dynamic_cast<UICheckBox*>(ul->getWidgetByName("cb_auto"));
		cbAuto->setSelectedState(false);

		// ��¼��ť
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
	//CCDirector::sharedDirector()->replaceScene(StartScrene::scene());
	ExitDlg* dlg = ExitDlg::create();  
	addChild(dlg); 
}