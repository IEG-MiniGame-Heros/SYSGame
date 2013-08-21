#ifndef SYS_GOODS
#define SYS_GOODS

#include "BaseEntity.h"
#include "cocos2d.h"

USING_NS_CC;

class Hero;

enum EGoodActionType
{
	EGAT_Fade
};

class Goods : public BaseEntity
{
public:

	Goods();

	virtual void onEnter();
	virtual void onExit();

	virtual void use(Hero* pHero = NULL);

	virtual void kill();

protected:

	int			m_iID;				// µÀ¾ßID

};
#endif