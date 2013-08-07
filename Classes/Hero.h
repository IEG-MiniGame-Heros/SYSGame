#ifndef SYS_HERO
#define SYS_HERO

#include "Character.h"

enum EHeroActionTag
{
	EHAT_Fade		// ��ʧ��Tag
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

	bool		m_bIsPickedUp;		// �Ƿ�ʰȡ��

};
#endif