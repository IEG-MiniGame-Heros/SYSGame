#ifndef SYS_HERO
#define SYS_HERO

#include "Character.h"

class Hero : public Character 
{
public:
	Hero();

	virtual void onEnter();

	virtual void onExit();

	virtual void onUpdate(float dt);

	static Hero* create(const char *pszFileName);

	void setIsPickedUp(bool is_picked_up);

	/** 
	 * 给队列调用的，人数增加，速度提升
	 * 要调用Anim的setDelayPerUnit
	 */
	void setAnimFreq();


protected:

	bool		m_bIsPickedUp;		// 是否被拾取了
	float		m_fSpeedIncrement;	// 没增加一个英雄增加的速度

};
#endif