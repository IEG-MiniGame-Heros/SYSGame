#include "MainGame.h"	
#include "Character.h"
#include "Queue.h"
#include "GameInfo.h"

void MainGame::onEnter()
{
	cocos2d::CCLayer::onEnter();

	///////// 所有游戏中的基础设置 /////////

	// 开启触屏
	setTouchEnabled(true);

	// 获取屏幕宽度和高度
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	GI.ScrrenOrigin = origin;
	GI.ScreenWidth = visibleSize.width;
	GI.ScreenHeight = visibleSize.height;
	GI.ScreenCenter = ccp(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
}

void MainGame::onExit()
{
	cocos2d::CCLayer::onExit();
}

void MainGame::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	CCLog("ccTouchesBegan");
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