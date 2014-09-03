//
//  Equipment.h
//  MyRPG
//
//  Created by RocLee on 14-8-28.
//
//

#ifndef __MyRPG__Equipment__
#define __MyRPG__Equipment__

#include <iostream>
#include "cocos2d.h"
#include "UserData.h"


USING_NS_CC;

class Equipment:public CCLayer{
public:
    virtual bool init();
    static CCScene* scene();
    CREATE_FUNC(Equipment);
    virtual void draw();
private:
    UserData* ud;
    CCSize getWinsize();
    void setupViews();

};


#endif /* defined(__MyRPG__Equipment__) */