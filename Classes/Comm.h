#ifndef SYS_COMM
#define SYS_COMM

#include <string>
#include <vector>
#include <map>
using namespace std;

// -------------------------------- 常量 --------------------------------


// -------------------------------- 枚举 --------------------------------
// 物品类型枚举
enum EItemType
{
	kMoney = 1, // 金币
	kStageItem = 2, // 场景道具
	kHero = 3 // 英雄
};

// 游戏模式枚举
enum EGameMode
{
	kEndlessMode = 1, // 无尽模式
	kLevelMode = 2 // 过关模式
};

// 特效类型
// 注意，这里跟技能绑定的特效是按照数据库的技能顺序来的！！！
enum EEffectType
{
	EET_FireBall	=	1,	// 火球
	EET_Bullet      =   2,  // 子弹	
	EET_IceBall		=	3,	// 冰球
	EET_SeeStar		=	4,	// 海星
	EET_MonsLight	=	5,	// 小怪攻击
	EET_Explosion	=	6,	// 爆炸
	EET_Frozen		=	7,	// 冰冻
	EET_Flash		=	8,	// 闪光
	EET_Smog		=	9,	// 烟雾
	EET_Twinkle		=	10,	// 星星闪烁
};

// 物品类型
enum EGoodType
{
	EGT_Coin		=	1,	// 金币
	EGT_BloodSupply	=	2,	// 血包
	EGT_IceCube		=	3,	// 冰块
};


// -------------------------------- 公共结构 --------------------------------
// 美术资源结构
struct TResource
{
	string sImagePath; // 图像路径(用于精灵初始化)
	int iFrames; // 帧数
	vector<string> vAnimationPath; // 每帧动画对应的图片资源(用于生成动画)
};

// 物品结构
struct TItem
{
	string sItemName; // 物品名称
	string sDescribe; // 物品描述
	EItemType eType; // 物品类型
	int iDuration; // 物品效果持续时间
	int iExistTime; // 场景道具在场景中保留的时间
	int iValue; // 价值
	TResource stResource; // 对应的图片资源
};

// 怪物奖励结构
struct TReward
{
	TItem stItem; // 掉落的物品
	int iWeight; // 掉落物品的权重
};

// 技能结构
struct TSkill
{
	string sSkillName; // 技能名称
	int iDamage; // 技能上海
	int iSkillCD; // 技能CD
	TResource stResource; // 对应的图片资源
	float fSpeed; // 技能速度
	float fAttackRange; // 攻击范围
};

// 怪物结构
struct TMonster
{
	string sMonsterName; // 怪物名称
	float fMoveSpeed; // 移动速度
	int iHP; // 生命值
	TSkill stSkill; // 技能
	TResource stResource; // 对应的图片资源
	vector<TReward> vReward; // 奖励列表
	float fAttackRange; // 攻击范围
	int iSkillID;		// 对应的技能ID
};

// 英雄结构
struct THero
{
	string sHeroName; // 英雄名称
	float fMoveSpeed; // 移动速度
	int iHP; // 生命值
	TSkill stSkill; // 技能
	float fAttackRange; // 攻击范围
	TResource stResource; // 对应的图片资源
	int iSkillID;		// 对应的技能ID
};

// 刷怪频率结构
struct TFrequency
{
	EGameMode eGameMode; // 游戏模式
	int iMonsterMin; // 击杀怪物条件的下限
	int iMonsterMax; // 击杀怪物条件的上限
	float iRefreshInterval; // 刷新时间间隔(单位:s)
	int iRefreshNum; // 刷新时间间隔内刷怪的数量
};

// 地图结构
struct TMap
{
	string sMapName; // 地图名称
	int iNeedKillNum; // 闯关模式通关需要杀怪的数量
	string sResourcePath; // 对应的地图资源路径
	vector<TFrequency> vFrequency; // 地图刷怪
};

// 配置结构
struct TConfig
{
	int iMapSize; // 地图单行(列)的个数
	float fMaxMoveSpeed; // 最大移动速度
	float fSpeedIncrement; // 每增加一个英雄,要增加的速度
	int iLifeNum; // 闯关模式时的生命数
	int iRebornCost; // 闯关模式重生消耗的金币数
	float fTimeCoefficient; // 时间得分系数
	float fCoinCoefficient; // 金币得分系数
	float fMonsterCoefficient; // 怪物得分系数
	float fExistTime;	// 英雄或者物品存在的时间（不计闪烁）
	float fFlashingTime; // 英雄或物品消失前的闪烁时间
	float fFrozenTime; // 冰冻时间
	float fHitRange; // 命中判断范围
	float fSkillSlideLen; // 技能在屏幕飞行长度（未攻击到怪情况下）
	float fPickupRange;// 拾取的范围
	float fAppearHeroTime; // 强制出现英雄的时间
};

// 用户结构
struct TUser
{
	int iMoney; // 用户拥有的金币数
	int iKillNum; // 用户杀怪的数量
	int iScore; // 最高分
	int iTime; // 持续时间
};



#endif