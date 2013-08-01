#include "MainGame.h"	
#include "Character.h"
#include "Queue.h"
#include "GameInfo.h"

void MainGame::onEnter()
{
	cocos2d::CCLayer::onEnter();

	///////// ������Ϸ�еĻ������� /////////

	// ��������
	setTouchEnabled(true);
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
		GI.Me->setMoveVector(moveVector);
	}
}