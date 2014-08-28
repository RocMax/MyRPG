//
//  Equipment.cpp
//  MyRPG
//
//  Created by RocLee on 14-8-28.
//
//

#include "Equipment.h"

CCScene* Equipment::scene(){
    CCScene* pScene=CCScene::create();
    Equipment* pLayer=Equipment::create();
    pScene->addChild(pLayer);
    return pScene;
    
}

bool Equipment::init(){
    bool sRect=false;
    do {
        CC_BREAK_IF(!CCLayer::init());
        ud=UserData::LoadUserData();
        sRect=true;
    } while (0);
    return sRect;
}

CCSize Equipment::getWinsize(){
    return CCDirector::sharedDirector()->getWinSize();
}

void Equipment::draw(){
    ccDrawLine(ccp(getWinsize().width/3,getWinsize().height/3), ccp(getWinsize().width/3, getWinsize().height));
    CHECK_GL_ERROR_DEBUG();
    ccDrawLine(ccp(0,getWinsize().height/3), ccp(getWinsize().width, getWinsize().height/3));
    CHECK_GL_ERROR_DEBUG();
}

void Equipment::onEnter(){
    CCLayer::onEnter();
    setupViews();
}

void Equipment::setupViews(){
    CCSprite* player=CCSprite::create(ud->getPic());
    player->setAnchorPoint(ccp(0,1));
    player->setPosition(ccp(0, getWinsize().height-150));
    player->setScale(2.0f);
    this->addChild(player);
}
