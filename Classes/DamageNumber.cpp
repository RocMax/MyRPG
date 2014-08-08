//
//  DamageNumber.cpp
//  MyRPG
//
//  Created by RocLee on 14-7-23.
//
//

#include "DamageNumber.h"
static DamageNumber* instance=NULL;

DamageNumber* DamageNumber::shareddamagenumber(){
    if (!instance) {
        instance=new DamageNumber();
    }
    return instance;
}

void DamageNumber::getDanageEffect(cocos2d::CCNode *target, bool isCritical, float damage){
    CCString* damagestring=CCString::createWithFormat(":%d",(int)damage);
    CCLabelAtlas* damageeffect=CCLabelAtlas::create(damagestring->getCString(), "number.png", 24, 34, 48);
    damageeffect->setAnchorPoint(ccp(0.5, 0.5));
//    damageeffect->setPosition(ccp(target->getPositionX()+target->getContentSize().width/2 , target->getPositionY()+target->getContentSize().height*1.5));
    damageeffect->setPosition(ccp(target->getPositionX() , target->getPositionY()+damageeffect->getContentSize().height+50));
//    CCLOG("damage number position:%f,%f",damageeffect->getPositionX(),damageeffect->getPositionY());
    
    
    ccBezierConfig bezier;
    bezier.controlPoint_1=ccp(0,10);
    bezier.controlPoint_2=ccp(20,20);
//    bezier.endPosition=ccp(0, target->getContentSize().height*1.5);
    CCBezierBy* pBezier=CCBezierBy::create(2.0f, bezier);
    
    CCFadeOut* pFadeout=CCFadeOut::create(2.0f);
    CCScaleBy* pScaleby=CCScaleBy::create(2.0f, 1.5f);
    
    CCFiniteTimeAction* pSpawnaction=CCSpawn::create(pBezier,pFadeout,pScaleby,NULL);
    CCCallFuncN* actioncallback=CCCallFuncN::create(this, callfuncN_selector(DamageNumber::callback));
    CCActionInterval* paction=CCSequence::create(pSpawnaction,actioncallback,NULL);
    target->getParent()->addChild(damageeffect,10);
    if (isCritical) {
        CCSprite* criticalbg=CCSprite::create("critical.png");
        criticalbg->setAnchorPoint(ccp(0.5,0.5));
        criticalbg->setPosition(ccp(damageeffect->getPositionX() , damageeffect->getPositionY()));
        criticalbg->setScale(damageeffect->getContentSize().width/criticalbg->getContentSize().width+0.2);
        target->getParent()->addChild(criticalbg,5);
        criticalbg->runAction((CCAction*)paction->copy()->autorelease());
    }
    damageeffect->runAction(paction);
    
}

void DamageNumber::callback(cocos2d::CCNode *pSender){
    pSender->removeFromParentAndCleanup(true);

}