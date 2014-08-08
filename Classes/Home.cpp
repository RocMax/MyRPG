//
//  Home.cpp
//  MyRPG
//
//  Created by RocLee on 14-7-27.
//
//

#include "Home.h"
#include "SelectHero.h"

CCScene* Home::scene(){
    CCScene* pScene=CCScene::create();
    CCLayer* pLayer=Home::create();
    pScene->addChild(pLayer);
    return pScene;
}

bool Home::init(){
    bool sRect=false;
    do {
        CC_BREAK_IF(!CCLayer::init());
        setupViews();
        sRect=true;
    } while (0);
    return sRect;
}

CCSize Home::getWinsize(){
    return CCDirector::sharedDirector()->getWinSize();
}

void Home::setupViews(){
    CCSprite* bg=CCSprite::create("home.png");
    bg->setAnchorPoint(ccp(0, 0));
    bg->setPosition(ccp(0,0));
    this->addChild(bg, 1);
    
    CCMenu* pMenu=CCMenu::create();
    
    CCLabelTTF* plabelstory=CCLabelTTF::create("剧情", "Arial", 50);
    CCLabelTTF* plabelattack=CCLabelTTF::create("出击", "Arial", 50);
    CCLabelTTF* plabelhistory=CCLabelTTF::create("历史", "Arial", 50);
    
    CCMenuItem* pitemstory=CCMenuItemLabel::create(plabelstory, this, menu_selector(Home::storymenucallback));
    CCMenuItem* pitemattack=CCMenuItemLabel::create(plabelattack, this, menu_selector(Home::attackmenucallback));
    CCMenuItem* pitemhistory=CCMenuItemLabel::create(plabelhistory, this, menu_selector(Home::historymenucallback));
    
    pMenu->addChild(pitemstory);
    pMenu->addChild(pitemattack);
    pMenu->addChild(pitemhistory);
    
    pMenu->alignItemsHorizontallyWithPadding(50);
    
    pMenu->setAnchorPoint(ccp(0.5, 0));
    pMenu->setPosition(ccp(getWinsize().width/2, 250));
    
    this->addChild(pMenu,10);
}

void Home::storymenucallback(CCObject *pSender){
    
}
void Home::attackmenucallback(CCObject *pSender){
    CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f,SelectHero::scene()));
    
    CCLOG("Game Start");

    
}
void Home::historymenucallback(CCObject *pSender){
    
}