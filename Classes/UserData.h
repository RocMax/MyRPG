//
//  UserData.h
//  MyRPG
//
//  Created by RocLee on 14-7-4.
//
//

#ifndef __MyRPG__UserData__
#define __MyRPG__UserData__

#include <iostream>
#include "cocos2d.h"

#define USER_DEFAULT CCUserDefault::sharedUserDefault()
#define SPEED_DEFAULT 10.0f

#define EXP_POWER 1.14

#define DAMAGE_REDUCTION_a 10000
#define DAMAGE_REDUCTION_k -6607.260726
#define DAMAGE_REDUCTION_b 0.760066007

#define LUK_ADDITION_a 50000
#define LUK_ADDITION_k -375000
#define LUK_ADDITION_b 7.5

#define CRITICAL_RATIO_a 3000
#define CRITICAL_RATIO_k -2607
#define CRITICAL_RATIO_b 0.739

#define CRITICAL_DAMAGE_a 3000
#define CRITICAL_DAMAGE_k -28302
#define CRITICAL_DAMAGE_b 10.534


using namespace std;
USING_NS_CC;

class UserData:public CCObject{
    //主角基础属性
    CC_SYNTHESIZE(char*, Name, Name);
    CC_SYNTHESIZE(char*, Pic, Pic);
    CC_SYNTHESIZE(int, Level, Level);
    CC_SYNTHESIZE(int, EXP, EXP);
    CC_SYNTHESIZE(int, GameTimes, GameTimes);
    
    CC_SYNTHESIZE(float, HP, HP);
    CC_SYNTHESIZE(float, ATK, ATK);
    CC_SYNTHESIZE(float, DEF, DEF);
    CC_SYNTHESIZE(float, AGI, AGI);
    CC_SYNTHESIZE(float, LUK, LUK);

    CC_SYNTHESIZE(float, HPPerPoint, HPPerPoint);
    CC_SYNTHESIZE(float, ATKPerPoint, ATKPerPoint);
    CC_SYNTHESIZE(float, DEFPerPoint, DEFPerPoint);
    CC_SYNTHESIZE(float, AGIPerPoint, AGIPerPoint);
    CC_SYNTHESIZE(float, LUKPerPoint, LUKPerPoint);
    
    CC_SYNTHESIZE(int, PointPerLevel, PointPerLevel);
    CC_SYNTHESIZE(int, SparePoint, SparePoint);
    
    CC_SYNTHESIZE(float, MoveSpeed, MoveSpeed);
    CC_SYNTHESIZE(float, MultipleSpeed, MultipleSpeed);
    
    //主角计算属性
    CC_SYNTHESIZE(float, ComboRatio, ComboRatio);
    CC_SYNTHESIZE(float, CricialRatio, CriticalRatio);
    CC_SYNTHESIZE(float, CriticalDamage, CriticalDamage);
    
    //地图及位置相关
    CC_SYNTHESIZE(char*, Map, Map);
    CC_SYNTHESIZE(int, MapOffsetX, MapOffsetX);
    CC_SYNTHESIZE(int, MapOffsetY, MapOffsetY);
    CC_SYNTHESIZE(int, PositionX, PositionX);
    CC_SYNTHESIZE(int, PositionY, PositionY);
    CC_SYNTHESIZE(int, MapArea, MapArea);
    
    //背包
    CC_SYNTHESIZE(char*, EquipBag, EquipBag);
    
    //装备栏
    CC_SYNTHESIZE(int, Weapon1, Weapon1);
    CC_SYNTHESIZE(int, Armor1, Armor1);
    CC_SYNTHESIZE(int, Accessor1, Accessor1);
    CC_SYNTHESIZE(int, Accessor2, Accessor2);
    CC_SYNTHESIZE(int, Accessor3, Accessor3);
    CC_SYNTHESIZE(int, Accessor4, Accessor4);
    CC_SYNTHESIZE(int, Accessor5, Accessor5);
    CC_SYNTHESIZE(int, Accessor6, Accessor6);
    
    //装备影响的数值参数,a为倍率,
    CC_SYNTHESIZE(float, EncounterNum_a, EncounterNum_a);

    
    //属性最终值
    CC_SYNTHESIZE(float, Final_ATK, Final_ATK);
    CC_SYNTHESIZE(float, Final_DemageReduction, Final_DemageReduction);
    
public:
    static UserData* LoadUserData();
    static void SaveUserData();
    
    static void RefreshUserData();
    
    static char* converstringtochar(string s);
    static string convertchartostring(char* c);
    

    
    
    
    
};

#endif /* defined(__MyRPG__UserData__) */
