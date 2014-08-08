//
//  AttackEffect.cpp
//  TiledMapTest
//
//  Created by RocLee on 14-6-17.
//
//

#include "AttackEffect.h"

static AttackEffect* instance=NULL;

AttackEffect* AttackEffect::atkeffect(){
    if (!instance) {
        instance=new AttackEffect();
    }

    return instance;
}

void AttackEffect::preload(){
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("edge.plist");
    CCAnimation* atkanimation=CCAnimation::create();
    atkanimation->setDelayPerUnit(0.1f);
    atkanimation->setLoops(1);
    
    //添加每一帧
    for (int i=1; i!=3; i++) {
        char str[20]={0};
        sprintf(str, "edge0%d.png",i);
        CCSpriteFrame* frame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
        atkanimation->addSpriteFrame(frame);
        
    }

    CCAnimationCache::sharedAnimationCache()->addAnimation(atkanimation, "atk");
}

void AttackEffect::attack(cocos2d::CCNode *target, cocos2d::CCPoint position){
    CCSprite* sp=CCSprite::createWithSpriteFrameName("edge01.png");
    target->addChild(sp,50);
    sp->setPosition(position);
    CCAnimation* atkanimation=CCAnimationCache::sharedAnimationCache()->animationByName("atk");
    CCAnimate* atkanimate=CCAnimate::create(atkanimation);
    
    CCCallFuncN* callback=CCCallFuncN::create(sp, callfuncN_selector(AttackEffect::callback));
    
    CCAction* pAction=CCSequence::create(atkanimate,callback,NULL);
    sp->runAction(pAction);
    
}

void AttackEffect::callback(cocos2d::CCNode *pNode){
    pNode->removeFromParentAndCleanup(true);
}