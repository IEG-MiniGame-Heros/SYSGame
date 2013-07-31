#include "MapHelper.h"
#include "GameInfo.h"

MapHelper& MapHelper::instance()
{
	static MapHelper inst;
	return inst;
}

MapHelper::MapHelper()
{
	// фад╩
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	ScrrenOrigin = origin;
	ScreenWidth = visibleSize.width;
	ScreenHeight = visibleSize.height;
	ScreenCenter = ccp(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);

	N = GI.MapN;
	M = GI.MapM;
	Width = GI.MapWidth;
	Height = GI.MapHeight;
	GridSize = GI.GridSize;	

	CCPoint left_org = ScreenCenter + ccp(-Width / 2, -Height / 2);
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < M; ++j)
		{
			Grid[i][j] = left_org + ccp(GridSize * i, GridSize * j);
		}
	}
}