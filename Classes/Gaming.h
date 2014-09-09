//
//  Gaming.h
//  MyRPG
//
//  Created by RocLee on 14-7-4.
//
//

#ifndef __MyRPG__Gaming__
#define __MyRPG__Gaming__

#include <iostream>
#include "cocos2d.h"
#include "UserData.h"

USING_NS_CC;
class Gaming:public CCLayer{
    
public:
    virtual bool init();
    static CCScene* scene();
    CREATE_FUNC(Gaming);
    
    
    CCTMXTiledMap* tiledMap;
    CCTMXLayer* metaLayer;
    CCTMXLayer* levelLayer;
    
    CCSprite* player;
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
    void onEnter();
    void onExit();
    void btlayerExitObserver();
    const char*  battlelayerexited;

    void refreshGameTimes();
    

    
    
private:
    void SetupViews();
    void EncounterMonster(float t);
    float EncounterNum;
    CCSize GetWinSize();
    bool touchFlag;
    CCPoint targetPoint;
    virtual void update(float t);
    CCPoint getOffset(CCPoint viewPoint);
    void movePlayer(CCPoint targetpos,float t);
    CCPoint getTiledCoord(CCPoint position);
    bool isReachable(CCPoint tileCoord);
    int getMapLevel(CCPoint tileCoord);
    void EquipmentsMenucallback(CCObject* pSender);
};

#endif /* defined(__MyRPG__Gaming__) */
