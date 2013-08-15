#include "GameHelper.h"
#include "Monster.h"
#include "Goods.h"
#include "Hero.h"
#include "EntityManager.h"
#include "GameInfo.h"

#include <algorithm>
#include <cstdlib>
#include <ctime>

void GameHelper::onEnter()
{
	CCNode::onEnter();

	// 初始化随机种子
	srand(time(NULL));

	// 初始化地图坐标
	// ...
	// (1, 1), (1, 2), (1, 3)...
	// (0, 1), (0, 2), (0, 3)...
	CCPoint offset(0, 0);
	CCPoint center = offset + ccp(GI.MapWidth / 2, GI.MapHeight / 2);
	m_OriginPos = center - ccp(GI.GridSize * 11, GI.GridSize * 11);
	m_UpRightPos = center + ccp(GI.GridSize * 11, GI.GridSize * 11);
	CCLog("m_OriginPos = %f, %f", m_OriginPos.x, m_OriginPos.y);
	CCLog("m_UpRightPos = %f, %f", m_UpRightPos.x, m_UpRightPos.y);
	for (int i = 0; i < 22; ++i)
	{
		for (int j = 0; j < 22; ++j)
		{
			int index = i * 22 + j;
			m_Points[index] = m_OriginPos + ccp(j * GI.GridSize, i * GI.GridSize);
		}
	}

	// 设置各种Timer
	schedule(schedule_selector(GameHelper::onUpdateGridUsage));
	schedule(schedule_selector(GameHelper::onUpdateMonster), GI.getMapConfig()[0].vFrequency[0].iRefreshInterval);
}

void GameHelper::onExit()
{
	unschedule(schedule_selector(GameHelper::onUpdateGridUsage));
	unschedule(schedule_selector(GameHelper::onUpdateMonster));

	CCNode::onExit();
}

CCPoint GameHelper::getGridCenter(int i, int j)
{
	return ccpAdd(m_Points[i * 22 + j], ccp(GI.GridSize / 2, GI.GridSize / 2));
}

CCPoint GameHelper::getNearestGridCenter(CCPoint pos)
{
	int i, j;
	getGridIndexOfPos(pos, i, j);
	return getGridCenter(i, j);
}

/** 
 * 检测这个格子在某个方向上的第几个是否可达
 */
bool GameHelper::isReachable(CCPoint pos, CCPoint moveVec, int gridNum) 
{
	int i, j;
	CCPoint desPos = pos + moveVec * (GI.GridSize * gridNum);
	if (!isWithinMap(desPos))
	{
		return false;
	}
	getGridIndexOfPos(desPos, i, j);
	return !m_bUsed[i][j];
}

/** 刷怪位置的缓存 */
CCPoint MonstRetPos[100];

void GameHelper::onUpdateMonster(float dt)
{
	//CCLog("A monster is getRandomFreeGridborned");
	int refreshNum = GI.getMapConfig()[0].vFrequency[0].iRefreshNum;

	// 获取随机的空余格子
	getRandomFreeGrid(MonstRetPos, refreshNum);

	for (int i = 0; i < refreshNum; ++i)
	{
		EM.addAMonster(MonstRetPos[i]);
	}
}

void GameHelper::getGridIndexOfPos(CCPoint pos, int& i, int& j)
{
	i = int((pos.y - m_OriginPos.y) / GI.GridSize);
	j = int((pos.x - m_OriginPos.x) / GI.GridSize);
}

void GameHelper::onUpdateGridUsage(float dt)
{
	// 先清空
	memset(m_bUsed, 0, sizeof(m_bUsed));

	int i, j;
	CCArray* array;
	CCObject* object;

	array = EM.getArrayByType(ET_Monster);
	CCARRAY_FOREACH(array, object)
	{
		if (object && object->retainCount() > 1)
		{
			Monster* monster = (Monster*)(object);
			getGridIndexOfPos(monster->getPosition(), i, j);
			if (i < 22 && j < 22)
			{
				m_bUsed[i][j] = true;
			}
		}
	}

	array = EM.getArrayByType(ET_Hero);
	CCARRAY_FOREACH(array, object)
	{
		if (object && object->retainCount() > 1)
		{
			Hero* hero = (Hero*)(object);
			getGridIndexOfPos(hero->getPosition(), i, j);
			if (i < 22 && j < 22)
			{
				m_bUsed[i][j] = true;
			}
		}
	}

	array = EM.getArrayByType(ET_Goods);
	CCARRAY_FOREACH(array, object)
	{
		if (object && object->retainCount() > 1)
		{
			Goods* good = (Goods*)(object);
			getGridIndexOfPos(good->getPosition(), i, j);
			if (i < 22 && j < 22)
			{
				m_bUsed[i][j] = true;
			}
		}
	}
}

/** 
 * 判断某点是否在有效地图内
 * @param pos 要判断的点
 * @param margin 边缘厚度
 */
bool GameHelper::isWithinMap(CCPoint pos, float margin /* = 0.f */)
{
	if (pos.x - margin < m_OriginPos.x ||
		pos.x + margin > m_UpRightPos.x ||
		pos.y - margin < m_OriginPos.y ||
		pos.y + margin > m_UpRightPos.y)
	{
		return false;
	}
	return true;
}

void GameHelper::getRandomFreeGrid(CCPoint ret[], int num)
{
	int totCount = 0;
	for (int i = 0; i < 22; ++i)
	{
		for (int j = 0; j < 22; ++j)
		{
			if (!m_bUsed[i][j])
			{
				m_PointsIndex[totCount++] = i * 22 + j;
			}
		}
	}

	// 将空余的位置打乱
	random_shuffle(m_PointsIndex, m_PointsIndex + totCount);

	for (int i = 0; i < num; ++i)
	{
		ret[i] = (m_Points[m_PointsIndex[i]] + ccp(GI.GridSize / 2, GI.GridSize / 2));
	}
}


int PB[10];
/** 
 * 怪死后随机生成英雄或者物品
 * 这个概率以后再来调配!!!!!!!
 * @param pos 出生地点
 */
void GameHelper::randomGenHeroOrGoods(CCPoint pos)
{
	PB[0] = 3;	// 英雄
	PB[1] = 4;	// 金币
	PB[2] = 2;	// 血包

	for (int i = 1; i < 3; ++i)
	{
		PB[i] += PB[i - 1];
	}

	int rret = rand() % PB[2];
	if (rret < PB[0])
	{
		EM.addAHero(pos);
	}
	else if (rret < PB[1])
	{
		EM.addAGoods(pos, EGT_Coin);
	}
	else 
	{
		EM.addAGoods(pos, EGT_BloodSupply);
	}
	
}

bool GameHelper::ccpEqual(const CCPoint& p1, const CCPoint& p2) const 
{
	return p1.x == p2.x && p1.y == p2.y;
}

int GameHelper::getRand(int mod)
{
	return rand() % mod;
}