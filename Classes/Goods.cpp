#include "Goods.h"
#include "EntityManager.h"
#include "GameInfo.h"

Goods::Goods()
{
	setType(ET_Goods);
}

void Goods::onEnter()
{
	BaseEntity::onEnter();

	int flashTimes = int(/*GI.getSystemConfig().fFlashingTime*/ 5 * 2.5);
	CCAction* fadeAway = CCSequence::create(
		CCDelayTime::create(/*float(GI.getItemConfig()[2].iExistTime)*/ 5.f),
		CCBlink::create(float(GI.getSystemConfig().fFlashingTime), flashTimes),
		CCDelayTime::create(0.2f),
		CCCallFunc::create(this, callfunc_selector(Goods::kill)),
		NULL
		);
	fadeAway->setTag(EGAT_Fade);
	runAction(fadeAway);
}

void Goods::onExit()
{
	BaseEntity::onExit();
}

void Goods::use()
{
	stopActionByTag(EGAT_Fade);
	setVisible(false);
	kill();
}

void Goods::kill()
{
	EM.removeAnEntity(this, ET_Goods);
}