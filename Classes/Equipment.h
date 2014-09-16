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
    ~Equipment();
private:
    CCSize getWinsize();
    void setupViews();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    CCArray* equipmentsarray;
    CCArray* bagarray;
    void refreshbag(int itemtype);
    void refreshequip();
    CCLabelTTF* ItemIntro;
    int equipflag;
    int touchitemid;
    void equipmenucallback(CCObject* pSender);
    void okmenucallback(CCObject* pSender);
    void changeequipment(int equipflag,int itemid);
    void changebag(int itemid,bool isadd);



};


#endif /* defined(__MyRPG__Equipment__) */
