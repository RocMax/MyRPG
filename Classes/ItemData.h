//
//  ItemData.h
//  MyRPG
//
//  Created by RocLee on 14-8-18.
//
//

#ifndef __MyRPG__ItemData__
#define __MyRPG__ItemData__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class ItemData:public CCObject{
    CC_SYNTHESIZE(int, ItemID, ItemID);
    CC_SYNTHESIZE(char*, ItemName, ItemName);
    CC_SYNTHESIZE(char*, ItemPic, ItemPic)
    CC_SYNTHESIZE(int, ItemPrice, ItemPrice);
    CC_SYNTHESIZE(int, EquipType, EquipType);
    CC_SYNTHESIZE(bool, isUnique, isunique);
    CC_SYNTHESIZE(float, ItemHP, ItemHP);
    CC_SYNTHESIZE(float, ItemATK, ItemATK);
    CC_SYNTHESIZE(float, ItemDEF, ItemDEF);
    CC_SYNTHESIZE(float, ItemAGI, ItemAGI);
    CC_SYNTHESIZE(float, ItemLUK, ItemLUK);
    CC_SYNTHESIZE(float, HPAbsorb, HPAbsorb);
    CC_SYNTHESIZE(float, ExpRate, ExpRate);
    CC_SYNTHESIZE(float, CriRate, CriRate);
    CC_SYNTHESIZE(float, CriDam, CriDam);
    CC_SYNTHESIZE(float, ComboRate, ComboRate);
    CC_SYNTHESIZE(float, EncounterRate, EncounterRate);
    CC_SYNTHESIZE(float, SpeedRate, SpeedRate);
    CC_SYNTHESIZE(float, ItemDropRate, ItemDropRate);
    CC_SYNTHESIZE(float, GoldGropRate, GoldDropRate);
    
public:
    static ItemData* getItemData(int ItemID);
private:
    static int sqlite_callback(
                               void* pv,    /* 由 sqlite3_exec() 的第四个参数传递而来 */
                               int column,        /* 表的列数 */
                               char** dbResult,    /* 指向查询结果的指针数组, 可以由 sqlite3_column_text() 得到 */
                               char** col        /* 指向表头名的指针数组, 可以由 sqlite3_column_name() 得到 */
    );

    
    
};

#endif /* defined(__MyRPG__ItemData__) */
