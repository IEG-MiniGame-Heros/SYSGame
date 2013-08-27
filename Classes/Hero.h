#ifndef SYS_HERO
#define SYS_HERO

#include "Character.h"

// ��ʾʱ��ϵ��������Tag
enum EHeroQueueNumTag
{
	EHQNT_X		=	201308230,		// x
	EHQNT_1		=	201308231,		// ��һλ
	EHQNT_2		=	201308232,		// �ڶ�λ
	EHQNT_3		=	201308233,		// ����λ
};

class Hero : public Character 
{
public:
	Hero();
	Hero(int ID);

	virtual void onEnter();

	virtual void onExit();

	virtual void onUpdate(float dt);

	static Hero* create(const char *pszFileName, int HeroID);

	void setIsPickedUp(bool is_picked_up);
	bool isPickedUp() const;

	void showQueueNum(int QueueNum);

	/** 
	 * �����е��õģ��������ӣ��ٶ�����
	 * Ҫ����Anim��setDelayPerUnit
	 */
	void setAnimFreq();


protected:

	bool		m_bIsPickedUp;		// �Ƿ�ʰȡ��
	float		m_fSpeedIncrement;	// ÿ����һ��Ӣ�����ӵ��ٶ�
	int			m_iHeroID;			// Ӣ��ID

};
#endif