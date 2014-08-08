//
//  LevelUpEffect.h
//  MyRPG
//
//  Created by RocLee on 14-8-3.
//
//

#ifndef __MyRPG__LevelUpEffect__
#define __MyRPG__LevelUpEffect__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class LevelUpEffect:public CCNode{
public:
    static LevelUpEffect* sharedlevleupeffect();
    void levelup(CCNode* target);
    void callback(CCNode* pSender);
};

#endif /* defined(__MyRPG__LevelUpEffect__) */
