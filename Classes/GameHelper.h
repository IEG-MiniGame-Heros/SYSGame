#ifndef SYS_GAME_HELPER
#define SYS_GAME_HELPER

#include "cocos2d.h"

USING_NS_CC;

/** 
 * 这个类作为刷怪、刷道具的一个辅助类
 */
class GameHelper : public CCNode
{
public:

	void onEnter();
	void onExit();

	void onUpdateMonster(float dt);
	void onUpdateGoods(float dt);
	void onUpdateGridUsage(float dt);

private:

	CCPoint getRandomFreeGrid();	

private:

	CCPoint			m_Points[22 * 22];
	int				m_PointsIndex[22 * 22];

	bool			m_bUsed[22][22];			// 标记地图上某一格是否被占用

};

#endif