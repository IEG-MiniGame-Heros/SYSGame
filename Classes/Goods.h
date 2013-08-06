#ifndef SYS_GOODS
#define SYS_GOODS

#include "BaseEntity.h"
#include "cocos2d.h"

#include "Comm.h"

USING_NS_CC;

class Goods : public BaseEntity
{
public:
	Goods();

	virtual void onEnter();
	virtual void onExit();

	virtual void use();

protected:

	EGoodType	m_iID;				// µÀ¾ßID

};
#endif