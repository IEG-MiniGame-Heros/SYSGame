#include "MainGame.h"	
#include "Character.h"
#include "Queue.h"
#include "GameInfo.h"
#include "GameInfo.h"
#include "StartScrene.h"

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

	ulGameControl->setTouchEnabled(true);
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

	UIButton *btnBackMenu = dynamic_cast<UIButton*>(ulPause->getWidgetByName("btn_back"));
	btnBackMenu->addPushDownEvent(this, coco_releaseselector(MainGame::btnBackMenuCallback));

	// 设置透明度
	UIPanel *p = dynamic_cast<UIPanel*>(ulPause->getWidgetByName("Panel"));
	p->setBackGroundColorOpacity(150);
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

// TODO :: kongcheng
void MainGame::btnRestartCallback(cocos2d::CCObject *pSender)
{

}

void MainGame::btnBackMenuCallback(cocos2d::CCObject *pSender)
{
	CCDirector::sharedDirector()->replaceScene(StartScrene::scene());
}

void MainGame::onPause(CCObject* pSender) //暂停
{
	CCLOG("Game Pause");
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	m_pauseBg = CCSprite::create();
	this->addChild(m_pauseBg,2000);

	CCMenu* menu = (CCMenu*)this->getChildByTag(10);
	menu->setVisible(false);

	CCMenuItemFont* item = CCMenuItemFont::create("Resume",this,menu_selector(MainGame::onResume));
	item->setColor(ccc3(255,255,255));
	item->setFontSize(50);
	CCMenu* resumeMenu = CCMenu::create(item,NULL);
	resumeMenu->setPosition(ccp(size.width/2,size.height/2));
	m_pauseBg->addChild(resumeMenu);

	CCDirector::sharedDirector()->pause();
}

void MainGame::onResume(CCObject* pSender)//恢复
{
	CCMenu* menu = (CCMenu*)this->getChildByTag(10);
	menu->setVisible(true);

	this->removeChild(m_pauseBg);
	CCDirector::sharedDirector()->resume();

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
		GI.Me->setMoveVector(moveVector);
	}
}