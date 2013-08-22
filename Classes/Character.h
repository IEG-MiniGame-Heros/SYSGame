#ifndef SYS_CHARACTER
#define SYS_CHARACTER

#include "MovingEntity.h"

class Queue;
class Skill;

enum ECharacterActionTag
{
	ECAT_HeroFade,		// Ӣ����ʧ��Tag
	ECAT_BloodFade		// Ѫ����ʧ��Tag
};


const CCPoint WalkVec[4] = 
{
	CCPoint(1, 0),		// ��
	CCPoint(0, -1),		// ��
	CCPoint(-1, 0),		// ��
	CCPoint(0, 1)		// ��
};

class Character : public MovingEntity
{
public:

	virtual void onEnter();

	virtual void onExit();

	virtual bool onMove();

	virtual void onMoveDone();

	virtual void kill();

	virtual void onUpdate(float dt);

	/** 
	 * �����ĸ�����&&���ö���
	 */
	Queue* getQueue() const;
	void setQueue(Queue* pQ);

	/** 
	 * ���ص��˵����ͣ��������Hero,����Monster��
	 * ��֮��Ȼ
	 */
	EEntityType	getEnemyType() const;

	int getCurHealth() const;
	void setCurHealth(int health);

	int getMaxHealth() const;
	void setMaxHealth(int max_health);

	/** 
	 * �ܵ��˺�
	 * @param damage �˺���С
	 * @param bHeroToMonster �ǲ���Ӣ�۴��
	 */
	virtual void getHarmed(int damage, bool bHeroToMonster = false);

	/** 
	 * ��Ѫ�����õ�����
	 */
	void getHeal(int amount);

    /* 
	 * ����������ת��Ϊ��ͼ��������
	 */
    CCPoint tileCoordForPosition(CCPoint pos);

	// ����Ѫ��
	bool initHPStrip();

	// �Ƿ���ʾѪ��
	void setShowHP(bool bShow);

	void stopShowHPCallback();

protected: 

	int				m_iCurHealth;		// ��ǰ����ֵ
	int				m_iMaxHealth;		// �������ֵ
	Queue*			m_pQueue;			// �����ĸ�����
	CCAnimation*	m_pWalkAnim[4];		// ���߶���

	bool			m_bIsPendingKill;	// ������kill��
	
	CCProgressTimer* m_pBloodBar;		// Ѫ��
	CCSprite*		m_pBloodBlack;		// Ѫ����Χ��һ���
	CCAction*		m_pShowHPAct;		// ��ʾѪ��Action
	CCNode*			m_pRunHPActNode;	// RunHP�����Ŀ���
	bool			m_bEnableShowHP;	// ��ʾѪ������

	Skill*			m_pSkill;			// ����ָ��
};
#endif