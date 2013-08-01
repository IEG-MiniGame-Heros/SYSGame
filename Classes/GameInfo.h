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

	// 英雄
	std::string			PathOfHero;					// 英雄的图片路径	
	float				RangeToPickupHero;			// “吃”英雄的有效范围
	float				HeroInitSpeed;				// 英雄初始速度
	float				HeroMaxSpeed;				// 英雄最大速度

	// 地图相关
	int					MapN;						//
	int					MapM;						// N行M列的地图
	int					MapWidth;					// 地图宽度
	int					MapHeight;					// 地图高度
	int					GridSize;					// 地图每一小格的大小

	// 其他
	float				ValidDraggedLength;			// 有效的滑动距离，在此基础上才进行滑动判定
};