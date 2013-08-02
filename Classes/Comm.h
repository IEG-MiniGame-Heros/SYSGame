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


// -------------------------------- �����ṹ --------------------------------
// ��Ʒ�ṹ
struct TItem
{
	string sItemName; // ��Ʒ����
	string sDescribe; // ��Ʒ����
	EItemType eType; // ��Ʒ����
	int iDuration; // ��ƷЧ������ʱ��
	int iExistTime; // ���������ڳ����б�����ʱ��
	int iValue; // ��ֵ
	string sResourcePath; // ��Ʒ��Ӧ��ͼƬ��Դ·��(�ж���ļ��Ļ�,��;�ָ�)
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
	string sResourcePath; // ���ܶ�Ӧ��ͼƬ��Դ·��(�ж���ļ��Ļ�,��;�ָ�)
};

// ����ṹ
struct TMonster
{
	string sMonsterName; // ��������
	int iMoveSpeed; // �ƶ��ٶ�
	int iHP; // ����ֵ
	TSkill stSkill; // ����
	string sResourcePath; // �����Ӧ��ͼƬ��Դ·��(�ж���ļ��Ļ�,��;�ָ�)
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
	string sResourcePath; // ���ܶ�Ӧ��ͼƬ��Դ·��(�ж���ļ��Ļ�,��;�ָ�)
	int iAttackRange; // ������Χ
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