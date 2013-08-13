#ifndef SYS_STARTSCRENE
#define SYS_STARTSCRENE

#include "cocos2d.h"
#include "cocos-ext.h"
#include "CocoGUILIB/System/CocosGUI.h"

USING_NS_CC;
USING_NS_CC_EXT;

class StartScrene : public cocos2d::CCLayer
{
public :
	virtual bool init();
	static cocos2d::CCScene* scene();

	// ��ʼ��Ϸ��ť��Ӧ�¼�
	void tbStartGameCallback(cocos2d::CCObject *pSender);

	// ���ð�ť��Ӧ�¼�
	void tbSettingCallback(cocos2d::CCObject *pSender);

	CREATE_FUNC(StartScrene);

private:
	UILayer *ul;
	UIButton *tbStartGame;
	UIButton *tbSetting;
};

#endif