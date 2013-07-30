#ifndef SYS_DATABASE
#define SYS_DATABASE

#include <string>
#include <map>
#include "cocos2d.h"
#include "sqlite3.h"


using namespace std;
using namespace cocos2d;

class Database
{
public:
	static string getDataBasePath();
	static int update(string tableName, map<string, string> param);
};

#endif