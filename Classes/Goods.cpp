#include "Goods.h"

void Goods::onEnter()
{
	CCSprite::onEnter();
}

void Goods::onExit()
{
	CCSprite::onEnter();
}

void Goods::use()
{
}

bool Goods::init()
{
	if (!CCSprite::init())
	{
		return false;
	}

	setType(ET_Goods);
	return true;
}