#include "GameInfo.h"
#include "Character.h"

#include <stdio.h>

GameInfo& GameInfo::instance()
{
	static GameInfo inst;
	return inst;
}

void GameInfo::initData()
{
	string sql;
	vector<map<string, string> > vData;
	int size = 0;

	// 取出配置表信息
	sql = "select * from t_config";
	CCLOG("sql %s", sql.c_str());
	Database::query(sql, vData);
	size = vData.size();
	for(int i = 0; i < size; i++)
	{
		map<string, string>::iterator iter;
		for(iter = vData[i].begin(); iter != vData[i].end(); iter++) 
		{
			if (iter->first == "life_num")
				stConfig.iLifeNum = Util::StringToNumber<int>(iter->second);
			if (iter->first == "reborn_cost")
				stConfig.iRebornCost = Util::StringToNumber<int>(iter->second);
			if (iter->first == "map_size")
				stConfig.iMapSize = Util::StringToNumber<int>(iter->second);
			if (iter->first == "max_move_speed")
				stConfig.iMaxMoveSpeed = Util::StringToNumber<int>(iter->second);
			if (iter->first == "speed_increment")
				stConfig.iSpeedIncrement = Util::StringToNumber<int>(iter->second);
			CCLOG("key: %s, value: %s", iter->first.c_str(), iter->second.c_str());
		}
		CCLOG("-------------");
	}


}

GameInfo::GameInfo()
{
	// 从数据库里面取出数据
	initData();

	Game = NULL;
	Me = NULL;


	// 英雄
	PathOfHero = "Hero1.png";
	RangeToPickupHero = 80.f;
	HeroInitSpeed = 1.5f;
	HeroMaxSpeed = 2.0f;

	// 怪
	PathOfMonster = "Monster1.png";
	MonsterInitSpeed = 1.0f;
	MonsterMaxSpeed = 2.0f;

	// 地图
	MapN = M_N;
	MapM = M_M;
	GridSize = 80.f;

	// 其他
	ValidDraggedLength = 10.f;

}