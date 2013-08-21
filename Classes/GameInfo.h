#ifndef SYS_GAMEINFO
#define SYS_GAMEINFO

#include "cocos2d.h"
#include "Comm.h"
#include "Util.h"
#include "Database.h"

#include <string>

USING_NS_CC;

#define GI (GameInfo::instance())

class Character;
class MainGame;
class Queue;
class GameHelper;

const int M_N = 20;
const int M_M = 20;

/** Ӣ��������� */
const int MAX_HERO_KINDS = 4;
const int MAX_MONSTER_KINDS = 3;

/** 
 * @brief ����ȫ����Ϣ�ĵ���
 */
class GameInfo
{
public:	
	static GameInfo& instance();

	GameInfo();


public:

	MainGame*			Game;						// ָ��ǰ��ϷLayer��ָ��
	Queue*				Me;							// ָ����ҵ�ָ��

	// Ӣ��
	std::string			PathOfHero;					// Ӣ�۵�ͼƬ·��	
	float				RangeToPickupHero;			// ���ԡ�Ӣ�۵���Ч��Χ
	float				HeroInitSpeed;				// Ӣ�۳�ʼ�ٶ�
	float				HeroMaxSpeed;				// Ӣ������ٶ�

	// ��
	std::string			PathOfMonster;				// �ֵ�ͼƬ·��
	float				MonsterInitSpeed;			// �ֵĳ�ʼ�ٶ�
	float				MonsterMaxSpeed;			// �ֵ�����ٶ�

	// ����
	CCLayer*			currentLayer;				// ÿһ�ص��л���Ҫ������������и�ֵ���Ը���Ӣ���ƶ�
													// �����ƶ��Ĵ�����FirstStage��update������
	bool				IsGameOver;					// �Ƿ���Ϸ����

	// ��ͼ���
	CCTMXTiledMap*		Map;						// ��ͼ������
    CCTMXLayer*			Meta;						// �����ײ�ĵ�ͼ�� 
    CCTMXLayer*			Barrier;					// �ϰ����

	int					MapN;						//
	int					MapM;						// N��M�еĵ�ͼ
	float				MapWidth;					// ��ͼ���
	float				MapHeight;					// ��ͼ�߶�
	int					GridSize;					// ��ͼÿһС��Ĵ�С

	// ����
	float				ValidDraggedLength;			// ��Ч�Ļ������룬�ڴ˻����ϲŽ��л����ж�
	GameHelper*			Helper;						// ��Ϸ������

	// ����
	int					musicVolume;				// ������������
	int					soundVolume;				// ��Ч��������

	// ��ң��÷֣�ɱ����
	int					Coin;						// ���
	float				Score;						// �÷�
	int					MonsterKillNum;				// ɱ����
	float				ChallengeTime;				// ����սʱ��

public:
	void initData();
	TConfig getSystemConfig();
	vector<TMap> getMapConfig();
	vector<THero> getHeroConfig();
	vector<TMonster> getMonsterConfig();
	vector<TItem> getItemConfig();
	vector<TSkill> getSkillConfig();
	vector<TReward> getRewardConfig();

private:
	TConfig stSystemConfig; // ϵͳ����
	vector<TMap> vMapConfig; // ��ͼ�����б�
	vector<THero> vHeroConfig; // Ӣ�������б�
	vector<TMonster> vMonsterConfig; // ���������б�
	vector<TItem> vItemConfig; // ��Ʒ�����б�
	vector<TSkill> vSkillConfig; // ���������б�
	vector<TReward> vRewardConfig;	// ���������б�
};

#endif