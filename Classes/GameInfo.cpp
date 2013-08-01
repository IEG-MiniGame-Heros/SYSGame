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

	// Ó¢ÐÛ
	PathOfHero = "Hero1.png";
	RangeToPickupHero = 80.f;
	HeroInitSpeed = 1.5f;
	HeroMaxSpeed = 2.0f;

	// ¹Ö
	PathOfMonster = "Monster1.png";
	MonsterInitSpeed = 1.0f;
	MonsterMaxSpeed = 2.0f;

	// µØÍ¼
	MapN = M_N;
	MapM = M_M;
	GridSize = 80.f;

	// ÆäËû
	ValidDraggedLength = 10.f;

}