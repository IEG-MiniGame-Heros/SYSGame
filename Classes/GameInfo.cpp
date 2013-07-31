#include "GameInfo.h"
#include "Character.h"

#include <stdio.h>

GameInfo& GameInfo::instance()
{
	static GameInfo inst;
	return inst;
}

GameInfo::GameInfo()
{
	Game = NULL;
	Me = NULL;
	PathOfHero = "Hero1.png";
	ValidDraggedLength = 10.f;

	// ��ͼ
	MapN = M_N;
	MapM = M_M;
	GridSize = 80.f;

}