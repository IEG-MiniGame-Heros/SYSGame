#ifndef SYS_EFFECT
#define SYS_EFFECT

#include "MovingEntity.h"

class Effect : public MovingEntity
{
public:
	Effect();
	virtual void onEnter();
	virtual void onExit();

	//void setLifeTime(float time);
	///** 
	// * @brief ������Ч
	// */
	//void play();

	/** 
	 * @brief �Ƴ���Ч
	 */
	void kill();

	void setTarget(CCPoint target);

protected:
	float			m_fLifeTime;		// ���ʱ��
	bool			m_bShouldMove;		// ��Ч��Ҫ�ƶ�
	CCPoint			m_vTargetPos;		// �����Ҫ�ƶ����ƶ����յ�
};
#endif