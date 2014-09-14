//
//  UserData.cpp
//  MyRPG
//
//  Created by RocLee on 14-7-4.
//
//

#include "UserData.h"


static UserData* instance=NULL;

UserData* UserData::SharedUserData(){
    if (!instance) {
        instance=new UserData();

    }
    
    return instance;
}

void UserData::LoadUserData(){
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
    CCDictionary* bagtemp=CCDictionary::create();
    convertchartodic(converstringtochar(USER_DEFAULT->getStringForKey("EquipBag")),bagtemp,false);
    instance->setEquipBag(bagtemp);
    EquipBag->retain();
//    bagtemp->release();
    CCDictionary* equiptemp=CCDictionary::create();
    convertchartodic(converstringtochar(USER_DEFAULT->getStringForKey("Equipments")),equiptemp,true);
    instance->setEquipments(equiptemp);
    Equipments->retain();
//    equiptemp->release();
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
        char* temp;
        convertdictochar(instance->getEquipBag(),temp);
        USER_DEFAULT->setStringForKey("EquipBag", temp);
        convertdictochar(instance->getEquipments(),temp);
        USER_DEFAULT->setStringForKey("Equipments", temp);
        
        USER_DEFAULT->flush();
        
    }
    
    
}

//根据主角基础数值及装备情况刷新最终数值,在升级加点或更换装备后调用此函数,在首次生成UserData时也需调用
void UserData::RefreshUserData(){
    //基础属性计算
    //生命值计算方法:点数*每点加的生命值+武器装备提供的生命值
    instance->setFinal_HP(instance->getHP()*instance->getHPPerPoint()+instance->equpmentsaddup(ItemData::eItemHP));
    //攻击力计算方法:(点数*每点加的攻击力+武器装备提供的攻击力)*武器提供的攻击倍率
    instance->setFinal_ATK((instance->getATK()*instance->getATKPerPoint()+instance->equpmentsaddup(ItemData::eItemATK))*(1+instance->equpmentsaddup(ItemData::eWeaponATKRate)));
    //防御力计算方法:点数*每点加的防御力+装备提供的防御力
    instance->setFinal_DEF(instance->getDEF()*instance->getDEFPerPoint()+instance->equpmentsaddup(ItemData::eItemDEF));
    //敏捷值计算方法:点数*每点加的敏捷值+装备提供的敏捷值
    instance->setFinal_AGI(instance->getAGI()*instance->getAGIPerPoint()+instance->equpmentsaddup(ItemData::eItemAGI));
    //幸运值计算方法:点数*每点加的幸运值+装备提供的幸运值
    instance->setFinal_LUK(instance->getLUK()*instance->getLUKPerPoint()+instance->equpmentsaddup(ItemData::eItemLUK));
    
    //以下是计算属性
    //伤害减免计算方法:k/(def+a)+b
    instance->setFinal_DamageReduction(DAMAGE_REDUCTION_k/(instance->getFinal_DEF()+DAMAGE_REDUCTION_a)+DAMAGE_REDUCTION_b);
    //攻击吸血计算方法:装备提供的攻击吸血
    instance->setFinal_HPAbsorb(instance->equpmentsaddup(ItemData::eHPAbsorb));
    //连击率计算方法:k/(agi+a)+b
    instance->setFinal_ComboRatio(COMBO_RATIO_k/(instance->getFinal_AGI()+COMBO_RATIO_a)+COMBO_RATIO_b);
    //暴击率计算方法:k/(agi+a)+b
    instance->setFinal_CriticalRatio(CRITICAL_RATIO_k/(instance->getFinal_AGI()+CRITICAL_RATIO_a)+CRITICAL_RATIO_b);
    //暴击伤害计算方法:k/(agi+a)+b
    instance->setFinal_CriticalDamage(CRITICAL_DAMAGE_k/(instance->getFinal_AGI()+CRITICAL_DAMAGE_a)+CRITICAL_DAMAGE_b);
    //遇怪速率计算方法:装备提供的遇怪速率
    instance->setFinal_EncounterRate(instance->equpmentsaddup(ItemData::eEncounterRate));
    //移动速度计算方法:原始移动速度*(1+装备提供的速度加成)
    instance->setFinal_MoveSpeed(SPEED_DEFAULT*(1+instance->equpmentsaddup(ItemData::eSpeedRate)));
    //道具经验加成计算方法:装备提供的经验加成
    instance->setFinal_ExpRate(instance->equpmentsaddup(ItemData::eExpRate));
    //幸运加成计算方法:k/(luk+a)+b
    instance->setFinal_LUKAddition(LUK_ADDITION_k/(instance->getFinal_LUK()+LUK_ADDITION_a)+LUK_ADDITION_b);

}




char* UserData::converstringtochar(string s){
    return strdup(s.c_str());
}

string UserData::convertchartostring(char *c){
    return (string)c;
}


//将字符串转化为存储装备属性的CCDictionary,key0-8分别表示武器,防具,饰品1-6
void UserData::convertchartodic(char *c,CCDictionary* d,bool isEquiping){

    if (strcmp(c, "0")==0) {
        d=NULL;
    }
    else{
        char* temp=strdup(c);
        strsep(&temp, ";");
        int i=0;
        char* itemtemp;
        do {
            itemtemp=strsep(&temp, ";");
            int itemid=atoi(strsep(&itemtemp, ":")) ;
            ItemData* idata=ItemData::getItemData(itemid);
            if (isEquiping) {
                idata->setItemcount(1);
            }
            else{
                idata->setItemcount(atoi(itemtemp));
            }
            d->setObject(idata, i);
            i++;
        } while (temp!=NULL);
        
    }
    
}

void UserData::convertdictochar(cocos2d::CCDictionary *d,char*c){
    if (d!=NULL) {
        CCDictElement* pElement;
        CCString* str=CCString::createWithFormat("0");
        CCDICT_FOREACH(d, pElement){
            if (pElement!=NULL) {
                ItemData* idata= (ItemData*)pElement->getObject();
                str=CCString::createWithFormat("%s;%d:%d",str->getCString(),idata->getItemID(),idata->getItemcount());
            }
            else continue;
        }
        //        char* temp=strdup(str->getCString());
        //        strsep(&temp, ":");   //切掉开头多余的":"
        c=strdup(str->getCString());
    }
    else{
        c=strdup("0") ;
    }
}

float UserData::equpmentsaddup(ItemData::enumStatu statuID){
    CCDictElement* pElement;
    CCDictionary* dic=instance->getEquipments();
    float sum=0;
    CCDICT_FOREACH(dic, pElement){
        ItemData* idata= (ItemData*)pElement->getObject();
        ItemData::pGet p=idata->getgetFounc(statuID);
        sum+=(idata->*p)();
    }
    return sum;
}




