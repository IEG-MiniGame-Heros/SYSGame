#ifndef SYS_UTIL
#define SYS_UTIL

#include "Comm.h"
#include <string>
#include <sstream>
using namespace std;

#define N2S(num) (Util::NumberToString(num))
#define N2C(num) (Util::NumberToString(num).c_str())
#define S2I(s) (Util::StringToNumber<int>(s))

class Util
{
public:
	// usage:NumberToString ( Number )
	template <typename T>
	static string NumberToString ( T Number )
	{
		ostringstream ss;
		ss << Number;
		return ss.str();
	}

	// usage:StringToNumber<Type> ( String )
	template <typename T>
	static T StringToNumber ( const string &Text )
	{
		istringstream ss(Text);
		T result;
		return ss >> result ? result : 0;
	}

	//�ַ����ָ�
	static vector<string> split(string str, string pattern)
	{
		int pos;
		vector<string> result;
		str += pattern;
		int size = str.size();
		for(int i = 0; i < size; i++)
		{
			pos = str.find(pattern, i);
			if(pos < size)
			{
				string s = str.substr(i, pos - i);
				result.push_back(s);
				i = pos+pattern.size() - 1;
			}
		}
		return result;
	}

	// ���ַ���ת��Ϊ��Դ�ṹ(�����ж�stResource.iFrames��֪ת���Ƿ�ɹ�)
	static void convertString2ResourceStruct(string path, TResource &stResource)
	{
		stResource.iFrames = -1;
		// ��|��ȡ
		vector<string> vPath = Util::split(path, "|");
		int size = vPath.size();
		do 
		{
			stResource.sImagePath = vPath[0];
			// ֻ��һ���ֵĻ�������֡��Ϊ0,����
			if (size == 1)
			{
				stResource.iFrames = 0;
				break;
			}
			// ��Ϊ�����ֵĻ����ж�֡���Ƿ����0,���Ķ�����Դ�Ƿ�Ϊ֡���ı���
			else if (size == 3)
			{
				int iFrames = StringToNumber<int>(vPath[1]);
				if (iFrames <= 0)
					break;
				vector<string> vAnimations = Util::split(vPath[2], ";");
				if (vAnimations.size() % iFrames != 0)
					break;
				stResource.vAnimationPath = vAnimations;
				stResource.iFrames = iFrames;
			}
		} while (0);
		return ;
	}
};

#endif