#ifndef SYS_FIRE_BALL
#define SYS_FIRE_BALL

#include "Effect.h"

/** 
 * »ðÇò
 */
class FireBall : public Effect
{
public:
	void onEnter();
	void onExit();

	static FireBall* create(const char *pszFileName);

};
#endif