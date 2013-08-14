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
	CCLOG("sql:%s", sql.c_str());
	vData.clear();
	Database::query(sql, vData);
	size = vData.size();
	for(int i = 0; i < size; i++)
	{
		map<string, string>::iterator iter;
		for(iter = vData[i].begin(); iter != vData[i].end(); iter++) 
		{
			if (iter->first == "life_num")
				stSystemConfig.iLifeNum = Util::StringToNumber<int>(iter->second);
			if (iter->first == "reborn_cost")
				stSystemConfig.iRebornCost = Util::StringToNumber<int>(iter->second);
			if (iter->first == "map_size")
				stSystemConfig.iMapSize = Util::StringToNumber<int>(iter->second);
			if (iter->first == "max_move_speed")
				stSystemConfig.fMaxMoveSpeed = Util::StringToNumber<float>(iter->second);
			if (iter->first == "speed_increment")
				stSystemConfig.fSpeedIncrement = Util::StringToNumber<float>(iter->second);
			if (iter->first == "time_coefficient")
				stSystemConfig.fTimeCoefficient = Util::StringToNumber<float>(iter->second);
			if (iter->first == "coin_coefficient")
				stSystemConfig.fCoinCoefficient = Util::StringToNumber<float>(iter->second);
			if (iter->first == "monster_coefficient")
				stSystemConfig.fMonsterCoefficient = Util::StringToNumber<float>(iter->second);
			if (iter->first == "flashing_time")
				stSystemConfig.fFlashingTime = Util::StringToNumber<float>(iter->second);
			CCLOG("key: %s, value: %s", iter->first.c_str(), iter->second.c_str());
		}
		CCLOG("-------------");
	}

	// 取出地图和地图刷怪频率信息
	sql = "select o.id, o.map_name, o.need_kill_num, o.resource_path, "
		"f.type, f.monster_min, f.monster_max, f.refresh_interval, f.refresh_num  from t_map o, t_frequency f where o.id = f.map_id order by o.id asc";
	CCLOG("sql:%s", sql.c_str());
	vData.clear();
	Database::query(sql, vData);
	size = vData.size();
	int id = 0;
	for(int i = 0; i < size; i++)
	{
		TMap stMap;
		TFrequency stFrequency;
		int curr_id;
		map<string, string>::iterator iter;
		for(iter = vData[i].begin(); iter != vData[i].end(); iter++) 
		{
			if (iter->first == "id")
				curr_id = Util::StringToNumber<int>(iter->second);
			if (iter->first == "monster_min")
				stFrequency.iMonsterMin = Util::StringToNumber<int>(iter->second);
			if (iter->first == "monster_max")
				stFrequency.iMonsterMax = Util::StringToNumber<int>(iter->second);
			if (iter->first == "refresh_interval")
				stFrequency.iRefreshInterval = Util::StringToNumber<int>(iter->second);
			if (iter->first == "refresh_num")
				stFrequency.iRefreshNum = Util::StringToNumber<int>(iter->second);
			if (iter->first == "type")
				stFrequency.eGameMode = EGameMode(Util::StringToNumber<int>(iter->second));
			if (iter->first == "map_name")
				stMap.sMapName = iter->second;
			if (iter->first == "need_kill_num")
				stMap.iNeedKillNum = Util::StringToNumber<int>(iter->second);
			if (iter->first == "resource_path")
				stMap.sResourcePath = iter->second;
			CCLOG("key: %s, value: %s", iter->first.c_str(), iter->second.c_str());
		}
		if (curr_id > id)
		{
			stMap.vFrequency.push_back(stFrequency);
			vMapConfig.push_back(stMap);
			id++;
			continue;
		} else 
		{
			vMapConfig[curr_id - 1].vFrequency.push_back(stFrequency);
		}
		//CCLOG("%s, %s, %d, %d", stMap.sMapName.c_str(), stMap.sResourcePath.c_str(), stMap.iNeedKillNum, vMapConfig[curr_id - 1].vFrequency.size());
		CCLOG("-------------");
	}

	// 取出英雄及其技能信息
	sql = "select o.hero_name, o.move_speed, o.hp, o.resource_path, o.attack_range, "
		"s.skill_name, s.damage, s.skill_cd, s.resource_path as skill_rc_path "
		"from t_hero o, t_skill s where o.skill_id = s.id order by o.id asc";
	CCLOG("sql:%s", sql.c_str());
	vData.clear();
	Database::query(sql, vData);
	size = vData.size();
	for(int i = 0; i < size; i++)
	{
		THero stHero;
		map<string, string>::iterator iter;
		for(iter = vData[i].begin(); iter != vData[i].end(); iter++) 
		{
			// 英雄部分
			if (iter->first == "attack_range")
				stHero.fAttackRange = Util::StringToNumber<float>(iter->second);
			if (iter->first == "hp")
				stHero.iHP = Util::StringToNumber<int>(iter->second);
			if (iter->first == "move_speed")
				stHero.fMoveSpeed = Util::StringToNumber<float>(iter->second);
			if (iter->first == "hero_name")
				stHero.sHeroName = iter->second;
			if (iter->first == "resource_path")
				Util::convertString2ResourceStruct(iter->second, stHero.stResource);

			// 技能部分
			if (iter->first == "damage")
				stHero.stSkill.iDamage = Util::StringToNumber<int>(iter->second);
			if (iter->first == "skill_cd")
				stHero.stSkill.iSkillCD = Util::StringToNumber<int>(iter->second);
			if (iter->first == "skill_name")
				stHero.stSkill.sSkillName = iter->second;
			if (iter->first == "skill_rc_path")
				Util::convertString2ResourceStruct(iter->second, stHero.stSkill.stResource);
			CCLOG("key: %s, value: %s", iter->first.c_str(), iter->second.c_str());
		}
		vHeroConfig.push_back(stHero);
		CCLOG("-------------");
	}

	// 取出物品信息
	sql = "select item_name, duration, exist_time, describe, resource_path, value, item_type from t_item order by id asc";
	CCLOG("sql:%s", sql.c_str());
	vData.clear();
	Database::query(sql, vData);
	size = vData.size();
	for(int i = 0; i < size; i++)
	{
		TItem stItem;
		map<string, string>::iterator iter;
		for(iter = vData[i].begin(); iter != vData[i].end(); iter++) 
		{
			if (iter->first == "item_name")
				stItem.sItemName = iter->second;
			if (iter->first == "duration")
				stItem.iDuration = Util::StringToNumber<int>(iter->second);
			if (iter->first == "exist_time")
				stItem.iExistTime = Util::StringToNumber<int>(iter->second);
			if (iter->first == "describe")
				stItem.sDescribe = iter->second;
			if (iter->first == "resource_path")
				Util::convertString2ResourceStruct(iter->second, stItem.stResource);
			if (iter->first == "value")
				stItem.iValue = Util::StringToNumber<int>(iter->second);
			if (iter->first == "item_type")
				stItem.eType = (EItemType)(Util::StringToNumber<int>(iter->second));
			CCLOG("key: %s, value: %s", iter->first.c_str(), iter->second.c_str());
		}
		vItemConfig.push_back(stItem);
		CCLOG("-------------");
	}

	// 取出怪物属性,技能信息
	sql = "select o.monster_name, o.move_speed, o.hp, o.resource_path, o.attack_range, "
		"s.skill_name, s.damage, s.skill_cd, s.resource_path as skill_rc_path "
		"from t_monster o, t_skill s where o.skill_id = s.id order by o.id asc";
	CCLOG("sql:%s", sql.c_str());
	vData.clear();
	Database::query(sql, vData);
	size = vData.size();
	for(int i = 0; i < size; i++)
	{
		TMonster stMonster;
		map<string, string>::iterator iter;
		for(iter = vData[i].begin(); iter != vData[i].end(); iter++) 
		{
			// 怪物部分
			if (iter->first == "attack_range")
				stMonster.fAttackRange = Util::StringToNumber<float>(iter->second);
			if (iter->first == "hp")
				stMonster.iHP = Util::StringToNumber<int>(iter->second);
			if (iter->first == "move_speed")
				stMonster.fMoveSpeed = Util::StringToNumber<float>(iter->second);
			if (iter->first == "monster_name")
				stMonster.sMonsterName = iter->second;
			if (iter->first == "resource_path")
				Util::convertString2ResourceStruct(iter->second, stMonster.stResource);

			// 技能部分
			if (iter->first == "damage")
				stMonster.stSkill.iDamage = Util::StringToNumber<int>(iter->second);
			if (iter->first == "skill_cd")
				stMonster.stSkill.iSkillCD = Util::StringToNumber<int>(iter->second);
			if (iter->first == "skill_name")
				stMonster.stSkill.sSkillName = iter->second;
			if (iter->first == "skill_rc_path")
				Util::convertString2ResourceStruct(iter->second, stMonster.stSkill.stResource);
			CCLOG("key: %s, value: %s", iter->first.c_str(), iter->second.c_str());
		}
		vMonsterConfig.push_back(stMonster);
		CCLOG("-------------");
	}

	// 取出怪物奖励信息
	sql = "select monster_id, item_id, weight from t_reward";
	CCLOG("sql:%s", sql.c_str());
	vData.clear();
	Database::query(sql, vData);
	size = vData.size();
	for(int i = 0; i < size; i++)
	{
		TReward stReward;
		map<string, string>::iterator iter;
		int monsterId, itemId;
		for(iter = vData[i].begin(); iter != vData[i].end(); iter++) 
		{
			if (iter->first == "monster_id")
				monsterId = Util::StringToNumber<int>(iter->second);
			if (iter->first == "weight")
				stReward.iWeight = Util::StringToNumber<int>(iter->second);
			if (iter->first == "item_id")
			{
				itemId = Util::StringToNumber<int>(iter->second);
				if (itemId > 0)
					stReward.stItem = vItemConfig[itemId - 1];
			}
			CCLOG("key: %s, value: %s", iter->first.c_str(), iter->second.c_str());
		}
		if (monsterId > 0)
		{
			vMonsterConfig[monsterId - 1].vReward.push_back(stReward);
		}
		CCLOG("-------------");
	}
	CCLOG("-------------  initData finish  -------------");
}

TConfig GameInfo::getSystemConfig()
{
	return stSystemConfig;
}

vector<TMap> GameInfo::getMapConfig()
{
	return vMapConfig;
}

vector<THero> GameInfo::getHeroConfig()
{
	return vHeroConfig;
}

vector<TMonster> GameInfo::getMonsterConfig()
{
	return vMonsterConfig;
}

vector<TItem> GameInfo::getItemConfig()
{
	return vItemConfig;
}

GameInfo::GameInfo()
{
	// 从数据库里面取出数据
	initData();

	Game = NULL;
	Me = NULL;


	// 英雄
	PathOfHero = "spirit/hero/Hero1_D_1.png";
	RangeToPickupHero = 80.f;
	HeroInitSpeed = 1.5f;
	HeroMaxSpeed = 2.0f;

	// 怪
	PathOfMonster = "spirit/monster/m1.png";
	MonsterInitSpeed = 1.0f;
	MonsterMaxSpeed = 2.0f;

	// 地图
	MapN = M_N;
	MapM = M_M;
	GridSize = 40.f;

	// 其他
	ValidDraggedLength = 10.f;

}