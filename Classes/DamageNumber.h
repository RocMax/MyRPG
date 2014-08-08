//
//  DamageNumber.h
//  MyRPG
//
//  Created by RocLee on 14-7-23.
//
//

#ifndef __MyRPG__DamageNumber__
#define __MyRPG__DamageNumber__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;

class DamageNumber:public CCNode{
public:
    static DamageNumber* damagenumber;
    static DamageNumber* shareddamagenumber();
    void getDanageEffect(CCNode* target,bool isCritical,float damage);
    void callback(CCNode* pSender);
    
};
#endif /* defined(__MyRPG__DamageNumber__) */
