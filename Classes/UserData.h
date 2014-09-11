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
#include "ItemData.h"

#define USER_DEFAULT CCUserDefault::sharedUserDefault()
#define USER_DATA UserData::SharedUserData()
 
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

#define COMBO_RATIO_a 3000
#define COMBO_RATIO_k -4770
#define COMBO_RATIO_b 1.95

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

    
    //地图及位置相关
    CC_SYNTHESIZE(char*, Map, Map);
    CC_SYNTHESIZE(int, MapOffsetX, MapOffsetX);
    CC_SYNTHESIZE(int, MapOffsetY, MapOffsetY);
    CC_SYNTHESIZE(int, PositionX, PositionX);
    CC_SYNTHESIZE(int, PositionY, PositionY);
    CC_SYNTHESIZE(int, MapArea, MapArea);
    
    //背包
    CC_SYNTHESIZE(CCDictionary*, EquipBag, EquipBag);
    
    //装备栏
    CC_SYNTHESIZE(CCDictionary*, Equipments, Equipments);
    
    //基础属性最终值
    CC_SYNTHESIZE(float, Final_HP, Final_HP);
    CC_SYNTHESIZE(float, Final_ATK, Final_ATK);
    CC_SYNTHESIZE(float, Final_DEF, Final_DEF);
    CC_SYNTHESIZE(float, Final_AGI, Final_AGI);
    CC_SYNTHESIZE(float, Final_LUK, Final_LUK);
    
    //计算属性最终值
    CC_SYNTHESIZE(float, Final_DamageReduction, Final_DamageReduction);
    CC_SYNTHESIZE(float, Final_HPAbsorb, Final_HPAbsorb);
    CC_SYNTHESIZE(float, Final_ComboRatio, Final_ComboRatio);
    CC_SYNTHESIZE(float, Final_CricialRatio, Final_CriticalRatio);
    CC_SYNTHESIZE(float, Final_CriticalDamage, Final_CriticalDamage);
    
    CC_SYNTHESIZE(float, Final_EncounterRate, Final_EncounterRate);
    CC_SYNTHESIZE(float, Final_MoveSpeed, Final_MoveSpeed);
    
    CC_SYNTHESIZE(float, Final_ExpRate, Final_ExpRate);
    CC_SYNTHESIZE(float, Final_LUKAddition, Final_LUKAddition);
    

    
public:
    static UserData* SharedUserData();
    void LoadUserData();
    void SaveUserData();
    
    void RefreshUserData();
    
    char* converstringtochar(string s);
    string convertchartostring(char* c);
    
    static void convertchartodic(char* c,CCDictionary* d,bool isEquiping);
    static void convertdictochar(CCDictionary* d,char* c,bool isEquiping);
    
private:
    float equpmentsaddup(ItemData::enumStatu statuID);
    

    
};

#endif /* defined(__MyRPG__UserData__) */
