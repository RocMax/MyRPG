//
//  Equipment.cpp
//  MyRPG
//
//  Created by RocLee on 14-8-28.
//
//

#include "Equipment.h"
#include "ItemData.h"

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
        setupViews();
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


void Equipment::setupViews(){
    CCSprite* player=CCSprite::create(USER_DATA->getPic());
    player->setAnchorPoint(ccp(0,1));
    player->setPosition(ccp(0, getWinsize().height-150));
    player->setScale(2.0f);
    this->addChild(player);
    
    //添加展示装备的CCArray
    CCArray* equipmentsarray=CCArray::create();
    equipmentsarray->retain();
    
    CCDictionary* equipdic=USER_DATA->getEquipments();
    CCDictElement* pelement;
    CCDICT_FOREACH(equipdic, pelement){
        ItemData* item=(ItemData*)pelement->getObject();
        CCLog("pic name:%s",item->getItemPic());
        CCSprite* sprite=CCSprite::create(item->getItemPic());
        sprite->setAnchorPoint(ccp(0, 0));
        sprite->setPosition(ccp(getWinsize().width/3+50, getWinsize().height-100-pelement->getIntKey()*50));
        this->addChild(sprite);
    }
    
//    for (int i=0; i!=8; i++) {
//        ItemData* item=(ItemData*)equipdic->objectForKey(i);
//        CCSprite* sprite=CCSprite::create(item->getItemPic());
//        sprite->setAnchorPoint(ccp(0, 0));
//        sprite->setPosition(ccp(getWinsize().width/3+50, getWinsize().height-100-i*50));
//        this->addChild(sprite);
//        equipmentsarray->addObject(sprite);
//    }
}
