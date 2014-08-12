//
//  Status.h
//  MyRPG
//
//  Created by RocLee on 14-8-11.
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
    virtual void onExit();
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
private:
    UserData* ud;
    CCSize getWinsize();
    void setupViews();
    virtual void onEnter();

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
    CCArray* buttomarray;
    int flag;
    virtual void update(float t);
    
    void labelchange(CCLabelAtlas* label,bool isadd);
    
    void okmeuncallback(CCNode* pSender);
    void canclemenucallback(CCNode* pSender);
    void resetmenucallback(CCNode* pSender);

};

#endif /* defined(__MyRPG__Status__) */
