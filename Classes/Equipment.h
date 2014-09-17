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
    virtual void onExit();
    //掉落时调用此函数
    void changebag(int itemid,bool isadd);
private:
    CCSize getWinsize();
    void setupViews();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    CCArray* equipmentsarray;
    CCArray* bagarray;
    CCArray* equiplabelarray;
    void refreshbag(int itemtype);
    void refreshequip();
    CCLabelTTF* ItemIntro;
    int equipflag;
    int touchitemid;
    void equipmenucallback(CCObject* pSender);
    void okmenucallback(CCObject* pSender);
    void changeequipment(int equipflag,int itemid);
    bool isexistinginbag(int itemid);

};


#endif /* defined(__MyRPG__Equipment__) */
