//
//  ItemData.cpp
//  MyRPG
//
//  Created by RocLee on 14-8-18.
//
//

#include "ItemData.h"
#include "DBOperations.h"

static ItemData* item_instance=NULL;

ItemData* ItemData::getItemData(int ItemID){
    if (!item_instance) {
        item_instance=new ItemData();
    }
    
    //读入对应ItemID的数据
    char* errorMsg;
    //读取数据库
    sqlite3* pDB=DBOperation::openDB();
    CCString* sqlcs=CCString::createWithFormat("select * from Item where ID=%d",ItemID);
    const char* sql=sqlcs->getCString();
    CCLog(sql);
    int result=sqlite3_exec(pDB, sql, sqlite_callback, NULL, &errorMsg);
    if (result!=SQLITE_OK) {
        CCLog(errorMsg);
    }
    
    sqlite3_close(pDB);
    
    return item_instance;

    
}

int ItemData::sqlite_callback(void *pv, int column, char **dbResult, char **col){
    item_instance->setItemName(dbResult[1]);
    item_instance->setItemPic(dbResult[2]);
    item_instance->setItemPrice(atoi(dbResult[3]));
    item_instance->setEquipType(atoi(dbResult[4]));
    item_instance->setisunique((bool)atoi(dbResult[5]));
    item_instance->setItemHP(atof(dbResult[6]));
    item_instance->setItemATK(atof(dbResult[7]));
    item_instance->setItemDEF(atof(dbResult[8]));
    item_instance->setItemAGI(atof(dbResult[9]));
    item_instance->setItemLUK(atof(dbResult[10]));
    item_instance->setWeaponATKRate(atof(dbResult[11]));
    item_instance->setHPAbsorb(atof(dbResult[12]));
    item_instance->setCriRate(atof(dbResult[13]));
    item_instance->setCriDam(atof(dbResult[14]));
    item_instance->setComboRate(atof(dbResult[15]));
    item_instance->setEncounterRate(atof(dbResult[16]));
    item_instance->setSpeedRate(atof(dbResult[17]));
    item_instance->setLUKAddition(atof(dbResult[18]));
    item_instance->setItemDropAddition(atof(dbResult[19]));
    item_instance->setGoldDropAddition(atof(dbResult[20]));
    
    return 0;
}

ItemData::pGet ItemData::getgetFounc(ItemData::enumStatu statuID){
    pGet p;
    switch (statuID) {
        case eItemHP:
            p=&ItemData::getItemHP;
            break;
        case eItemATK:
            p=&ItemData::getItemATK;
            break;
        case eItemDEF:
            p=&ItemData::getItemDEF;
            break;
        case eItemAGI:
            p=&ItemData::getItemAGI;
            break;
        case eItemLUK:
            p=&ItemData::getItemLUK;
            break;
        case eWeaponATKRate:
            p=&ItemData::getWeaponATKRate;
            break;
        case eHPAbsorb:
            p=&ItemData::getHPAbsorb;
            break;
        case eCriRate:
            p=&ItemData::getCriRate;
            break;
        case eCriDam:
            p=&ItemData::getCriDam;
            break;
        case eComboRate:
            p=&ItemData::getComboRate;
            break;
        case eEncounterRate:
            p=&ItemData::getEncounterRate;
            break;
        case eSpeedRate:
            p=&ItemData::getSpeedRate;
            break;
        case eLUKAddition:
            p=&ItemData::getLUKAddition;
            break;
        case eItemDropAddition:
            p=&ItemData::getItemDropAddition;
            break;
        case eGoldDropAddition:
            p=&ItemData::getGoldDropAddition;
            break;
        case eExpRate:
            p=&ItemData::getExpRate;
            break;
        default:
            p=0;
            break;
    }
    return p;
}
