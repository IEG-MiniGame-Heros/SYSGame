#ifndef __SYS_BULLET__
#define __SYS_BULLET__

#include "Effect.h"

/** 
 * ×Óµ¯
 */
class Bullet : public Effect
{
public:
	void onEnter();
	void onExit();

	static Bullet* create(const char *pszFileName);

};
#endif