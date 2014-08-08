//
//  AttackEffect.h
//  TiledMapTest
//
//  Created by RocLee on 14-6-17.
//
//

#ifndef __TiledMapTest__AttackEffect__
#define __TiledMapTest__AttackEffect__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class AttackEffect:public CCNode{
public:
    static AttackEffect* atkeffect();
    void preload();
    void attack(CCNode* target,CCPoint position);
    void callback(CCNode* pNode);
};

#endif /* defined(__TiledMapTest__AttackEffect__) */
