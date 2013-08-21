#include "MainGame.h"	
#include "Character.h"
#include "Queue.h"
#include "GameInfo.h"
#include "GameInfo.h"
#include "FirstStage.h"
#include "StartScrene.h"
#include "ResultScrene.h"
#include "Util.h"

void MainGame::onEnter()
{
	cocos2d::CCLayer::onEnter();

	///////// ������Ϸ�еĻ������� /////////

	//��������
	setTouchEnabled(true);
	m_bTouchBegin = false;

	// ��ͣ������UI
	ulGameControl = UILayer::create();
	this->addChild(ulGameControl, 200, 150);
	ulGameControl->addWidget(CCUIHELPER->createWidgetFromJsonFile("ui/screne_game/screne_game_1.ExportJson"));

	// ��ͣ��ť
	btnPause = dynamic_cast<UIButton*>(ulGameControl->getWidgetByName("Button"));
	btnPause->addReleaseEvent(this, coco_releaseselector(MainGame::btnPauseCallback));

	laMonster = dynamic_cast<UILabelAtlas*>(ulGameControl->getWidgetByName("la_monster"));
	laCoin = dynamic_cast<UILabelAtlas*>(ulGameControl->getWidgetByName("la_money"));
	laScore = dynamic_cast<UILabelAtlas*>(ulGameControl->getWidgetByName("la_score"));
	laMin = dynamic_cast<UILabelAtlas*>(ulGameControl->getWidgetByName("la_min"));
	laSec = dynamic_cast<UILabelAtlas*>(ulGameControl->getWidgetByName("la_sec"));

	setText(laMonster, "0");
	setText(laCoin, "0");
	setText(laScore, "0");
	setText(laMin, "0");
	setText(laSec, "0");

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
	btnResume->addReleaseEvent(this, coco_releaseselector(MainGame::btnResumeCallback));
	btnResume->setPressedTexture("ui/screne_pause/big_continue.png");

	// ���¿�ʼ��ť
	UIButton *btnRestart = dynamic_cast<UIButton*>(ulPause->getWidgetByName("btn_restart"));
	btnRestart->addReleaseEvent(this, coco_releaseselector(MainGame::btnRestartCallback));
	btnRestart->setPressedTexture("ui/screne_pause/big_restart.png");

	// �������˵���ť
	UIButton *btnBackMenu = dynamic_cast<UIButton*>(ulPause->getWidgetByName("btn_back"));
	btnBackMenu->addReleaseEvent(this, coco_releaseselector(MainGame::btnBackMenuCallback));
	btnBackMenu->setPressedTexture("ui/screne_pause/big_back_main.png");

	// ����͸����
	UIPanel *p = dynamic_cast<UIPanel*>(ulPause->getWidgetByName("Panel"));
	p->setBackGroundColorOpacity(150);
}

void MainGame::createGameOverUI()
{
	// ��ʾ��ͣ����
	CCPoint nowViewPos = ulGameControl->getPosition();
	ulPause = UILayer::create();
	this->addChild(ulPause, 300, 200);
	ulPause->addWidget(CCUIHELPER->createWidgetFromJsonFile("ui/screne_gameover/screne_gameover_1.ExportJson"));
	ulPause->setPosition(nowViewPos);

	// ����͸����
	UIPanel *p = dynamic_cast<UIPanel*>(ulPause->getWidgetByName("Panel"));
	p->setBackGroundColorOpacity(150);

	ulGameControl->dispose();
	// 2��֮���л�����
	this->schedule(schedule_selector(MainGame::replaceScrene), 2.0f);  
}

void MainGame::replaceScrene(float dt)
{
	this->unschedule(schedule_selector(MainGame::replaceScrene));  
	// TODO ::
	// ��������
	int Sec = int(GI.ChallengeTime) % 60;
	int Min = int(GI.ChallengeTime) / 60;
	int Score = int(GI.Score);
	int MonsterNum = GI.MonsterKillNum;
	int CoinNum = GI.Coin;
	CCDirector::sharedDirector()->replaceScene(ResultScrene::scene(Score, Min, Sec, MonsterNum, CoinNum));
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

	m_bTouchBegin = true;
}

void MainGame::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	CCSetIterator it = pTouches->begin();
	CCTouch* touch = (CCTouch*)(*it);

	CCPoint curPos = touch->getLocation();
	CCPoint slideDir = ccpSub(curPos, m_tBeginPos);
	if (!m_bTouchBegin || slideDir.getLengthSq() < GI.ValidDraggedLength * GI.ValidDraggedLength)
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
		GI.Me->setNextMoveVector(moveVector);
	}
}

void MainGame::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	m_bTouchBegin = false;
}


void MainGame::setCoin(int CoinNum)
{
	setText(laCoin, (Util::NumberToString(CoinNum)).c_str());
}

void MainGame::setScore(int Score)
{
	setText(laScore, (Util::NumberToString(Score)).c_str());
}

void MainGame::setMonsterKillNum(int KillNum)
{
	setText(laMonster, (Util::NumberToString(KillNum)).c_str());
}

void MainGame::setMin(int min)
{
	setText(laMin, N2C(min));
}

void MainGame::setSec(int sec)
{
	setText(laSec, N2C(sec));
}