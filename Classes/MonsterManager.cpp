//
//  MonsterManager.cpp
//  MyRPG
//
//  Created by RocLee on 14-7-8.
//
//

#include "MonsterManager.h"


static MonsterManager* m_instance=NULL;

MonsterManager* MonsterManager::GetMonster(int MapArea){
    if (!m_instance) {
        m_instance=new MonsterManager();
    }

    char* errorMsg;
    //读取数据库
    sqlite3* pDB=DBOperation::openDB();
    CCString* sqlcs=CCString::createWithFormat("select * from Monster where MapArea=%d",MapArea);
    const char* sql=sqlcs->getCString();
    CCLog(sql);
    int result=sqlite3_exec(pDB, sql, sqlite_callback, NULL, &errorMsg);
    
    if (result!=SQLITE_OK) {
        CCLog(errorMsg);
    }
    
    sqlite3_close(pDB);
    
    
    //需要写掉落生成函数,然后把掉落填进instance里
    
    
    int picno=(int)(CCRANDOM_0_1()*4)+1;

    CCString* mns=CCString::createWithFormat("Monster%d.png",picno);
    const char* monsterpic=mns->getCString();
//    CCLOG(monsterpic);
    m_instance->setM_Pic(monsterpic);
    
    
    return m_instance;
}

int MonsterManager::sqlite_callback(void *pv, int column, char **dbResult, char **col){
    //设定属性值
    m_instance->setM_Level(atoi(dbResult[1]));
    m_instance->setM_Name(dbResult[2]);
    m_instance->setM_HP(atof (dbResult[3]));
    m_instance->setM_ATK(atof(dbResult[4]));
    m_instance->setM_DamageReduction(atof(dbResult[5]));
    m_instance->setM_ComboRatio(atof(dbResult[6]));
    m_instance->setM_CriticalRatio(atof(dbResult[7]));
    m_instance->setM_CriticalDamage(atof(dbResult[8]));
    m_instance->setM_Exp(atoi(dbResult[9]));
    m_instance->setM_Gold(atoi(dbResult[10]));
    
    return 0;     //callback一定要返回0!!!
    
}




//获取掉落,待完善
//int MonsterManager::getDropItem(char **dbReasult){
//    
//}
