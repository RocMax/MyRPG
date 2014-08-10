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
    void addmeuncallback(CCNode* pSender);
    void submenucallback(CCNode* pSender);
    int sp;
    int HP;
    int ATK;
    int DEF;
    int AGI;
    int LUK;
    CCLabelAtlas* statunum1;
    CCLabelAtlas* statunum2;
    CCLabelAtlas* statunum3;
    CCLabelAtlas* statunum4;
    CCLabelAtlas* statunum5;
    CCLabelAtlas* sparepoint;
    int flag;
    virtual void update(float t);
    
    void labelchange(CCLabelAtlas* label,bool isadd);
    

};

#endif /* defined(__MyRPG__Status__) */
