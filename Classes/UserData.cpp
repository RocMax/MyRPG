//
//  UserData.cpp
//  MyRPG
//
//  Created by RocLee on 14-7-4.
//
//

#include "UserData.h"



static UserData* instance=NULL;

UserData* UserData::LoadUserData(){
    if (!instance) {
        instance=new UserData();

    }
    instance->setName(converstringtochar(USER_DEFAULT->getStringForKey("Name")));
    instance->setPic(converstringtochar(USER_DEFAULT->getStringForKey("Pic")));
    instance->setLevel(USER_DEFAULT->getIntegerForKey("Level"));
    instance->setEXP(USER_DEFAULT->getIntegerForKey("EXP"));
    instance->setGameTimes(USER_DEFAULT->getIntegerForKey("GameTimes"));
    
    instance->setHP(USER_DEFAULT->getFloatForKey("HP"));
    instance->setATK(USER_DEFAULT->getFloatForKey("ATK"));
    instance->setDEF(USER_DEFAULT->getFloatForKey("DEF"));
    instance->setAGI(USER_DEFAULT->getFloatForKey("AGI"));
    instance->setLUK(USER_DEFAULT->getFloatForKey("LUK"));
    
    instance->setHPPerPoint(USER_DEFAULT->getFloatForKey("HPPerPoint"));
    instance->setATKPerPoint(USER_DEFAULT->getFloatForKey("ATKPerPoint"));
    instance->setDEFPerPoint(USER_DEFAULT->getFloatForKey("DEFPerPoint"));
    instance->setAGIPerPoint(USER_DEFAULT->getFloatForKey("AGIPerPoint"));
    instance->setLUKPerPoint(USER_DEFAULT->getFloatForKey("LUKPerPoint"));
    
    instance->setPointPerLevel(USER_DEFAULT->getIntegerForKey("PointPerLevel"));
    instance->setSparePoint(USER_DEFAULT->getIntegerForKey("SparePoint"));
    
    instance->setMoveSpeed(USER_DEFAULT->getFloatForKey("MoveSpeed"));
    instance->setMultipleSpeed(USER_DEFAULT->getFloatForKey("MultipleSpeed"));
    
    instance->setComboRatio(USER_DEFAULT->getFloatForKey("ComboRatio"));
    instance->setCriticalRatio(USER_DEFAULT->getFloatForKey("CriticalRatio"));
    instance->setCriticalDamage(USER_DEFAULT->getFloatForKey("CriticalDamage"));
    
    
    instance->setMap(converstringtochar(USER_DEFAULT->getStringForKey("Map")));
    instance->setMapOffsetX(USER_DEFAULT->getIntegerForKey("MapOffsetX"));
    instance->setMapOffsetY(USER_DEFAULT->getIntegerForKey("MapOffsetY"));
    instance->setPositionX(USER_DEFAULT->getIntegerForKey("PositionX"));
    instance->setPositionY(USER_DEFAULT->getIntegerForKey("PositionY"));
    instance->setMapArea(USER_DEFAULT->getIntegerForKey("MapArea"));
    
    instance->setEncounterNum_a(USER_DEFAULT->getFloatForKey("EncounterNum_a"));

    
    instance->setEquipBag(converstringtochar(USER_DEFAULT->getStringForKey("EquipBag")));
    
    instance->setWeapon1(USER_DEFAULT->getIntegerForKey("Weapon1"));
    instance->setArmor1(USER_DEFAULT->getIntegerForKey("Armor1"));
    instance->setAccessor1(USER_DEFAULT->getIntegerForKey("Accessor1"));
    instance->setAccessor2(USER_DEFAULT->getIntegerForKey("Accessor2"));
    instance->setAccessor3(USER_DEFAULT->getIntegerForKey("Accessor3"));
    instance->setAccessor4(USER_DEFAULT->getIntegerForKey("Accessor4"));
    instance->setAccessor5(USER_DEFAULT->getIntegerForKey("Accessor5"));
    instance->setAccessor6(USER_DEFAULT->getIntegerForKey("Accessor6"));
    
    //以下是计算后的值
    instance->setFinal_ATK(USER_DEFAULT->getFloatForKey("Final_ATK"));
    instance->setFinal_DemageReduction(USER_DEFAULT->getFloatForKey("Final_DemageReduction"));

    
    return instance;
}



void UserData::SaveUserData(){
    if (!instance) {
        CCLOG("UserData not exist");
    }
    else{
        USER_DEFAULT->setStringForKey("Name", instance->getName());
        USER_DEFAULT->setStringForKey("Pic", instance->getPic());
        USER_DEFAULT->setIntegerForKey("Level", instance->getLevel());
        USER_DEFAULT->setIntegerForKey("EXP", instance->getEXP());
        USER_DEFAULT->setIntegerForKey("GameTimes", instance->getGameTimes());
        USER_DEFAULT->setFloatForKey("HP", instance->getHP());
        USER_DEFAULT->setFloatForKey("ATK", instance->getATK());
        USER_DEFAULT->setFloatForKey("DEF", instance->getDEF());
        USER_DEFAULT->setFloatForKey("AGI", instance->getAGI());
        USER_DEFAULT->setFloatForKey("LUK", instance->getLUK());
        USER_DEFAULT->setFloatForKey("HPPerPoint", instance->getHPPerPoint());
        USER_DEFAULT->setFloatForKey("ATKPerPoint", instance->getATKPerPoint());
        USER_DEFAULT->setFloatForKey("DEFPerPoint", instance->getDEFPerPoint());
        USER_DEFAULT->setFloatForKey("AGIPerPoint", instance->getAGIPerPoint());
        USER_DEFAULT->setFloatForKey("LUKPerPoint", instance->getLUKPerPoint());
        USER_DEFAULT->setIntegerForKey("PointPerLevel", instance->getPointPerLevel());
        USER_DEFAULT->setIntegerForKey("SparePoint", instance->getSparePoint());
        USER_DEFAULT->setFloatForKey("MoveSpeed", instance->getMoveSpeed());
        USER_DEFAULT->setFloatForKey("MultipleSpeed", instance->getMultipleSpeed());
        
        USER_DEFAULT->setFloatForKey("ComboRatio", instance->getComboRatio());
        USER_DEFAULT->setFloatForKey("CriticalRatio", instance->getCriticalRatio());
        USER_DEFAULT->setFloatForKey("CriticalDamage", instance->getCriticalDamage());
        
        USER_DEFAULT->setStringForKey("Map",instance->getMap());
        USER_DEFAULT->setIntegerForKey("MapOffsetX", instance->getMapOffsetX());
        USER_DEFAULT->setIntegerForKey("MapOffsetY", instance->getMapOffsetY());
        USER_DEFAULT->setIntegerForKey("PositionX", instance->getPositionX());
        USER_DEFAULT->setIntegerForKey("PositionY", instance->getPositionY());
        USER_DEFAULT->setIntegerForKey("MapArea", instance->getMapArea());
        
        USER_DEFAULT->setFloatForKey("EncounterNum_a", instance->getEncounterNum_a());
        
        USER_DEFAULT->setStringForKey("EquipBag", instance->getEquipBag());
        USER_DEFAULT->setIntegerForKey("Weapon1", instance->getWeapon1());
        USER_DEFAULT->setIntegerForKey("Armor1", instance->getArmor1());
        USER_DEFAULT->setIntegerForKey("Accessor1", instance->getAccessor1());
        USER_DEFAULT->setIntegerForKey("Accessor2", instance->getAccessor2());
        USER_DEFAULT->setIntegerForKey("Accessor3", instance->getAccessor3());
        USER_DEFAULT->setIntegerForKey("Accessor4", instance->getAccessor4());
        USER_DEFAULT->setIntegerForKey("Accessor5", instance->getAccessor5());
        USER_DEFAULT->setIntegerForKey("Accessor6", instance->getAccessor6());
        
        
        USER_DEFAULT->setFloatForKey("Final_ATK", instance->getFinal_ATK());
        USER_DEFAULT->setFloatForKey("Final_DemageReduction", instance->getFinal_DemageReduction());
        
        USER_DEFAULT->flush();
        
        
    }
    
    
}

//根据主角基础数值及装备情况刷新最终数值,在升级加点或更换装备后调用此函数
void UserData::RefreshUserData(){
    USER_DEFAULT->setFloatForKey("Final_ATK", USER_DEFAULT->getFloatForKey("ATK")); //需修改
    USER_DEFAULT->setFloatForKey("Final_DemageReduction", DAMAGE_REDUCTION_k/(USER_DEFAULT->getFloatForKey("DEF")+DAMAGE_REDUCTION_a)+DAMAGE_REDUCTION_b);

}




char* UserData::converstringtochar(string s){
    const char* c=s.c_str();
    char* buff=new char[strlen(c)+1];
    strcpy(buff, c);
    return buff;
}

string UserData::convertchartostring(char *c){
    return (string)c;
}
