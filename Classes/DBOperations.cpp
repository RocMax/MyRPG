//
//  DBOperations.cpp
//  MyRPG
//
//  Created by RocLee on 14-6-29.
//
//

#include "DBOperations.h"
using namespace std;


sqlite3* DBOperation::openDB(){
    sqlite3* pDB=NULL;
    int result;
    string path=CCFileUtils::sharedFileUtils()->fullPathForFilename(DB_FILENAME);
    result=sqlite3_open(path.c_str(), &pDB);
    if (result!=SQLITE_OK) {
        CCLOG("open sql file failed");
        return NULL;
    }
    return pDB;
}

