//
//  Start.h
//  MyRPG
//
//  Created by RocLee on 14-7-25.
//
//

#ifndef __MyRPG__Start__
#define __MyRPG__Start__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class Start:public CCLayer{
public:
    virtual bool init();
    static CCScene* scene();
    CREATE_FUNC(Start);
    virtual void onExit();
    
private:
    CCSize getWinsize();
    void setupViews();
    void callback();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    
};

#endif /* defined(__MyRPG__Start__) */
