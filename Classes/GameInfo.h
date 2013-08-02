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

const int M_N = 20;
const int M_M = 20;

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


	// ��ͼ���
	int					MapN;						//
	int					MapM;						// N��M�еĵ�ͼ
	int					MapWidth;					// ��ͼ���
	int					MapHeight;					// ��ͼ�߶�
	int					GridSize;					// ��ͼÿһС��Ĵ�С

	// ����
	float				ValidDraggedLength;			// ��Ч�Ļ������룬�ڴ˻����ϲŽ��л����ж�

public:
	void initData();
	TConfig getSystemConfig();
	vector<TMap> getMapConfig();
	vector<THero> getHeroConfig();
	vector<TMonster> getMonsterConfig();
	vector<TItem> getItemConfig();

private:
	TConfig stSystemConfig; // ϵͳ����
	vector<TMap> vMapConfig; // ��ͼ�����б�
	vector<THero> vHeroConfig; // Ӣ�������б�
	vector<TMonster> vMonsterConfig; // ���������б�
	vector<TItem> vItemConfig; // ��Ʒ�����б�
};

#endif