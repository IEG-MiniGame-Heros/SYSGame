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
	kOthers = 3 // ����
};

// ��Ϸģʽö��
enum EGameMode
{
	kEndlessMode = 1, // �޾�ģʽ
	kLevelMode = 2 // ����ģʽ
};

// ��Ч����
enum EEffectType
{
	EET_FireBall	=	1,	// ����
};

// ��Ʒ����
enum EGoodType
{
	EGT_Coin		=	1,	// ���
	EGT_BloodSupply	=	2,	// Ѫ��
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
};

// ����ṹ
struct TMonster
{
	string sMonsterName; // ��������
	int iMoveSpeed; // �ƶ��ٶ�
	int iHP; // ����ֵ
	TSkill stSkill; // ����
	TResource stResource; // ��Ӧ��ͼƬ��Դ
	vector<TReward> vReward; // �����б�
	int iAttackRange; // ������Χ
};

// Ӣ�۽ṹ
struct THero
{
	string sHeroName; // Ӣ������
	int iMoveSpeed; // �ƶ��ٶ�
	int iHP; // ����ֵ
	TSkill stSkill; // ����
	int iAttackRange; // ������Χ
	TResource stResource; // ��Ӧ��ͼƬ��Դ
};

// ˢ��Ƶ�ʽṹ
struct TFrequency
{
	EGameMode eGameMode; // ��Ϸģʽ
	int iMonsterMin; // ��ɱ��������������
	int iMonsterMax; // ��ɱ��������������
	int iRefreshInterval; // ˢ��ʱ����(��λ:s)
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
	int iMaxMoveSpeed; // ����ƶ��ٶ�
	int iSpeedIncrement; // ÿ����һ��Ӣ��,Ҫ���ӵ��ٶ�
	int iLifeNum; // ����ģʽʱ��������
	int iRebornCost; // ����ģʽ�������ĵĽ����
	float fTimeCoefficient; // ʱ��÷�ϵ��
	float fCoinCoefficient; // ��ҵ÷�ϵ��
	float fMonsterCoefficient; // ����÷�ϵ��
};

// �û��ṹ
struct TUser
{
	int iMoney; // �û�ӵ�еĽ����
	int iKillNum; // �û�ɱ�ֵ�����
};



#endif