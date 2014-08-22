//
//  ItemData.cpp
//  MyRPG
//
//  Created by RocLee on 14-8-18.
//
//

#include "ItemData.h"
#include "DBOperations.h"

ItemData* instance=NULL;

ItemData* ItemData::getItemData(int ItemID){
    if (!instance) {
        instance=new ItemData();
    }
    
    //读入对应ItemID的数据
    char* errorMsg;
    //读取数据库
    sqlite3* pDB=DBOperation::openDB();
    CCString* sqlcs=CCString::createWithFormat("select * from Item where ItemID=%d",ItemID);
    const char* sql=sqlcs->getCString();
    CCLog(sql);
    int result=sqlite3_exec(pDB, sql, sqlite_callback, NULL, &errorMsg);
    if (result!=SQLITE_OK) {
        CCLog(errorMsg);
    }
    
    sqlite3_close(pDB);
    
    return instance;

    
}

int ItemData::sqlite_callback(void *pv, int column, char **dbResult, char **col){
    instance->setItemName(dbResult[1]);
    instance->setItemPic(dbResult[2]);
    instance->setItemPrice(atoi(dbResult[3]));
    instance->setEquipType(atoi(dbResult[4]));
    instance->setisunique((bool)atoi(dbResult[5]));
    instance->setItemHP(atof(dbResult[6]));
    instance->setItemATK(atof(dbResult[7]));
    instance->setItemDEF(atof(dbResult[8]));
    instance->setItemAGI(atof(dbResult[9]));
    instance->setItemLUK(atof(dbResult[10]));
    instance->setHPAbsorb(atof(dbResult[11]));
    instance->setExpRate(atof(dbResult[12]));
    instance->setCriRate(atof(dbResult[13]));
    instance->setCriDam(atof(dbResult[14]));
    instance->setComboRate(atof(dbResult[15]));
    instance->setEncounterRate(atof(dbResult[16]));
    instance->setSpeedRate(atof(dbResult[17]));
    instance->setItemDropRate(atof(dbResult[18]));
    instance->setGoldDropRate(atof(dbResult[19]));
    
    return 0;
}
