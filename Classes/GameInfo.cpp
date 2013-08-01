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

	// Ӣ��
	PathOfHero = "Hero1.png";
	RangeToPickupHero = 80.f;
	HeroInitSpeed = 1.5f;
	HeroMaxSpeed = 2.0f;

	// ��
	PathOfMonster = "Monster1.png";
	MonsterInitSpeed = 1.0f;
	MonsterMaxSpeed = 2.0f;

	// ��ͼ
	MapN = M_N;
	MapM = M_M;
	GridSize = 80.f;

	// ����
	ValidDraggedLength = 10.f;

}