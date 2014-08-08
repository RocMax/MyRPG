//
//  Start.cpp
//  MyRPG
//
//  Created by RocLee on 14-7-25.
//
//

#include "Start.h"
#include "Home.h"

CCScene* Start::scene(){
    CCScene* pScene=CCScene::create();
    CCLayer* pLayer=Start::create();
    pScene->addChild(pLayer);
    return pScene;
}

bool Start::init(){
    bool sRect=false;
    do {
        CC_BREAK_IF(!CCLayer::init());
        setupViews();
        sRect=true;
    } while (0);
    return sRect;
}

void Start::setupViews(){
    CCSprite* simaqian=CCSprite::create("SimaQian.png");
    simaqian->setAnchorPoint(ccp(0.5, 1));
    simaqian->setPosition(ccp(getWinsize().width/2, getWinsize().height));
    simaqian->setScale(0.5f);
    simaqian->setOpacity(0);
    this->addChild(simaqian);
    
    CCFadeIn* fadein=CCFadeIn::create(2.0);
    simaqian->runAction(CCSequence::create(fadein,CCDelayTime::create(3),fadein->reverse(),NULL));
    
    const char* story="司马迁，字子长\n著史记。\n完成史记后隐居山野不知所踪。\n对于司马迁的死，历史上没有明确记载，卒年无法确定，死因也众说纷纭。";
    
    CCLabelTTF* storylabel=CCLabelTTF::create(story, "Arial", 30);
    storylabel->setDimensions(CCSizeMake(600, 0));
    storylabel->setHorizontalAlignment(kCCTextAlignmentLeft);
    storylabel->setAnchorPoint(ccp(0.5, 1));
    storylabel->setPosition(ccp(getWinsize().width/2, 0));
    this->addChild(storylabel);
    CCMoveTo* labelmove=CCMoveTo::create(5, ccp(getWinsize().width/2, getWinsize().height-simaqian->getContentSize().height));
    CCCallFunc* labelcallback=CCCallFunc::create(this, callfunc_selector(Start::callback));
    CCAction* labelaction=CCSequence::create(labelmove,fadein->reverse(),labelcallback,NULL);
    storylabel->runAction(labelaction);
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, INT_MIN, true);
}

CCSize Start::getWinsize() {
    return CCDirector::sharedDirector()->getWinSize();
}

void Start::callback() {
    this->removeAllChildren();
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.5f,Home::scene()));
}

bool Start::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    this->removeAllChildren();
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.5f,Home::scene()));
    return true;
}

void Start::onExit(){
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCLayer::onExit();
}