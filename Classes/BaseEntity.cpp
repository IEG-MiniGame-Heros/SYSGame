#include "BaseEntity.h"

//EEntityBaseType BaseEntity::getBaseType() const
//{
//	return m_uEntityBaseType;
//}
//
//void BaseEntity::setBaseType(EEntityBaseType base_type)
//{
//	m_uEntityBaseType = base_type;
//}

EEntityType BaseEntity::getType() const 
{
	return m_uEntityType;
}

void BaseEntity::setType(EEntityType type)
{
	m_uEntityType = type;
}

