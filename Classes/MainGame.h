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
	 * @brief ��Ӧ�����¼�
	 */
	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);

	void createPauseUI();

	void btnPauseCallback(cocos2d::CCObject *pSender);
	void btnResumeCallback(cocos2d::CCObject *pSender);
	void btnRestartCallback(cocos2d::CCObject *pSender);
	void btnBackMenuCallback(cocos2d::CCObject *pSender);

	void setText(UILabelAtlas *la, const char *s);

protected:

	CCPoint			m_tBeginPos;		// ������������ʼλ��
	CCSprite*       m_pauseBg;          // ��ͣ����
	// ��ͣ��ť������UI
	UILayer *ulGameControl;
	// ��ͣ����UI
	UILayer *ulPause;
	// ��ͣ��ť
	UIButton *btnPause;

	// ɱ����
	UILabelAtlas *laMonster;
	// �����
	UILabelAtlas *laCoin;
	// ����
	UILabelAtlas *laScore;
	// ʱ��
	UILabelAtlas *laTime;
};

#endif