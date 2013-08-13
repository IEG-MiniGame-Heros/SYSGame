#ifndef SYS_HPSHOW
#define SYS_HPSHOW

#include "cocos2d.h"
USING_NS_CC;

class SYS_HPSHOW: public cocos2d::CCLayer {
private:
	int life;
public:
	SYS_HPSHOW():life(100) {};
	int getlife();
	void setlife(int tmp);
	void draw();
};

#endif