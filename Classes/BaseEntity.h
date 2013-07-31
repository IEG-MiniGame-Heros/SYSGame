#ifndef SYS_BASE_ENTITY
#define SYS_BASE_ENTITY

#include "cocos2d.h"

USING_NS_CC;

//enum EEntityBaseType
//{
//	EBT_Movable,		// 可以动的
//	EBT_UnMovable		// 不可动的
//};

enum EEntityType
{
	ET_Goods,			// 物品道具类
	ET_Hero,			// 英雄
	ET_Monster,			// 怪物
	ET_Effect,			// 特效
	ET_Max
};

class BaseEntity : public cocos2d::CCNode
{
public:

	///** 
	// * 基本类型,这个类是能动的还是不能动的
	// */
	//EEntityBaseType	getBaseType() const;
	//void setBaseType(EEntityBaseType base_type);

	/** 
	 * 获取Entity类型
	 */
	EEntityType getType() const;
	void setType(EEntityType type);

	/** 
	 * 这个物体是否是可移动的
	 */
	bool isMovable() const;

protected:
	EEntityType				m_uEntityType;
};


#endif