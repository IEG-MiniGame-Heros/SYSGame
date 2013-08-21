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

	// ��ʼ���������
	srand(time(NULL));

	// ��ʼ����ͼ����
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

	memset(m_bUsed, 0, sizeof(m_bUsed));

	// ��ʼ�����ֽ����������
	initRewardProp();

	// ���ø���Timer
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
 * ������������ĳ�������ϵĵڼ����Ƿ�ɴ�
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

/** ˢ��λ�õĻ��� */
CCPoint MonstRetPos[100];

void GameHelper::onUpdateMonster(float dt)
{
	//CCLog("A monster is getRandomFreeGridborned");
	int refreshNum = GI.getMapConfig()[0].vFrequency[0].iRefreshNum;

	// ��ȡ����Ŀ������
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
	// �����
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
 * �ж�ĳ���Ƿ�����Ч��ͼ��
 * @param pos Ҫ�жϵĵ�
 * @param margin ��Ե���
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

void GameHelper::getRandomFreeGrid(CCPoint ret[], int& num)
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

	// �������λ�ô���
	random_shuffle(m_PointsIndex, m_PointsIndex + totCount);

	// �����Ļ�
	if (totCount < num)
	{
		num = totCount;
	}

	for (int i = 0; i < num; ++i)
	{
		ret[i] = (m_Points[m_PointsIndex[i]] + ccp(GI.GridSize / 2, GI.GridSize / 2));
	}
}

const int MAX_REWARDS_NUM = 7;
int RP[10] = {0};
/** 
 * ��ʼ�����佱Ʒ�ĸ���
 */
void GameHelper::initRewardProp()
{
	
	CCAssert(MAX_REWARDS_NUM == GI.getRewardConfig().size(), "MAX_REWARDS_NUM is not right!!!");

	RP[0] = 0;
	for (int i = 1; i <= MAX_REWARDS_NUM; ++i)
	{
		RP[i] = GI.getRewardConfig()[i - 1].iWeight;
		RP[i] += RP[i - 1];
	}
}

/** 
 * �������������Ӣ�ۻ�����Ʒ
 * ��������Ժ���������!!!!!!!
 * @param pos �����ص�
 */
void GameHelper::randomGenHeroOrGoods(CCPoint pos)
{
	int rret = getRand(RP[MAX_REWARDS_NUM]);

	// 1.Ӣ��
	// 2.Ѫ��
	// 3.����
	// 4.��ң�1~4��
	// 5.��ң�5~10��
	// 6.��ң�10~15��
	// 7.�޽���

	if (rret < RP[1])
	{
		EM.addAHero(pos);
	}
	else if (rret < RP[2])
	{
		EM.addAGoods(pos, EGT_BloodSupply);
	}
	else if (rret < RP[3])
	{
		EM.addAGoods(pos, EGT_IceCube);
	}
	else if (rret < RP[4])
	{
		int num = 1 + getRand(4);
		EM.addCoins(pos, num);
	}
	else if (rret < RP[5])
	{
		int num = 5 + getRand(6);
		EM.addCoins(pos, num);
	}
	else if (rret < RP[6])
	{
		int num = 11 + getRand(5);
		EM.addCoins(pos, num);
	}
	else if (rret < RP[7])
	{
		// ʲô��û����
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

bool GameHelper::isReverseDir(const CCPoint& dir1, const CCPoint& dir2)
{
	return  (dir1.x == (dir2.x * -1)) && (dir1.y == (dir2.y * -1));
}

bool GameHelper::isInGridCenter(CCPoint pos)
{
	if (isWithinMap(pos))
	{
		CCPoint center = getNearestGridCenter(pos);
		if (fabs(pos.x - center.x) < 1e-6 &&
			fabs(pos.y - center.y) < 1e-6)
		{
			return true;
		}
	}
	return false;
}