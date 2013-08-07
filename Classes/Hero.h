#ifndef SYS_HERO
#define SYS_HERO

#include "Character.h"

enum EHeroActionTag
{
	EHAT_Fade		// 消失的Tag
};

class Hero : public Character 
{
public:
	Hero();

	virtual void onEnter();

	virtual void onExit();

	virtual void onUpdate(float dt);

	static Hero* create(const char *pszFileName);

	void setIsPickedUp(bool is_picked_up);

	void kill();


protected:

	bool		m_bIsPickedUp;		// 是否被拾取了

};
#endif