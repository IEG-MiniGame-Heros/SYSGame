#ifndef SYS_BLOODSUPPLY
#define SYS_BLOODSUPPLY

#include "Goods.h"
#include "Comm.h"
USING_NS_CC;
class BloodSupply : public Goods
{
public:

	virtual void onEnter();
	virtual void onExit();
	virtual void use();

	//为什么要在这里重载CCSprite???!!!
	//void  draw();

	static BloodSupply* create(const char *pszFileName);


protected:
	
	int		m_iSupplyAmount;		// 补给量
};
#endif 