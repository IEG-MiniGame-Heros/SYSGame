#include "Goods.h"
#include "EntityManager.h"

Goods::Goods()
{
	setType(ET_Goods);
}

void Goods::onEnter()
{
	BaseEntity::onEnter();
}

void Goods::onExit()
{
	BaseEntity::onExit();
}

void Goods::use()
{
}

void Goods::kill()
{
	EM.removeAnEntity(this, ET_Goods);
}