#ifndef SYS_UTIL
#define SYS_UTIL

#include "Comm.h"
#include <string>
#include <sstream>
#include "cocos2d.h"

using namespace cocos2d;
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

	static string convertScore2string(int score)
	{
		string s, ss;
		s = N2S(score);
		int size = (int)s.size();
		int count = 0;
		for (int i = size - 1; i >= 0; i--)
		{
			count++;
			char c = s.c_str()[i];
			ss += c;
			if (count == 3 && i != 0)
			{
				ss += ',';
				count = 0;
			}
		}
		//CCLog("string %s", ss.c_str());
		return ss;
	}


	static float convertNumber2Spirit2(CCSprite *parentSpirit, char before_c, char c, int pos, float before_separator_size)
	{
		const char *fileName;
		int final_separator_size;
		int base_separator_size = 45;

		switch(before_c)
		{
		case '0':
			base_separator_size = 42;
			break;
		case '1':
			base_separator_size = 30;
			break;
		case '2':
			base_separator_size = 37;
			break;
		case '3':
			base_separator_size = 37;
			break;
		case '4':
			base_separator_size = 37;
			break;
		case '5':
			base_separator_size = 37;
			break;
		case '6':
			base_separator_size = 37;
			break;
		case '7':
			base_separator_size = 37;
			break;
		case '8':
			base_separator_size = 38;
			break;
		case '9':
			base_separator_size = 37;
			break;
		default:
			base_separator_size = 30;
			break;
		};

		switch(c)
		{
		case '0':
			fileName = "ui/score/0.png";
			break;
		case '1':
			fileName = "ui/score/1.png";
			break;
		case '2':
			fileName = "ui/score/2.png";
			break;
		case '3':
			fileName = "ui/score/3.png";
			break;
		case '4':
			fileName = "ui/score/4.png";
			break;
		case '5':
			fileName = "ui/score/5.png";
			break;
		case '6':
			fileName = "ui/score/6.png";
			break;
		case '7':
			fileName = "ui/score/7.png";
			break;
		case '8':
			fileName = "ui/score/8.png";
			break;
		case '9':
			fileName = "ui/score/9.png";
			break;
		default:
			fileName = "ui/score/sign.png";
			break;
		};
		if (pos == 0)
		{
			parentSpirit->initWithFile(fileName);
			return 0.0f;
		}
		if (pos % 4 == 3 || (pos % 4 == 0 && pos > 0))
		{
			final_separator_size = base_separator_size + 10;
		} else 
		{
			final_separator_size = base_separator_size;
		}

		float size = final_separator_size + before_separator_size;
		CCSprite *child = CCSprite::create();
		child->initWithFile(fileName);
		child->setPosition(ccp(parentSpirit->getContentSize().width/2 + size, parentSpirit->getContentSize().height/2));
		parentSpirit->addChild(child);

		return size;
	}

};

#endif