#ifndef SYS_SELECTHERO
#define SYS_SELECTHERO

#include "Comm.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "CocoGUILIB/System/CocosGUI.h"

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

	// ���ѡ��Ӣ�۰�ť
	void tbSelectLeftCallback(cocos2d::CCObject *pSender);

	// �ұ�ѡ��Ӣ�۰�ť
	void tbSelectRightCallback(cocos2d::CCObject *pSender);

	// ��ʼ��ť��Ӧ�¼�
	void tbStartGameCallback(cocos2d::CCObject *pSender);

	CREATE_FUNC(SelectHeroScrene);

private:
	// ����ʱʹ��
	vector<hero> heroList;

	// ��ǰѡ���λ��
	int pos;

	UILayer *ul;
	// ����������Ӣ��
	UIImageView *uvLeftHero;
	UIImageView *uvMidHero;
	UIImageView *uvRightHero;
	
	// ����ѡ��Ӣ�۰�ť
	UIButton *btnSelectLeft;
	UIButton *btnSelectRight;

	// Ӣ�����������ı�ȥ
	UITextArea *taHeroDesc;

	UIButton *btnStartGame;
};

#endif