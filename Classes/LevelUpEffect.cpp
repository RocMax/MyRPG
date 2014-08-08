//
//  LevelUpEffect.cpp
//  MyRPG
//
//  Created by RocLee on 14-8-3.
//
//

#include "LevelUpEffect.h"

static LevelUpEffect* instance=NULL;

LevelUpEffect* LevelUpEffect::sharedlevleupeffect(){
    if (!instance) {
        instance=new LevelUpEffect();
    }
    return instance;
}

void LevelUpEffect::levelup(cocos2d::CCNode *target){
    CCSprite* slvup=CCSprite::create("LevelUP.png");
    slvup->setPosition(ccp(target->getPositionX(), target->getPositionY()+target->getContentSize().height/2+30));
    target->getParent()->addChild(slvup);
    CCMoveBy* levelupmoveby=CCMoveBy::create(0.5, ccp(0, 50));
    CCFadeOut* levelupfadeout=CCFadeOut::create(0.5);
    CCFiniteTimeAction* levelupspawn=CCSpawn::create(levelupmoveby,levelupfadeout,NULL);
    CCCallFuncN* levelupcallback=CCCallFuncN::create(this, callfuncN_selector(LevelUpEffect::callback));
    CCActionInterval* levelupaction=CCSequence::create(levelupspawn,levelupcallback,NULL);
    slvup->runAction(levelupaction);
}

void LevelUpEffect::callback(cocos2d::CCNode *pSender){
    pSender->removeFromParentAndCleanup(true);
}