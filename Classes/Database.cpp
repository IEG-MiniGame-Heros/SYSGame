#include "Database.h"

string Database::getDataBasePath()
{
	string path;
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		path = "database.db";
		CCLOG("database in windows");
	#else
		path = CCFileUtils::sharedFileUtils()->getWritablePath() + "database.db";
		CCLOG("database in other platform");
	#endif
	return path;
}

int Database::updateCoin(int currNum)
{
	int result = SQLITE_ERROR;

	string dbPath = getDataBasePath();
	CCLOG("database path : %s", dbPath.c_str());
	sqlite3 *pDB = NULL;
	char * errMsg = NULL;
	string sqlstr;
	do 
	{
		result = sqlite3_open(dbPath.c_str(), &pDB); 
		if( result != SQLITE_OK )
		{
			CCLOG("open database fail");
			break;
		}
		CCLOG("open database succ");
		sqlstr = "update t_user set money = " + Util::NumberToString(currNum) + " where id = 1";
		result = sqlite3_exec(pDB, sqlstr.c_str(), NULL, NULL, &errMsg); 
		if( result != SQLITE_OK )
			break;
	} while (0);
	
	return result;
}