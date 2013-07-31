#ifndef SYS_HERO
#define SYS_HERO

#include "Character.h"

class Hero : public Character 
{
public:
	bool init();

	virtual void onEnter();

	virtual void onExit();

	virtual void onUpdate(float dt);

	static Hero* create(const char *pszFileName);

protected:

};
#endif