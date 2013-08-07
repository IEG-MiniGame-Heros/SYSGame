#ifndef SYS_UTIL
#define SYS_UTIL

#include "Comm.h"
#include <string>
#include <sstream>
using namespace std;

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

	//字符串分割
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

	// 将字符串转换为资源结构(根据判断stResource.iFrames可知转换是否成功)
	static void convertString2ResourceStruct(string path, TResource &stResource)
	{
		stResource.iFrames = -1;
		// 按|截取
		vector<string> vPath = Util::split(path, "|");
		int size = vPath.size();
		do 
		{
			stResource.sImagePath = vPath[0];
			// 只有一部分的话就设置帧数为0,返回
			if (size == 1)
			{
				stResource.iFrames = 0;
				break;
			}
			// 分为三部分的话就判断帧数是否大于0,最后的动画资源是否为帧数的倍数
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