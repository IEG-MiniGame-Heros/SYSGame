#include "GameHelper.h"
#include "Monster.h"
#include "Goods.h"
#include "Hero.h"
#include "EntityManager.h"
#include "GameInfo.h"


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
	CCPoint origin(0, 0);
	CCPoint center = origin + ccp(GI.MapWidth / 2, GI.MapHeight / 2);
	CCPoint offset = center - ccp(GI.GridSize * 11, GI.GridSize * 11);
	CCLog("offset = %f, %f", offset.x, offset.y);
	for (int i = 0; i < 22; ++i)
	{
		for (int j = 0; j < 22; ++j)
		{
			int index = i * 22 + j;
			m_Points[index] = offset + ccp(j * GI.GridSize, i * GI.GridSize);
		}
	}


}

void GameHelper::onExit()
{
	CCNode::onExit();
}

CCPoint GameHelper::getGridCenter(int i, int j)
{
	return ccpAdd(m_Points[i * 22 + j], ccp(GI.GridSize / 2, GI.GridSize / 2));
}

void GameHelper::onUpdateMonster(float dt)
{

}

void GameHelper::onUpdateGoods(float dt)
{

}

void GetIndexOfPos(const CCPoint& pos, int& i, int& j)
{
	i = int(pos.y / GI.GridSize);
	j = int(pos.x / GI.GridSize);
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
			GetIndexOfPos(monster->getPosition(), i, j);
			m_bUsed[i][j] = true;
		}
	}

	array = EM.getArrayByType(ET_Hero);
	CCARRAY_FOREACH(array, object)
	{
		if (object && object->retainCount() > 1)
		{
			Hero* hero = (Hero*)(object);
			GetIndexOfPos(hero->getPosition(), i, j);
			m_bUsed[i][j] = true;
		}
	}

	array = EM.getArrayByType(ET_Goods);
	CCARRAY_FOREACH(array, object)
	{
		if (object && object->retainCount() > 1)
		{
			Goods* good = (Goods*)(object);
			GetIndexOfPos(good->getPosition(), i, j);
			m_bUsed[i][j] = true;
		}
	}
}

CCPoint GameHelper::getRandomFreeGrid()
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

	int ret = rand() % totCount;
	CCPoint offSet(GI.GridSize / 2, GI.GridSize / 2);

	return (m_Points[m_PointsIndex[ret]] + offSet);
}
