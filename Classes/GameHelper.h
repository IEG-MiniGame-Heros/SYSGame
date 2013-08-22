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
	CREATE_FUNC(GameHelper);

	void onEnter();
	void onExit();

	int getRand(int mod);

	bool ccpEqual(const CCPoint& p1, const CCPoint& p2) const;
	bool isReverseDir(const CCPoint& dir1, const CCPoint& dir2);
	bool isInGridCenter(CCPoint pos);

	bool isReachable(CCPoint pos, CCPoint moveVec, int gridNum);
	bool isWithinMap(CCPoint pos, float margin = 0.f);

	bool isGridInUsed(int i, int j) const;
	CCPoint getGridCenter(int i, int j);
	CCPoint getNearestGridCenter(CCPoint pos);

	void onUpdateMonster(float dt);
	void onUpdateGridUsage(float dt);

	void randomGenHeroOrGoods(CCPoint pos);

	void getRandomFreeGrid(CCPoint ret[], int& num);

	void getGridIndexOfPos(CCPoint pos, int& i, int& j);

private:	
	
	void initRewardProp();
	int	getCurMonsFreq();

private:

	CCPoint			m_OriginPos;				// 地图原点
	CCPoint			m_UpRightPos;				// 地图右上角

	CCPoint			m_Points[22 * 22];
	int				m_PointsIndex[22 * 22];
	bool			m_bUsed[22][22];			// 标记地图上某一格是否被占用

	int				m_iMonsFreqID;				// 刷怪频率ID

};

#endif