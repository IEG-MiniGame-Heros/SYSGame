#ifndef SYS_RESULTSCRENE
#define SYS_RESULTSCRENE

#include "cocos2d.h"
#include "cocos-ext.h"
#include "CocoGUILIB/System/CocosGUI.h"

USING_NS_CC;
USING_NS_CC_EXT;

class ResultScrene : public cocos2d::CCLayer
{
public :
	virtual bool init();
	ResultScrene() {}
	ResultScrene(int score, int min, int sec, int monsterNum, int coinNum);
	static cocos2d::CCScene* scene();
	static cocos2d::CCScene* scene(int score, int min, int sec, int monsterNum, int coinNum);
	static ResultScrene* create(int score, int min, int sec, int monsterNum, int coinNum);

	void btnBackCallback(CCObject *pSender);
	void btnRestartCallback(CCObject *pSender);

	void update(float dt);

	void save2DataBase();

	CREATE_FUNC(ResultScrene);

private:
	UILayer *ul;
	UIButton *btnBack;
	UIButton *btnRestart;
	UIImageView *iv_newRecord;

	bool isNewRecord;

	int iScore;
	int iMin;
	int iSec;
	int iMonsterNum;
	int iCoinNum;

	int iNowMin;
	int iNowSec;
	int iNowMonsterNum;
	int iNowCoinNum;

	// ����
	UILabelAtlas *laScore;
	// ��
	UILabelAtlas *laMin;
	// ��
	UILabelAtlas *laSec;
	// ɱ����
	UILabelAtlas *laMonsterNum;
	// �����
	UILabelAtlas *laCoinNum;
};

#endif