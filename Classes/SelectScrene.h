#ifndef SYS_SELECTSCRENE
#define SYS_SELECTSCRENE

#include "cocos2d.h"
#include "cocos-ext.h"
#include "CocoGUILIB/System/CocosGUI.h"

USING_NS_CC;
USING_NS_CC_EXT;

class SelectScrene : public cocos2d::CCLayer
{
public :
	virtual bool init();
	static cocos2d::CCScene* scene();

	void btnBackCallback(CCObject *pSender);
	void btnOKCallback(CCObject *pSender);
	void btnSettingCallback(CCObject *pSender);
	void btnLeftCallback(CCObject *pSender);
	void btnRightCallback(CCObject *pSender);

	void updateHeroInfo(int pos);

	CREATE_FUNC(SelectScrene);

private:
	int iPos;
	UILayer *ul;

	UIButton *btnBack;
	UIButton *btnOK;
	UIButton *btnSetting;
	UIButton *btnLeft;
	UIButton *btnRight;

	UIImageView *iv_name;
	UIImageView *iv_heroPic;
	UIImageView *iv_HP;
	UIImageView *iv_moveSpeed;
	UIImageView *iv_skillSpeed;
	UIImageView *iv_attack;
	UIImageView *iv_range;
	UIImageView *iv_cd;
	UIImageView *iv_desc;
};

#endif