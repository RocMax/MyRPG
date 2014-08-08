//
//  Home.h
//  MyRPG
//
//  Created by RocLee on 14-7-27.
//
//

#ifndef __MyRPG__Home__
#define __MyRPG__Home__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;

class Home:public CCLayer{
public:
    virtual bool init();
    static CCScene* scene();
    CREATE_FUNC(Home);
    
private:
    CCSize getWinsize();
    void setupViews();
    void storymenucallback(CCObject *pSender);
    void attackmenucallback(CCObject *pSender);
    void historymenucallback(CCObject *pSender);
};

#endif /* defined(__MyRPG__Home__) */
