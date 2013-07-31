#ifndef SYS_GOODS
#define SYS_GOODS

#include "BaseEntity.h"
#include "cocos2d.h"

USING_NS_CC;

class Goods : public BaseEntity
{
public:
	virtual void onEnter();
	virtual void onExit();

	virtual void use();

	bool init();

protected:

	int			m_iID;				// µÀ¾ßID

};
#endif