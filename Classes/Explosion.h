#ifndef SYS_EXPLOSION
#define SYS_EXPLOSION

#include "Effect.h"

/** 
 * À¿Õˆ∫Û±¨’®∂Øª≠
 */
class Explosion : public Effect
{
public:

	void onEnter();
	void onExit();

	static Explosion* create(const char *pszFileName);
};

#endif