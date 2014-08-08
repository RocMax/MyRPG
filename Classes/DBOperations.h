//
//  DBOperations.h
//  MyRPG
//
//  Created by RocLee on 14-6-29.
//
//

#ifndef __MyRPG__DBOperations__
#define __MyRPG__DBOperations__

#include <iostream>
#include "cocos2d.h"

#define DB_FILENAME "data.db"
extern "C"
{
#include "sqlite3.h"
};


USING_NS_CC;

class DBOperation{
public:
    
    static sqlite3* openDB();

    
    
};





#endif /* defined(__MyRPG__DBOperations__) */
