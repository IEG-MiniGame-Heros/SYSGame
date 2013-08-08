#ifndef SYS_SELECTHERO
#define SYS_SELECTHERO

#include "Comm.h"
#include "cocos2d.h"
#include "cocos-ext.h"
//#include "CocoGUILIB/System/CocosGUI.h"

USING_NS_CC;
USING_NS_CC_EXT;

struct hero
{
	string path;
	string desc;
};

class SelectHeroScrene : public cocos2d::CCLayer
{

public :
	void initTestData();
	void setDisplayByPos(int pos);

	virtual bool init();
	static cocos2d::CCScene* scene();

	// 左边选择英雄按钮
	void tbSelectLeftCallback(cocos2d::CCObject *pSender);

	// 右边选择英雄按钮
	void tbSelectRightCallback(cocos2d::CCObject *pSender);

	// 开始按钮响应事件
	void tbStartGameCallback(cocos2d::CCObject *pSender);

	CREATE_FUNC(SelectHeroScrene);

private:
	// 测试时使用
	vector<hero> heroList;

	// 当前选择的位置
	int pos;

	UILayer *ul;
	// 左中右三个英雄
	UIImageView *uvLeftHero;
	UIImageView *uvMidHero;
	UIImageView *uvRightHero;
	
	// 左右选择英雄按钮
	UIButton *btnSelectLeft;
	UIButton *btnSelectRight;

	// 英雄描述内容文本去
	UITextArea *taHeroDesc;

	UIButton *btnStartGame;
};

#endif