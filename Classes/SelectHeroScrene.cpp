#include "SelectHeroScrene.h"
#include "FirstStage.h"

void SelectHeroScrene::initTestData()
{
	hero h1;
	h1.path = "ui/select_hero/red_button.png";
	h1.desc = "红毛企鹅";
	hero h2;
	h2.path = "ui/select_hero/green_button.png";
	h2.desc = "绿毛企鹅";
	hero h3;
	h3.path = "ui/select_hero/blue_button.png";
	h3.desc = "蓝毛企鹅";
	hero h4;
	h4.path = "ui/select_hero/orange_button.png";
	h4.desc = "橙毛企鹅";

	heroList.push_back(h1);
	heroList.push_back(h2);
	heroList.push_back(h3);
	heroList.push_back(h4);
}

void SelectHeroScrene::setDisplayByPos(int pos)
{
	CCLog("---------- setDisplayByPos BEGIN ----------");
	int size = heroList.size();
	if (size == 0)
		return ;
	uvMidHero->setTexture(heroList[pos - 1].path.c_str());
	taHeroDesc->setText(heroList[pos - 1].desc.c_str());
	if (size == 1)
	{
		btnSelectLeft->setVisible(false);
		uvLeftHero->setVisible(false);
		btnSelectRight->setVisible(false);
		uvRightHero->setVisible(false);
		return ;
	}
	if (pos == 1)
	{
		btnSelectLeft->setVisible(false);
		uvLeftHero->setVisible(false);

		uvRightHero->setTexture(heroList[pos].path.c_str());
		uvRightHero->setVisible(true);
	}
	else if (pos == size)
	{
		btnSelectRight->setVisible(false);
		uvRightHero->setVisible(false);

		uvLeftHero->setTexture(heroList[pos - 2].path.c_str());
		uvLeftHero->setVisible(true);
	}
	else
	{
		btnSelectLeft->setVisible(true);
		btnSelectRight->setVisible(true);
		uvLeftHero->setTexture(heroList[pos - 2].path.c_str());
		uvLeftHero->setVisible(true);
		uvRightHero->setTexture(heroList[pos].path.c_str());
		uvRightHero->setVisible(true);
	}
	CCLog("---------- setDisplayByPos END ----------");
}

bool SelectHeroScrene::init()
{
	bool bRef = true;
	initTestData();
	pos = 1;
	do{
		CC_BREAK_IF(! CCLayer::init());
		ul = UILayer::create();

		this->addChild(ul);
		ul->addWidget(CCUIHELPER->createWidgetFromJsonFile("ui/select_hero/selectui_1.ExportJson"));

		// 英雄图片
		uvLeftHero = dynamic_cast<UIImageView*>(ul->getWidgetByName("iv_hero_left"));
		uvMidHero = dynamic_cast<UIImageView*>(ul->getWidgetByName("iv_hero_mid"));
		uvRightHero = dynamic_cast<UIImageView*>(ul->getWidgetByName("iv_hero_right"));

		// 左右选择英雄按钮
		btnSelectLeft = dynamic_cast<UIButton*>(ul->getWidgetByName("btn_select_left"));
		btnSelectRight = dynamic_cast<UIButton*>(ul->getWidgetByName("btn_select_right"));

		btnSelectLeft->addPushDownEvent(this, coco_releaseselector(SelectHeroScrene::tbSelectLeftCallback));
		btnSelectRight->addPushDownEvent(this, coco_releaseselector(SelectHeroScrene::tbSelectRightCallback));

		// 英雄描述文本
		taHeroDesc = dynamic_cast<UITextArea*>(ul->getWidgetByName("ta_hero_desc"));

		// 开始游戏按钮
		btnStartGame = dynamic_cast<UIButton*>(ul->getWidgetByName("btn_start"));
		btnStartGame->addPushDownEvent(this, coco_releaseselector(SelectHeroScrene::tbStartGameCallback));

		setDisplayByPos(pos);

		ul->setTouchEnabled(true);
		bRef = true;
	}while(0);
	return bRef;
}

CCScene* SelectHeroScrene::scene()
{
	CCScene *scene = CCScene::create();
	CCLayer *layer = SelectHeroScrene::create();
	scene->addChild(layer);
	return scene;
}

void SelectHeroScrene::tbSelectLeftCallback(cocos2d::CCObject *pSender)
{
	CCLog("---------- LEFT ----------");
	if (pos > 1)
		pos--;
	setDisplayByPos(pos);
}

void SelectHeroScrene::tbSelectRightCallback(cocos2d::CCObject *pSender)
{
	CCLog("---------- RIGHT ----------");
	if (pos < (int)(heroList.size()))
		pos++;
	setDisplayByPos(pos);
}

void SelectHeroScrene::tbStartGameCallback(cocos2d::CCObject *pSender)
{
	CCDirector::sharedDirector()->replaceScene(FirstStage::scene());
}