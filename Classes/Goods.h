#ifndef SYS_GOODS
#define SYS_GOODS

#include "cocos2d.h"

USING_NS_CC;

class Goods : public CCSprite
{
public:
	virtual void onEnter();
	virtual void onExit();

	virtual void use();

protected:

	int			m_iID;				// µÀ¾ßID

};
#endif