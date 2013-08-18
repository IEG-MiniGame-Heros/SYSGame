#ifndef SYS_FIRST_STAGE
#define SYS_FIRST_STAGE

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "SimpleAudioEngine.h"
#include "MainGame.h"
#include "Database.h"


class FirstStage : public MainGame
{
public:

	virtual void onEnter();

	virtual void onExit();

	void updateLayer(float dt);

	/** 
	 * 更新显示金币、分数、杀怪数
	 */
	void updateAllScores(float dt);

	static cocos2d::CCScene* scene();

	CREATE_FUNC(FirstStage)
};

#endif