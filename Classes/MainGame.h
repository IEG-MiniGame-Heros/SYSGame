#ifndef SYS_MAIN_GAME
#define SYS_MAIN_GAME

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC_EXT;
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

	void createPauseUI();

	void btnPauseCallback(cocos2d::CCObject *pSender);
	void btnResumeCallback(cocos2d::CCObject *pSender);
	void btnRestartCallback(cocos2d::CCObject *pSender);
	void btnBackMenuCallback(cocos2d::CCObject *pSender);

	void onPause(CCObject* pSender); //暂停
	void onResume(CCObject* pSender);//恢复

protected:

	CCPoint			m_tBeginPos;		// 滑动触屏，开始位置
	CCSprite*       m_pauseBg;          // 暂停界面
	// 暂停按钮，分数UI
	UILayer *ulGameControl;
	// 暂停界面UI
	UILayer *ulPause;
	// 暂停按钮
	UIButton *btnPause;
};

#endif