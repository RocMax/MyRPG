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
#include "UserData.h"

USING_NS_CC;

class Status:public CCLayer{
public:
    virtual bool init();
    static CCScene* scene();
    CREATE_FUNC(Status);
    virtual void draw();
    
private:
    UserData* ud;
    CCSize getWinsize();
    void setupViews();
    virtual void onEnter();
};

#endif /* defined(__MyRPG__Status__) */
