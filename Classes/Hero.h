#ifndef SYS_HERO
#define SYS_HERO

#include "Character.h"

// 显示时间系数的数字Tag
enum EHeroQueueNumTag
{
	EHQNT_X		=	201308230,		// x
	EHQNT_1		=	201308231,		// 第一位
	EHQNT_2		=	201308232,		// 第二位
	EHQNT_3		=	201308233,		// 第三位
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
	 * 给队列调用的，人数增加，速度提升
	 * 要调用Anim的setDelayPerUnit
	 */
	void setAnimFreq();


protected:

	bool		m_bIsPickedUp;		// 是否被拾取了
	float		m_fSpeedIncrement;	// 没增加一个英雄增加的速度
	int			m_iHeroID;			// 英雄ID

};
#endif