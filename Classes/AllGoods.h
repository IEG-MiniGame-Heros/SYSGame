#ifndef SYS_COIN
#define SYS_COIN

#include "Goods.h"

/** 
 * ���
 */
class Coin : public Goods
{
public:

	void onEnter();
	void onExit();
	void use();

	static Coin* create(const char *pszFileName);

protected:

	int		m_iValue;		// ��Ҽ�ֵ
};

class BloodSupply : public Goods
{
public:

	virtual void onEnter();
	virtual void onExit();
	virtual void use();

	//ΪʲôҪ����������CCSprite???!!!
	//void  draw();

	static BloodSupply* create(const char *pszFileName);

protected:

	int		m_iSupplyAmount;		// ������
};

#endif