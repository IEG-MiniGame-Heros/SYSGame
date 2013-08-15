#ifndef SYS_ALL_GOODS
#define SYS_ALL_GOODS

#include "Goods.h"

/** 
 * 金币
 */
class Coin : public Goods
{
public:

	void onEnter();
	void onExit();
	void use();

	static Coin* create(const char *pszFileName);

protected:

	int		m_iValue;		// 金币价值
};

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