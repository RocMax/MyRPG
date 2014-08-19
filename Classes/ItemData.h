//
//  ItemData.h
//  MyRPG
//
//  Created by RocLee on 14-8-18.
//
//

#ifndef __MyRPG__ItemData__
#define __MyRPG__ItemData__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class ItemData:public CCObject{
    CC_SYNTHESIZE_READONLY(int, ItemID, ItemID);
    CC_SYNTHESIZE_READONLY(char*, ItemName, ItemName);
    CC_SYNTHESIZE_READONLY(char*, ItemPic, ItemPic)
    CC_SYNTHESIZE_READONLY(int, ItemPrice, ItemPrice);
    CC_SYNTHESIZE_READONLY(int, EquipType, EquipType);
    CC_SYNTHESIZE_READONLY(bool, isUnique, isunique);
    CC_SYNTHESIZE_READONLY(float, ItemHP, ItemHP);
    CC_SYNTHESIZE_READONLY(float, ItemATK, ItemATK);
    CC_SYNTHESIZE_READONLY(float, ItemDEF, ItemDEF);
    CC_SYNTHESIZE_READONLY(float, ItemAGI, ItemAGI);
    CC_SYNTHESIZE_READONLY(float, ItemLUK, ItemLUK);
    CC_SYNTHESIZE_READONLY(float, HPAbsorb, HPAbsorb);
    CC_SYNTHESIZE_READONLY(float, ExpRate, ExpRate);
    CC_SYNTHESIZE_READONLY(float, CriRate, CriRate);
    CC_SYNTHESIZE_READONLY(float, CriDam, CriDam);
    
    
    
    
public:
    static ItemData* getItemData(int ItemID);
    
};

#endif /* defined(__MyRPG__ItemData__) */
