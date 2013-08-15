#include "MainGame.h"	
#include "Character.h"
#include "Queue.h"
#include "GameInfo.h"

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


	//暂停按钮
	/*CCMenuItemImage* pauseBtn = CCMenuItemImage::create("ui/pause/pauseBtn.png","ui/pause/resumeBtn.png",this,menu_selector(MainGame::onPause));
	pauseBtn->setAnchorPoint(ccp(1,1));
	CCMenu* menu = CCMenu::create(pauseBtn,NULL);
	menu->setPosition(ccp(100,100));
	addChild(menu,1000,10);*/
}

void MainGame::btnPauseCallback(cocos2d::CCObject *pSender)
{
	CCDirector::sharedDirector()->pause();
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