#ifndef SYS_COMM
#define SYS_COMM

#include <string>
#include <vector>
#include <map>
using namespace std;

// ��Ʒ����ö��
enum EItemType
{
	kMoney, // ���
	kStageItem, // ��������
	kOthers // ����
};

// ��Ϸģʽ����
enum EGameMode
{
	kEndlessMode, // �޾�ģʽ
	kLevelMode // ����ģʽ
};

// ��Ʒ�ṹ
struct TItem
{
	string sItemName; // ��Ʒ����
	string sDescribe; // ��Ʒ����
	EItemType eType; // ��Ʒ����
	int iDuration; // ��ƷЧ������ʱ��
	int iExistTime; // ���������ڳ����б�����ʱ��
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
};

// Ӣ�۽ṹ
struct THero
{
	string sHeroName; // Ӣ������
	int iMoveSpeed; // �ƶ��ٶ�
	int iHP; // ����ֵ
	TSkill stSkill; // ����
	string sResourcePath; // ���ܶ�Ӧ��ͼƬ��Դ·��(�ж���ļ��Ļ�,��;�ָ�)
};

// ˢ��Ƶ�ʽṹ
struct TFrequency
{
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
	map<EGameMode, TFrequency> mFrequency; // ��ͼˢ��,�뵱ǰ����Ϸģʽ���

};


#endif