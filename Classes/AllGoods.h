#ifndef SYS_ALL_GOODS
#define SYS_ALL_GOODS

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

/** 
 * Ѫ��
 */
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

/** 
 * ����(����������Ч)
 */
class IceCube : public Goods
{
public:

	void onEnter();
	void onExit();
	void use();

	static IceCube* create(const char *pszFileName);
};

#endif