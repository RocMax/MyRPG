//
//  Status.cpp
//  MyRPG
//
//  Created by RocLee on 14-8-5.
//
//

#include "Status.h"
#include "Battle.h"


CCScene* Status::scene(){
    CCScene* pScene=CCScene::create();
    CCLayer* pLayer=Status::create();
    pScene->addChild(pLayer);
    return pScene;
}

bool Status::init(){
    bool sRect=false;
    do {
        CC_BREAK_IF(!CCLayer::init());
//        setupViews();
        ud=UserData::LoadUserData();
        sRect=true;
    } while (0);
    return sRect;
}

void Status::onEnter(){
    CCLayer::onEnter();
    setupViews();
}

void Status::draw(){
    CCSize winsize=CCDirector::sharedDirector()->getWinSize();
    ccDrawLine(ccp(0, winsize.height*3/4), ccp(winsize.width, winsize.height*3/4));
    
    CHECK_GL_ERROR_DEBUG();
}

CCSize Status::getWinsize(){
    return CCDirector::sharedDirector()->getWinSize();
}

void Status::setupViews(){
    CCSprite* player=CCSprite::create(ud->getPic());
    player->setPosition(ccp(player->getContentSize().width/2+50, getWinsize().height-player->getContentSize().height/2-100));
    player->setScale(2.0f);
    this->addChild(player);
    
    CCString* stringlevel=CCString::createWithFormat("LEVEL :%d",ud->getLevel());
    CCLabelBMFont* level=CCLabelBMFont::create(stringlevel->getCString(), "myfont1.fnt");
    level->setPosition(ccp(getWinsize().width/2+30, getWinsize().height-100));
    this->addChild(level);
    CCLabelBMFont* pointlabel=CCLabelBMFont::create("SparePoint :", "myfont1.fnt");
    pointlabel->setPosition(ccp(getWinsize().width/2+30, getWinsize().height-200));
    this->addChild(pointlabel);
    
    CCLabelAtlas* sparepoint=CCLabelAtlas::create(Battle::IntToChar(ud->getSparePoint()), "number.png", 24, 34, 48);
    sparepoint->setPosition(ccp(getWinsize().width/2+pointlabel->getContentSize().width/2+50, getWinsize().height-220));
    this->addChild(sparepoint);
    
    
    
    
}