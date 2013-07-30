#ifndef SYS_FIRST_STAGE
#define SYS_FIRST_STAGE

#include "MainGame.h"
#include "Database.h"

class FirstStage : public MainGame
{
public:

	virtual void onEnter();

	virtual void onExit();

	static cocos2d::CCScene* scene();

	CREATE_FUNC(FirstStage)
};

#endif