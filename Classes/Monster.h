#ifndef SYS_MONSTER
#define SYS_MONSTER

#include "Character.h"

class Monster : public Character
{
public:
	Monster();

	virtual void onEnter();

	virtual void onExit();

	virtual void onUpdate(float dt);

	static Monster* create(const char *pszFileName);

protected:

};

#endif