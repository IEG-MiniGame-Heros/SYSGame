#ifndef SYS_EFFECT
#define SYS_EFFECT

#include "MovingEntity.h"

enum EEffectActionType
{
	EEAT_Frozenning,		// ������ЧTag
};

class Effect : public MovingEntity
{
public:
	Effect();
	virtual void onEnter();
	virtual void onExit();

	/** 
	 * @brief �Ƴ���Ч
	 */
	virtual void kill();

	bool isKilled() const;

	void setTarget(CCPoint target);

protected:
	float			m_fLifeTime;		// ���ʱ��
	bool			m_bShouldMove;		// ��Ч��Ҫ�ƶ�
	CCPoint			m_vTargetPos;		// �����Ҫ�ƶ����ƶ����յ�
	bool			m_bIsKilled;		// �Ѿ���Kill��
};
#endif