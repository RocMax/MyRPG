//
//  MonsterManager.h
//  MyRPG
//
//  Created by RocLee on 14-7-8.
//
//

#ifndef __MyRPG__MonsterManager__
#define __MyRPG__MonsterManager__

#include <iostream>
#include "cocos2d.h"
#include "UserData.h"
#include "sqlite3.h"
#include "DBOperations.h"


USING_NS_CC;

class MonsterManager:public CCObject{
    CC_SYNTHESIZE(int, M_Level, M_Level);
    CC_SYNTHESIZE(char*, M_Name, M_Name);
    CC_SYNTHESIZE(const char*, M_Pic, M_Pic);
    CC_SYNTHESIZE(float, M_HP, M_HP);
    CC_SYNTHESIZE(float, M_ATK, M_ATK);
    CC_SYNTHESIZE(float, M_DamageReduction , M_DamageReduction);
    CC_SYNTHESIZE(float, M_ComboRatio, M_ComboRatio);
    CC_SYNTHESIZE(float, M_CriticalRatio, M_CriticalRatio);
    CC_SYNTHESIZE(float, M_CriticalDamage, M_CriticalDamage);
    CC_SYNTHESIZE(int, M_Exp, M_Exp);
    CC_SYNTHESIZE(int, M_Gold, M_Gold);
public:
    static MonsterManager* GetMonster(int MapArea);
    
private:
    static int sqlite_callback(
                        void* pv,    /* 由 sqlite3_exec() 的第四个参数传递而来 */
                        int column,        /* 表的列数 */
                        char** dbResult,    /* 指向查询结果的指针数组, 可以由 sqlite3_column_text() 得到 */
                        char** col        /* 指向表头名的指针数组, 可以由 sqlite3_column_name() 得到 */
    );
};


#endif /* defined(__MyRPG__MonsterManager__) */
