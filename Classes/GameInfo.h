#include "cocos2d.h"

#include <string>

USING_NS_CC;

#define GI (GameInfo::instance())

class Character;
class MainGame;
class Queue;

const int M_N = 20;
const int M_M = 20;

/** 
 * @brief 所有全局信息的单例
 */
class GameInfo
{
public:	
	static GameInfo& instance();

	GameInfo();

public:

public:

	MainGame*			Game;						// 指向当前游戏Layer的指针
	Queue*				Me;							// 指向玩家的指针

	std::string			PathOfHero;					// 英雄的图片路径	
	float				ValidDraggedLength;			// 有效的滑动距离，在此基础上才进行滑动判定

	// 屏幕
	CCPoint				ScreenCenter;				// 屏幕中心
	CCPoint				ScrrenOrigin;				// 屏幕原点(左下角)
	float				ScreenWidth;				// 屏幕宽度
	float				ScreenHeight;				// 屏幕高度

	// 地图相关
	int					MapN;						//
	int					MapM;						// N行M列的地图
	int					GridSize;					// 地图每一小格的大小
	bool				IsConq[M_N][M_M];			// 地图的某一格是否被占领
	CCPoint				Grids[M_N][M_M];			// 每一格的中点
};