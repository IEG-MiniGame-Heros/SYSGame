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

	int					N;							// ��ͼ����
	int					M;							// ��ͼ����
	int					Width;						// ��ͼ�Ŀ��
	int					Height;						// ��ͼ�ĸ߶�
	int					GridSize;					// ���Ӵ�С
	CCPoint				Grid[MAP_SIZE][MAP_SIZE];	// �����ͼ���ӵ����½ǵĵ�

public:
	// ��Ļ
	CCPoint				ScreenCenter;				// ��Ļ����
	CCPoint				ScrrenOrigin;				// ��Ļԭ��(���½�)
	float				ScreenWidth;				// ��Ļ���
	float				ScreenHeight;				// ��Ļ�߶�

};
#endif