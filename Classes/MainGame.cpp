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

	///////// 所有游戏中的基础设置 /////////

	//开启触屏
	setTouchEnabled(true);

	// 暂停、分数UI
	ulGameControl = UILayer::create();
	this->addChild(ulGameControl, 200, 150);
	ulGameControl->addWidget(CCUIHELPER->createWidgetFromJsonFile("ui/screne_game/screne_game_1.ExportJson"));

	// 暂停按钮
	btnPause = dynamic_cast<UIButton*>(ulGameControl->getWidgetByName("Button"));
	btnPause->addPushDownEvent(this, coco_releaseselector(MainGame::btnPauseCallback));

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
	// 显示暂停界面
	CCPoint nowViewPos = ulGameControl->getPosition();
	ulPause = UILayer::create();
	this->addChild(ulPause, 300, 200);
	ulPause->addWidget(CCUIHELPER->createWidgetFromJsonFile("ui/screne_pause/screne_pause_1.ExportJson"));
	ulPause->setPosition(nowViewPos);

	// 恢复按钮
	UIButton *btnResume = dynamic_cast<UIButton*>(ulPause->getWidgetByName("btn_continue"));
	btnResume->addPushDownEvent(this, coco_releaseselector(MainGame::btnResumeCallback));

	// 重新开始按钮
	UIButton *btnRestart = dynamic_cast<UIButton*>(ulPause->getWidgetByName("btn_restart"));
	btnRestart->addPushDownEvent(this, coco_releaseselector(MainGame::btnRestartCallback));

	// 返回主菜单按钮
	UIButton *btnBackMenu = dynamic_cast<UIButton*>(ulPause->getWidgetByName("btn_back"));
	btnBackMenu->addPushDownEvent(this, coco_releaseselector(MainGame::btnBackMenuCallback));

	// 设置透明度
	UIPanel *p = dynamic_cast<UIPanel*>(ulPause->getWidgetByName("Panel"));
	p->setBackGroundColorOpacity(150);
}

void MainGame::createGameOverUI()
{
	// 显示暂停界面
	CCPoint nowViewPos = ulGameControl->getPosition();
	ulPause = UILayer::create();
	this->addChild(ulPause, 300, 200);
	ulPause->addWidget(CCUIHELPER->createWidgetFromJsonFile("ui/screne_gameover/screne_gameover_1.ExportJson"));
	ulPause->setPosition(nowViewPos);

	// 设置透明度
	UIPanel *p = dynamic_cast<UIPanel*>(ulPause->getWidgetByName("Panel"));
	p->setBackGroundColorOpacity(150);

	ulGameControl->dispose();
	// 2秒之后切换场景
	this->schedule(schedule_selector(MainGame::replaceScrene), 2.0f);  
}

void MainGame::replaceScrene(float dt)
{
	this->unschedule(schedule_selector(MainGame::replaceScrene));  
	// TODO ::
	// 结算数据
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
	// 暂停游戏
	CCDirector::sharedDirector()->pause();
	// 隐藏暂停按钮
	btnPause->setVisible(false);
}

void MainGame::btnResumeCallback(cocos2d::CCObject *pSender)
{
	// 移除暂停界面
	ulPause->dispose();
	// 恢复游戏
	CCDirector::sharedDirector()->resume();
	// 显示暂停按钮
	btnPause->setVisible(true);
}


void MainGame::btnRestartCallback(cocos2d::CCObject *pSender)
{
	//重新开始游戏
	CCDirector::sharedDirector()->replaceScene(FirstStage::scene());
	CCDirector::sharedDirector()->resume();
}

void MainGame::btnBackMenuCallback(cocos2d::CCObject *pSender)
{
	// 恢复游戏
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
		// 左右滑动
		moveVector = ccp(slideDir.x < 0 ? -1 : 1, 0);	
	}
	else 
	{
		// 上下滑动
		moveVector = ccp(0, slideDir.y < 0 ? -1 : 1);
	}

	if (GI.Me)
	{
		//GI.Me->setMoveVector(moveVector);
		GI.Me->setNextMoveVector(moveVector);
	}
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