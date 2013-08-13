#ifndef SYS_COIN
#define SYS_COIN

#include "Goods.h"

class Coin : public Goods
{
public:

	void onEnter();
	void onExit();
	void use();

	static Coin* create(const char *pszFileName);

protected:

	int		m_iValue;		// ½ð±Ò¼ÛÖµ
};

#endif