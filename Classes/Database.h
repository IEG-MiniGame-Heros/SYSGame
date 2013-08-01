#ifndef SYS_DATABASE
#define SYS_DATABASE

#include <string>
#include <map>
#include "Comm.h"
#include "Util.h"
#include "cocos2d.h"
#include "sqlite3.h"


using namespace std;
using namespace cocos2d;

class Database
{
public:
	static string getDataBasePath();
	static int callback(void *data, int argc, char **argv, char **azColName);
	static int query(string sql, vector<map<string, string> > &vData);
	static int updateCoin(int currNum);
};

#endif