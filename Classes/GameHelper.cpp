#include "GameHelper.h"
#include "GameInfo.h"

#include <cstdlib>
#include <ctime>

void GameHelper::onEnter()
{
	CCNode::onEnter();

	// ��ʼ���������
	srand(time(NULL));

	// ��ʼ����ͼ����
	CCPoint origin(0, 0);


	///////////////////////////////


}

void GameHelper::onExit()
{

}

void GameHelper::onUpdateMonster(float dt)
{

}

void GameHelper::onUpdateGoods(float dt)
{

}

void GameHelper::onUpdateGridUsage(float dt)
{

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

	return m_Points[m_PointsIndex[ret]];
}
