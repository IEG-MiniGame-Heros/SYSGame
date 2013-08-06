#ifndef SYS_SKILL
#define SYS_SKILL

#include "cocos2d.h"

USING_NS_CC;

class Character;
class Effect;

class Skill : public CCNode
{
public:

	virtual void onEnter();
	virtual void onExit();

	/** 
	 * @brief ��⵽�Ƿ������ڹ�����Χ��
	 */
	bool shouldAttack();

	virtual void attack() {}
	virtual void onUpdate(float dt) {}

protected:

	int			m_iDamage;			// �˺�
	float		m_fAttackRange;		// �ж�Ӧ�ù�����Χ
	float		m_fHitRange;		// �ж����з�Χ	
	float		m_fCoolTime;		// ��ȴʱ��
	float		m_fElapseTime;		// �Ѿ���ȥ��ʱ��
	float		m_bIsAttacking;		// �Ƿ����ڹ�����

	Character*	m_pOwner;			// ������ܵ�������
	Character*	m_pTarget;			// ���������ָ�뻺��
	Effect*		m_pEffect;			// ��Чָ��

	float		m_fAttackSpeed;		// �����ٶ�

};
#endif