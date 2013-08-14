#ifndef SYS_MAIN_GAME
#define SYS_MAIN_GAME

#include "cocos2d.h"

USING_NS_CC;

class MainGame : public cocos2d::CCLayer
{
public:
	
	virtual void onEnter();
	virtual void onExit();

	/** 
	 * @brief 响应触屏事件
	 */
	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);

	void onPause(CCObject* pSender); //暂停
	void onResume(CCObject* pSender);//恢复

protected:

	CCPoint			m_tBeginPos;		// 滑动触屏，开始位置
	CCSprite*       m_pauseBg;          // 暂停界面
};

#endif