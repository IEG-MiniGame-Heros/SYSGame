#ifndef SYS_GAME_HELPER
#define SYS_GAME_HELPER

#include "cocos2d.h"

USING_NS_CC;

/** 
 * �������Ϊˢ�֡�ˢ���ߵ�һ��������
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

	bool			m_bUsed[22][22];			// ��ǵ�ͼ��ĳһ���Ƿ�ռ��

};

#endif