#ifndef SYS_UTIL
#define SYS_UTIL

#include <string>
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
};

#endif