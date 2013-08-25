#include "SelectScrene.h"
#include "StartScrene.h"
#include "GuideScrene.h"
#include "SoundScrene.h"
#include "GameInfo.h"

#include "SimpleAudioEngine.h"

using namespace CocosDenshion;


CCScene* SelectScrene::scene()
{
	CCScene *scene = CCScene::create();
	CCLayer *layer = SelectScrene::create();
	scene->addChild(layer);
	return scene;
}

bool SelectScrene::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(! CCLayer::init());
		ul = UILayer::create();
		iPos = 0;

		this->addChild(ul);
		ul->addWidget(CCUIHELPER->createWidgetFromJsonFile("ui/screne_select/screne_select_1.ExportJson"));

		iv_name = dynamic_cast<UIImageView*>(ul->getWidgetByName("iv_heroname"));
		// TODO::
		//iv_heroPic
		iv_heroPic = dynamic_cast<UIImageView*>(ul->getWidgetByName("iv_hero"));
		iv_HP = dynamic_cast<UIImageView*>(ul->getWidgetByName("iv_hp"));
		iv_moveSpeed = dynamic_cast<UIImageView*>(ul->getWidgetByName("iv_movespeed"));
		iv_skillSpeed = dynamic_cast<UIImageView*>(ul->getWidgetByName("iv_skillspeed"));
		iv_attack = dynamic_cast<UIImageView*>(ul->getWidgetByName("iv_attack"));
		iv_range = dynamic_cast<UIImageView*>(ul->getWidgetByName("iv_range"));
		iv_cd = dynamic_cast<UIImageView*>(ul->getWidgetByName("iv_cd"));
		iv_desc = dynamic_cast<UIImageView*>(ul->getWidgetByName("iv_desc"));

		btnBack = dynamic_cast<UIButton*>(ul->getWidgetByName("btn_back"));
		btnBack->addReleaseEvent(this, coco_releaseselector(SelectScrene::btnBackCallback));

		btnOK = dynamic_cast<UIButton*>(ul->getWidgetByName("btn_ok"));
		btnOK->addReleaseEvent(this, coco_releaseselector(SelectScrene::btnOKCallback));

		btnSetting = dynamic_cast<UIButton*>(ul->getWidgetByName("btn_setting"));
		btnSetting->addReleaseEvent(this, coco_releaseselector(SelectScrene::btnSettingCallback));

		btnLeft = dynamic_cast<UIButton*>(ul->getWidgetByName("btn_left"));
		btnLeft->addReleaseEvent(this, coco_releaseselector(SelectScrene::btnLeftCallback));

		btnRight = dynamic_cast<UIButton*>(ul->getWidgetByName("btn_right"));
		btnRight->addReleaseEvent(this, coco_releaseselector(SelectScrene::btnRightCallback));

		updateHeroInfo(iPos);

		ul->setTouchEnabled(true);
		bRet = true;
	} while (0);

	return bRet;
}

void SelectScrene::updateHeroInfo(int pos)
{
	const char *sHeroName;
	switch (pos)
	{
	case 0:
		sHeroName = "red";
		break;
	case 1:
		sHeroName = "purple";
		break;
	case 2:
		sHeroName = "blue";
		break;
	case 3:
		sHeroName = "yellow";
		break;
	default:
		return ;
	}

	char sNamePath[50];
	sprintf(sNamePath, "ui/screne_select/%s/name.png", sHeroName);
	// TODO :: hero pic

	char sHeroPath[50];
	sprintf(sHeroPath, "ui/screne_select/%s/hero.png", sHeroName);

	char sAttackPath[50];
	sprintf(sAttackPath, "ui/screne_select/%s/at.png", sHeroName);

	char sCDPath[50];
	sprintf(sCDPath, "ui/screne_select/%s/cd.png", sHeroName);

	char sDescPath[50];
	sprintf(sDescPath, "ui/screne_select/%s/desc.png", sHeroName);

	char sHPPath[50];
	sprintf(sHPPath, "ui/screne_select/%s/hp.png", sHeroName);

	char sSkillSpeedPath[50];
	sprintf(sSkillSpeedPath, "ui/screne_select/%s/ss.png", sHeroName);

	char sMoveSpeedPath[50];
	sprintf(sMoveSpeedPath, "ui/screne_select/%s/mv.png", sHeroName);

	char sRangePath[50];
	sprintf(sRangePath, "ui/screne_select/%s/ra.png", sHeroName);
	
	iv_name->setTexture(sNamePath);
	iv_heroPic->setTexture(sHeroPath);
	iv_moveSpeed->setTexture(sMoveSpeedPath);
	iv_skillSpeed->setTexture(sSkillSpeedPath);
	iv_attack->setTexture(sAttackPath);
	iv_range->setTexture(sRangePath);
	iv_cd->setTexture(sCDPath);
	iv_desc->setTexture(sDescPath);
	iv_HP->setTexture(sHPPath);

	if (pos == 0)
		btnLeft->setVisible(false);
	else if (pos == 3)
		btnRight->setVisible(false);
	else
	{
		btnLeft->setVisible(true);
		btnRight->setVisible(true);
	}
}

void SelectScrene::btnBackCallback(CCObject *pSender)
{
	SimpleAudioEngine::sharedEngine()->playEffect("music/btn.mp3");
	GI.CurrHeroId = iPos;
	CCDirector::sharedDirector()->replaceScene(StartScrene::scene());
}

void SelectScrene::btnOKCallback(CCObject *pSender)
{
	SimpleAudioEngine::sharedEngine()->playEffect("music/btn.mp3");
	GI.CurrHeroId = iPos;
	CCDirector::sharedDirector()->replaceScene(GuideScrene::scene());
}

void SelectScrene::btnSettingCallback(CCObject *pSender)
{
	SimpleAudioEngine::sharedEngine()->playEffect("music/btn.mp3");
	CCDirector::sharedDirector()->pushScene(SoundScrene::scene());
}

void SelectScrene::btnLeftCallback(CCObject *pSender)
{
	SimpleAudioEngine::sharedEngine()->playEffect("music/btn.mp3");
	iPos--;
	updateHeroInfo(iPos);
}

void SelectScrene::btnRightCallback(CCObject *pSender)
{
	SimpleAudioEngine::sharedEngine()->playEffect("music/btn.mp3");
	iPos++;
	updateHeroInfo(iPos);
}