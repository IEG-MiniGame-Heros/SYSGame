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
	 * @brief ��Ӧ�����¼�
	 */
	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);

	void onPause(CCObject* pSender); //��ͣ
	void onResume(CCObject* pSender);//�ָ�

protected:

	CCPoint			m_tBeginPos;		// ������������ʼλ��
	CCSprite*       m_pauseBg;          // ��ͣ����
};

#endif