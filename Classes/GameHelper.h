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

};

#endif