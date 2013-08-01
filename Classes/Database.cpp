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

int Database::callback(void *data, int argc, char **argv, char **azColName)
{
	vector<map<string, string> > *pData = (vector<map<string, string> > *)data;
	string key, value;
	map<string, string> m;
	for(int i = 0; i < argc; i++)
	{
		key = azColName[i];
		value = argv[i];
		m.insert(map<string, string>::value_type(key, value));
		//CCLOG("%s, %s", key.c_str(), value.c_str());
	}
	pData->push_back(m);
	return 0;
}

int Database::query(string sql, vector<map<string, string> > &vData)
{
	int result = SQLITE_ERROR;
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;

	do 
	{
		/* Open database */
		rc = sqlite3_open("database.db", &db);
		if( rc ){
			CCLOG("Can't open database: %s", sqlite3_errmsg(db));
			break;
		}else{
			CCLOG("Opened database successfully");
		}

		/* Execute SQL statement */
		 vector<map<string, string> > *pData = &vData;
		rc = sqlite3_exec(db, sql.c_str(), callback, (void*)pData, &zErrMsg);
		if( rc != SQLITE_OK ){
			CCLOG("SQL error: %s", zErrMsg);
			sqlite3_free(zErrMsg);
			break;
		}else{
			CCLOG("Operation done successfully");
		}
#if 0
		CCLOG("--------- %s ---------", sql.c_str());
		int size = vData.size();
		for(int i = 0; i < size; i++)
		{
			map<string, string>::iterator iter;
			for(iter = vData[i].begin(); iter != vData[i].end(); iter++) 
			{
				CCLOG("key: %s, value: %s", iter->first.c_str(), iter->second.c_str());
			}
			CCLOG("----------------");
		}
		CCLOG("--------- end ---------");
#endif
		result = SQLITE_OK;
	} while (0);

	sqlite3_close(db);
	return result;
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