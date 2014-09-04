//
//  Battle.h
//  MyRPG
//
//  Created by RocLee on 14-7-19.
//
//

#ifndef __MyRPG__Battle__
#define __MyRPG__Battle__

#include <iostream>
#include "cocos2d.h"
#include "UserData.h"
#include "MonsterManager.h"


USING_NS_CC;

class Battle:public CCLayer{
public:
    CREATE_FUNC(Battle);
    virtual bool init();
    virtual void onExit();
    static void setRandomSeed();
    static const char* IntToChar(int num);
private:
    CCSprite* blackbg;
    MonsterManager* mm;
    CCSprite* player;
    CCSprite* monster;
    
    float pHP;
    float mHP;
    CCProgressTimer* pHPBar;
    CCProgressTimer* mHPBar;
    
    bool isinbattle;
    bool isbattlepaused;
    bool isplayerfailed;
    int maxCombo_player;
    int comboNO_player;
    int maxCombo_monster;
    int comboNO_monster;

    CCSize GetWinSize();
    
    void PlayerAttack();
    void MonsterAttack();
    void PlayerAttackCallBack(CCNode* pSender);
    void MonsterAttackCallBack(CCNode* pSender);
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    int ComboCheck(float ComboRatio);
    bool isCriticalHit(float CriticalRatio);
    
    float levelCorrection(int AtkLevel,int DefLevel);
    void setupViews();
    void finalview(bool isPlayerWins);
    
    int EXPnow;
    int EXPadd;
    int EXPmax;
    CCProgressTimer* EXPBar;
    void LevelUp();
    bool LevelUpEXP();
    void EXPBarcallbackLvUp(CCNode* pSender);
    void EXPBarcallbackLv(CCNode* pSender);
    
    CCLabelAtlas* lvNumber;
    CCLabelBMFont* startlabel;
    CCLabelBMFont* pauselabel;
    
//    void ExitNotify();
    

    
    void menucallback(CCObject* pSender);
    
    
};

#endif /* defined(__MyRPG__Battle__) */
