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
	void createGameOverUI();

	void replaceScrene(float dt);

	void btnPauseCallback(cocos2d::CCObject *pSender);
	void btnResumeCallback(cocos2d::CCObject *pSender);
	void btnRestartCallback(cocos2d::CCObject *pSender);
	void btnBackMenuCallback(cocos2d::CCObject *pSender);

	void setText(UILabelAtlas *la, const char *s);

	void setCoin(int CoinNum);
	void setScore(int Score);
	void setMonsterKillNum(int KillNum);
	void setMin(int min);
	void setSec(int sec);

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
	UILabelAtlas *laMin;
	UILabelAtlas *laSec;
};

#endif