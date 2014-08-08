//
//  Status.h
//  MyRPG
//
//  Created by RocLee on 14-8-5.
//
//

#ifndef __MyRPG__Status__
#define __MyRPG__Status__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class Status:public CCLayer{
public:
    virtual bool init();
    static CCScene* scene();
    CREATE_FUNC(Status);
    
private:
    CCSize getWinsize();
    void setupViews();

};

#endif /* defined(__MyRPG__Status__) */
