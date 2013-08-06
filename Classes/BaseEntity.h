#ifndef SYS_BASE_ENTITY
#define SYS_BASE_ENTITY

#include "cocos2d.h"

USING_NS_CC;

enum EEntityType
{
	ET_Goods,			// ��Ʒ������
	ET_Hero,			// Ӣ��
	ET_Monster,			// ����
	ET_Effect,			// ��Ч
	ET_Max
};

class BaseEntity : public CCSprite
{
public:

	/** 
	 * ��ȡEntity����
	 */
	EEntityType getType() const;
	void setType(EEntityType type);

	/** 
	 * ��������Ƿ��ǿ��ƶ���
	 */
	bool isMovable() const;

protected:
	EEntityType				m_uEntityType;
};


#endif