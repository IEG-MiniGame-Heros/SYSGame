#include "IntroduceScrene.h"
#include "SelectHeroScrene.h"
#include "CocostudioReader/CCJsonReader.h"

CCScene* IntroduceScrene::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		IntroduceScrene *layer = IntroduceScrene::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}

bool IntroduceScrene::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(! CCLayerColor::initWithColor( ccc4(0,0,0,255) ) );

		CCNode *root = createGameScene();
		CC_BREAK_IF(!root);
		this->addChild(root, 0, 1);

		// ��ȡUI��
		CCComRender *pRender = (CCComRender*)(m_pCurNode->getChildByTag(1)->getComponent("GUIComponent"));
		ul = (UILayer*)(pRender->getRender());
		// ��ȡ������ť
		btnContinue = dynamic_cast<UIButton*>(ul->getWidgetByName("btn_continue"));
		btnContinue->addPushDownEvent(this, coco_releaseselector(IntroduceScrene::tbContinueCallback));

		// ������Ļ
		isOver = 0;  
		//�õ�ģ������͸�  
		float SW = CCDirector::sharedDirector()->getWinSize().width;  
		float SH = CCDirector::sharedDirector()->getWinSize().height;  
 
		CCSprite* sp = CCSprite::create("ui/introduce/zimu.png", CCRect(0, 0, 400, 100));  

		//����ˮƽ���������ģ����  
		sp->setPosition(ccp(SW*0.5, sp->getContentSize().height*0.5 + 100));  
		addChild(sp,0,99);  

		scheduleUpdate();  

		bRet = true;
	} while (0);

	return bRet;
}

void IntroduceScrene::tbContinueCallback(cocos2d::CCObject *pSender)
{
	CCDirector::sharedDirector()->replaceScene(SelectHeroScrene::scene());
}

cocos2d::CCNode* IntroduceScrene::createGameScene()
{
	CCNode *pNode = CCJsonReader::sharedJsonReader()->createNodeWithJsonFile("ui/introduce/sceneTest.json");
	if (pNode == NULL)
	{
		return NULL;
	}
	m_pCurNode = pNode;

	CCComRender *pLoadRender = (CCComRender*)(m_pCurNode->getChildByTag(1)->getChildByTag(2)->getComponent("CCArmature"));
	CCArmature* armLoad = (CCArmature*)(pLoadRender->getRender());
	armLoad->getAnimation()->playByIndex(0);

	return pNode;
}

void IntroduceScrene::update(float time)  
{  
	CCSprite* sp = (CCSprite*)getChildByTag(99);  
	//��Ļ�����ٶ�  
	isOver += 0.5;  
	sp->setTextureRect(CCRect(0, isOver, 400, 100));  
	//ѭ��������Ļ  
	if (isOver >= 200) {  
		isOver = 0;  
	}  
}  