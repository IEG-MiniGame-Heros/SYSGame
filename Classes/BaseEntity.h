#ifndef SYS_BASE_ENTITY
#define SYS_BASE_ENTITY

#include "cocos2d.h"

USING_NS_CC;

enum EEntityType
{
	ET_Goods,			// 物品道具类
	ET_Hero,			// 英雄
	ET_Monster,			// 怪物
	ET_Effect,			// 特效
	ET_Max
};

class BaseEntity : public CCSprite
{
public:

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