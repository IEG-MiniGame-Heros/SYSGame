#ifndef SYS_COMM
#define SYS_COMM

#include <string>
#include <vector>
#include <map>
using namespace std;

// -------------------------------- ���� --------------------------------


// -------------------------------- ö�� --------------------------------
// ��Ʒ����ö��
enum EItemType
{
	kMoney = 1, // ���
	kStageItem = 2, // ��������
	kHero = 3 // Ӣ��
};

// ��Ϸģʽö��
enum EGameMode
{
	kEndlessMode = 1, // �޾�ģʽ
	kLevelMode = 2 // ����ģʽ
};

// ��Ч����
// ע�⣬��������ܰ󶨵���Ч�ǰ������ݿ�ļ���˳�����ģ�����
enum EEffectType
{
	EET_FireBall	=	1,	// ����
	EET_Bullet      =   2,  // �ӵ�	
	EET_IceBall		=	3,	// ����
	EET_SeeStar		=	4,	// ����
	EET_MonsLight	=	5,	// С�ֹ���
	EET_Arrow		=	6,	// ��
	EET_EnergyBall	=	7,	// ������
	EET_Explosion	=	8,	// ��ը
	EET_Frozen		=	9,	// ����
	EET_Flash		=	10,	// ����
	EET_Smog		=	11,	// ����
	EET_Twinkle		=	12,	// ������˸
	EET_ShowNum		=	13,	// ��ʾ����
};

// ��Ʒ����
enum EGoodType
{
	EGT_Coin		=	1,	// ���
	EGT_BloodSupply	=	2,	// Ѫ��
	EGT_IceCube		=	3,	// ����
};


// -------------------------------- �����ṹ --------------------------------
// ������Դ�ṹ
struct TResource
{
	string sImagePath; // ͼ��·��(���ھ����ʼ��)
	int iFrames; // ֡��
	vector<string> vAnimationPath; // ÿ֡������Ӧ��ͼƬ��Դ(�������ɶ���)
};

// ��Ʒ�ṹ
struct TItem
{
	string sItemName; // ��Ʒ����
	string sDescribe; // ��Ʒ����
	EItemType eType; // ��Ʒ����
	int iDuration; // ��ƷЧ������ʱ��
	int iExistTime; // ���������ڳ����б�����ʱ��
	int iValue; // ��ֵ
	TResource stResource; // ��Ӧ��ͼƬ��Դ
};

// ���ｱ���ṹ
struct TReward
{
	TItem stItem; // �������Ʒ
	int iWeight; // ������Ʒ��Ȩ��
};

// ���ܽṹ
struct TSkill
{
	string sSkillName; // ��������
	int iDamage; // �����Ϻ�
	int iSkillCD; // ����CD
	TResource stResource; // ��Ӧ��ͼƬ��Դ
	float fSpeed; // �����ٶ�
	float fAttackRange; // ������Χ
};

// ����ṹ
struct TMonster
{
	string sMonsterName; // ��������
	float fMoveSpeed; // �ƶ��ٶ�
	int iHP; // ����ֵ
	TSkill stSkill; // ����
	TResource stResource; // ��Ӧ��ͼƬ��Դ
	vector<TReward> vReward; // �����б�
	float fAttackRange; // ������Χ
	int iSkillID;		// ��Ӧ�ļ���ID
};

// Ӣ�۽ṹ
struct THero
{
	string sHeroName; // Ӣ������
	float fMoveSpeed; // �ƶ��ٶ�
	int iHP; // ����ֵ
	TSkill stSkill; // ����
	float fAttackRange; // ������Χ
	TResource stResource; // ��Ӧ��ͼƬ��Դ
	int iSkillID;		// ��Ӧ�ļ���ID
};

// ˢ��Ƶ�ʽṹ
struct TFrequency
{
	EGameMode eGameMode; // ��Ϸģʽ
	int iMonsterMin; // ��ɱ��������������
	int iMonsterMax; // ��ɱ��������������
	float iRefreshInterval; // ˢ��ʱ����(��λ:s)
	int iRefreshNum; // ˢ��ʱ������ˢ�ֵ�����
};

// ��ͼ�ṹ
struct TMap
{
	string sMapName; // ��ͼ����
	int iNeedKillNum; // ����ģʽͨ����Ҫɱ�ֵ�����
	string sResourcePath; // ��Ӧ�ĵ�ͼ��Դ·��
	vector<TFrequency> vFrequency; // ��ͼˢ��
};

// ���ýṹ
struct TConfig
{
	int iMapSize; // ��ͼ����(��)�ĸ���
	float fMaxMoveSpeed; // ����ƶ��ٶ�
	float fSpeedIncrement; // ÿ����һ��Ӣ��,Ҫ���ӵ��ٶ�
	int iLifeNum; // ����ģʽʱ��������
	int iRebornCost; // ����ģʽ�������ĵĽ����
	float fTimeCoefficient; // ʱ��÷�ϵ��
	float fCoinCoefficient; // ��ҵ÷�ϵ��
	float fMonsterCoefficient; // ����÷�ϵ��
	float fExistTime;	// Ӣ�ۻ�����Ʒ���ڵ�ʱ�䣨������˸��
	float fFlashingTime; // Ӣ�ۻ���Ʒ��ʧǰ����˸ʱ��
	float fFrozenTime; // ����ʱ��
	float fHitRange; // �����жϷ�Χ
	float fSkillSlideLen; // ��������Ļ���г��ȣ�δ������������£�
	float fPickupRange;// ʰȡ�ķ�Χ
	float fAppearHeroTime; // ǿ�Ƴ���Ӣ�۵�ʱ��
};

// �û��ṹ
struct TUser
{
	int iMoney; // �û�ӵ�еĽ����
	int iKillNum; // �û�ɱ�ֵ�����
	int iScore; // ��߷�
	int iTime; // ����ʱ��
};



#endif