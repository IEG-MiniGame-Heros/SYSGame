#include "BaseEntity.h"

EEntityType BaseEntity::getType() const 
{
	return m_uEntityType;
}

void BaseEntity::setType(EEntityType type)
{
	m_uEntityType = type;
}

bool BaseEntity::isMovable() const 
{
	if (m_uEntityType == ET_Goods)
	{
		return false;
	}
	return true;
}