#ifndef SYS_MAP_HELPER
#define SYS_MAP_HELPER

#include "cocos2d.h"

#define MAP_SIZE 30

USING_NS_CC;

class MapHelper
{
public:
	static MapHelper& instance();

	MapHelper();

public:

	int					N;							// 地图行数
	int					M;							// 地图列数
	int					Width;						// 地图的宽度
	int					Height;						// 地图的高度
	int					GridSize;					// 格子大小
	CCPoint				Grid[MAP_SIZE][MAP_SIZE];	// 缓存地图格子的左下角的点

public:
	// 屏幕
	CCPoint				ScreenCenter;				// 屏幕中心
	CCPoint				ScrrenOrigin;				// 屏幕原点(左下角)
	float				ScreenWidth;				// 屏幕宽度
	float				ScreenHeight;				// 屏幕高度

};
#endif