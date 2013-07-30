#include "Database.h"

string Database::getDataBasePath()
{
	string path;
	#if (CC_TARGET_PLATFORM == CC_TARGET_WIN32)
		path = "database.db";
	#else
		path = CCFileUtils::sharedFileUtils()->getWritablePath() + "database.db";
	#endif
	return path;
}

int Database::update(string tableName, map<string, string> param)
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
			break;
		sqlstr = "insert into t_monster (id) values (1)";
		result = sqlite3_exec(pDB, sqlstr.c_str(), NULL, NULL, &errMsg); 
		if( result != SQLITE_OK )
			break;
	} while (0);
	
	return result;
}