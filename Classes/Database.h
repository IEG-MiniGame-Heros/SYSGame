#ifndef SYS_DATABASE
#define SYS_DATABASE

#include <string>
#include <map>
#include "Util.h"
#include "cocos2d.h"
#include "sqlite3.h"


using namespace std;
using namespace cocos2d;

class Database
{
public:
	static string getDataBasePath();
	static int updateCoin(int currNum);
};

#endif