#include "cocos2d.h"
#include "CCEGLView.h"
#include "AppDelegate.h"
#include "FirstStage.h"
//#include "LoginScrene.h"
//#include "SelectHeroScrene.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

USING_NS_CC;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
    SimpleAudioEngine::end();
}

bool AppDelegate::applicationDidFinishLaunching()
{
#if (CC_TARGET_PLATFORM !=CC_TARGET_WIN32)//Android下需要复制数据文件
	//检查数据库文件是否已经提取
	if(!isDatabaseFileExist("database.db"))
	{
		copyDatabaseFile("database.db");//要使用的sqlite库文件
	}
#endif

    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

    // turn on display FPS
    pDirector->setDisplayStats(false);

	CCEGLView::sharedOpenGLView()->setDesignResolutionSize(480, 800, kResolutionShowAll);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    //CCScene *pScene = LoginScrene::scene();
	CCScene* pScene = FirstStage::scene();

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();

    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();

    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}


bool AppDelegate::isDatabaseFileExist(const char* pFileName)
{
	if(!pFileName)return false;
	std::string filePath = CCFileUtils::sharedFileUtils()->getWritablePath();
	filePath+=pFileName;
	FILE *pFp = fopen(filePath.c_str(),"r");
	CCLog(filePath.c_str());
	if(pFp)
	{
		fclose(pFp);
		return true;
	}
	return false;
}

void AppDelegate::copyDatabaseFile(const char* pFileName)
{
	std::string strPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(pFileName);
	unsigned long len=0;
	unsigned char* data =NULL;
	data = CCFileUtils::sharedFileUtils()->getFileData(strPath.c_str(),"r",&len);

	std::string destPath = CCFileUtils::sharedFileUtils()->getWritablePath();
	destPath+= pFileName;

	FILE *pFp=fopen(destPath.c_str(),"w+");
	fwrite(data,sizeof(char),len,pFp);
	fclose(pFp);
	delete []data;
	data=NULL;
}