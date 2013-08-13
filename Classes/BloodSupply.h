#ifndef SYS_BLOODSUPPLY
#define SYS_BLOODSUPPLY

#include "Goods.h"
#include "Comm.h"
USING_NS_CC;
class BloodSupply : public Goods
{
public:
	BloodSupply();

	virtual void onEnter();
	virtual void onExit();
	virtual void use();
	void  draw();

	static BloodSupply* create(const char *pszFileName);


protected:
	
	int		m_iSupplyAmount;		// ²¹¸øÁ¿
};
#endif 