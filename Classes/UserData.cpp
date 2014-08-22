//
//  UserData.cpp
//  MyRPG
//
//  Created by RocLee on 14-7-4.
//
//

#include "UserData.h"
#include "ItemData.h"



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

    instance->setMap(converstringtochar(USER_DEFAULT->getStringForKey("Map")));
    instance->setMapOffsetX(USER_DEFAULT->getIntegerForKey("MapOffsetX"));
    instance->setMapOffsetY(USER_DEFAULT->getIntegerForKey("MapOffsetY"));
    instance->setPositionX(USER_DEFAULT->getIntegerForKey("PositionX"));
    instance->setPositionY(USER_DEFAULT->getIntegerForKey("PositionY"));
    instance->setMapArea(USER_DEFAULT->getIntegerForKey("MapArea"));

    

    
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
        //存储基础值
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
        
        USER_DEFAULT->setStringForKey("Map",instance->getMap());
        USER_DEFAULT->setIntegerForKey("MapOffsetX", instance->getMapOffsetX());
        USER_DEFAULT->setIntegerForKey("MapOffsetY", instance->getMapOffsetY());
        USER_DEFAULT->setIntegerForKey("PositionX", instance->getPositionX());
        USER_DEFAULT->setIntegerForKey("PositionY", instance->getPositionY());
        USER_DEFAULT->setIntegerForKey("MapArea", instance->getMapArea());
        
        //存储装备和包裹的字符串
        USER_DEFAULT->setStringForKey("EquipBag", convertdictochar(instance->getEquipBag()));
        USER_DEFAULT->setStringForKey("Equipments", convertdictochar(instance->getequipments()));
        
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


//将字符串转化为存储装备属性的CCDictionary,key0-8分别表示武器,防具,饰品1-6
CCDictionary* UserData::convertchartodic(char *c){
    CCDictionary* dic=CCDictionary::create();
    char* temp=strdup(c);
    const char* delim=":";
    int i=0;
    do {
        int itemid=atoi(strsep(&temp, delim)) ;
        ItemData* idata=ItemData::getItemData(itemid);
        dic->setObject(idata, i);
        i++;
    } while (temp!=NULL);
    return dic ;

}

char* UserData::convertdictochar(cocos2d::CCDictionary *d){
    CCDictElement* pElement;
    CCString* str;
    CCDICT_FOREACH(d, pElement){
        if (pElement!=NULL) {
            ItemData* idata= (ItemData*)pElement;
            str=CCString::createWithFormat("%s:%d",str->getCString(),idata->getItemID());
        }
    }
    return strdup(str->getCString());
}
