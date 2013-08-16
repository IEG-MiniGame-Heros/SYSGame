#include "MainGame.h"	
#include "Character.h"
#include "Queue.h"
#include "GameInfo.h"
#include "GameInfo.h"
#include "StartScrene.h"
#include "FirstStage.h"

void MainGame::onEnter()
{
	cocos2d::CCLayer::onEnter();

	///////// ������Ϸ�еĻ������� /////////

	//��������
	setTouchEnabled(true);

	// ��ͣ������UI
	ulGameControl = UILayer::create();
	this->addChild(ulGameControl, 200, 150);
	ulGameControl->addWidget(CCUIHELPER->createWidgetFromJsonFile("ui/screne_game/screne_game_1.ExportJson"));

	// ��ͣ��ť
	btnPause = dynamic_cast<UIButton*>(ulGameControl->getWidgetByName("Button"));
	btnPause->addPushDownEvent(this, coco_releaseselector(MainGame::btnPauseCallback));

	laMonster = dynamic_cast<UILabelAtlas*>(ulGameControl->getWidgetByName("la_monster"));
	laCoin = dynamic_cast<UILabelAtlas*>(ulGameControl->getWidgetByName("la_money"));
	laScore = dynamic_cast<UILabelAtlas*>(ulGameControl->getWidgetByName("la_score"));
	laTime = dynamic_cast<UILabelAtlas*>(ulGameControl->getWidgetByName("la_time"));

	setText(laMonster, "12");
	setText(laCoin, "1234");
	setText(laScore, "12345");
	setText(laTime, "11");

	ulGameControl->setTouchEnabled(true);
}

void MainGame::setText(UILabelAtlas *la, const char *s)
{
	if (la == NULL || s == NULL)
		return;
	la->setStringValue(s);
}

void MainGame::createPauseUI()
{
	// ��ʾ��ͣ����
	CCPoint nowViewPos = ulGameControl->getPosition();
	ulPause = UILayer::create();
	this->addChild(ulPause, 300, 200);
	ulPause->addWidget(CCUIHELPER->createWidgetFromJsonFile("ui/screne_pause/screne_pause_1.ExportJson"));
	ulPause->setPosition(nowViewPos);

	// �ָ���ť
	UIButton *btnResume = dynamic_cast<UIButton*>(ulPause->getWidgetByName("btn_continue"));
	btnResume->addPushDownEvent(this, coco_releaseselector(MainGame::btnResumeCallback));

	// ���¿�ʼ��ť
	UIButton *btnRestart = dynamic_cast<UIButton*>(ulPause->getWidgetByName("btn_restart"));
	btnRestart->addPushDownEvent(this, coco_releaseselector(MainGame::btnRestartCallback));

	// �������˵���ť
	UIButton *btnBackMenu = dynamic_cast<UIButton*>(ulPause->getWidgetByName("btn_back"));
	btnBackMenu->addPushDownEvent(this, coco_releaseselector(MainGame::btnBackMenuCallback));

	// ����͸����
	UIPanel *p = dynamic_cast<UIPanel*>(ulPause->getWidgetByName("Panel"));
	p->setBackGroundColorOpacity(150);
}

void MainGame::btnPauseCallback(cocos2d::CCObject *pSender)
{
	createPauseUI();
	// ��ͣ��Ϸ
	CCDirector::sharedDirector()->pause();
	// ������ͣ��ť
	btnPause->setVisible(false);
}

void MainGame::btnResumeCallback(cocos2d::CCObject *pSender)
{
	// �Ƴ���ͣ����
	ulPause->dispose();
	// �ָ���Ϸ
	CCDirector::sharedDirector()->resume();
	// ��ʾ��ͣ��ť
	btnPause->setVisible(true);
}


void MainGame::btnRestartCallback(cocos2d::CCObject *pSender)
{
	//���¿�ʼ��Ϸ
	CCDirector::sharedDirector()->replaceScene(FirstStage::scene());
	CCDirector::sharedDirector()->resume();
}

void MainGame::btnBackMenuCallback(cocos2d::CCObject *pSender)
{
	// �ָ���Ϸ
	CCDirector::sharedDirector()->resume();
	CCDirector::sharedDirector()->replaceScene(StartScrene::scene());
}

void MainGame::onExit()
{
	cocos2d::CCLayer::onExit();
}

void MainGame::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	//CCLog("ccTouchesBegan");
	CCSetIterator it = pTouches->begin();
	CCTouch* touch = (CCTouch*)(*it);
	m_tBeginPos = touch->getLocation();  
}

void MainGame::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	CCSetIterator it = pTouches->begin();
	CCTouch* touch = (CCTouch*)(*it);

	CCPoint curPos = touch->getLocation();
	CCPoint slideDir = ccpSub(curPos, m_tBeginPos);
	if (slideDir.getLengthSq() < GI.ValidDraggedLength * GI.ValidDraggedLength)
	{		
		return;
	}

	CCPoint moveVector;
	if (fabs(slideDir.x) > fabs(slideDir.y)) 
	{
		// ���һ���
		moveVector = ccp(slideDir.x < 0 ? -1 : 1, 0);	
	}
	else 
	{
		// ���»���
		moveVector = ccp(0, slideDir.y < 0 ? -1 : 1);
	}

	if (GI.Me)
	{
		//GI.Me->setMoveVector(moveVector);
		GI.Me->setNextMoveVector(moveVector);
	}
}