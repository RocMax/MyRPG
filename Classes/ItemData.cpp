//
//  ItemData.cpp
//  MyRPG
//
//  Created by RocLee on 14-9-4.
//
//

#include "ItemData.h"
#include "DBOperations.h"



ItemData* ItemData::getItemData(int ItemID){
    ItemData* item=new ItemData();
    item->setItemID(ItemID);
//    item->autorelease();
    //读入对应ItemID的数据
    char* errorMsg;
    //读取数据库
    sqlite3* pDB=DBOperation::openDB();
    CCString* sqlcs=CCString::createWithFormat("select * from Item where ID=%d",ItemID);
    const char* sql=sqlcs->getCString();
    CCLOG(sql);
    int result=sqlite3_exec(pDB, sql, sqlite_callback,item,&errorMsg);
    if (result!=SQLITE_OK) {
        CCLOG(errorMsg);
    }
    
    sqlite3_close(pDB);
    
    CCLOG("itemname:%s",item->getItemName());
    CCLOG("item retaincount:%d",item->retainCount());


    return item;
    
}

int ItemData::sqlite_callback(void *pv, int column, char **dbResult, char **col){
    ItemData* pitem=(ItemData*)pv;
    
    pitem->setItemName(strdup(dbResult[1]));
    pitem->setItemPic(strdup(dbResult[2]));
    pitem->setItemPrice(atoi(dbResult[3]));
    pitem->setEquipType(atoi(dbResult[4]));
    pitem->setisunique((bool)atoi(dbResult[5]));
    pitem->setItemHP(atof(dbResult[6]));
    pitem->setItemATK(atof(dbResult[7]));
    pitem->setItemDEF(atof(dbResult[8]));
    pitem->setItemAGI(atof(dbResult[9]));
    pitem->setItemLUK(atof(dbResult[10]));
    pitem->setWeaponATKRate(atof(dbResult[11]));
    pitem->setHPAbsorb(atof(dbResult[12]));
    pitem->setCriRate(atof(dbResult[13]));
    pitem->setCriDam(atof(dbResult[14]));
    pitem->setComboRate(atof(dbResult[15]));
    pitem->setEncounterRate(atof(dbResult[16]));
    pitem->setSpeedRate(atof(dbResult[17]));
    pitem->setLUKAddition(atof(dbResult[18]));
    pitem->setItemDropAddition(atof(dbResult[19]));
    pitem->setGoldDropAddition(atof(dbResult[20]));
    pitem->setExpRate(atof(dbResult[21]));
    pitem->setIntroduction(strdup(dbResult[22]));

    
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