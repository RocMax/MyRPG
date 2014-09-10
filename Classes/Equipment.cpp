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
//    USER_DATA->RefreshUserData();
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
        sprite->setAnchorPoint(ccp(0, 0.5));
        sprite->setPosition(ccp(getWinsize().width/3+50, getWinsize().height-100-pelement->getIntKey()*80));
        sprite->setScale(1.5);
        equipmentsarray->addObject(sprite);
        this->addChild(sprite);
        
        CCLabelTTF* Itemlabel=CCLabelTTF::create(item->getItemName(), "Arial", 25);
        Itemlabel->setAnchorPoint(ccp(0, 0.5));
        Itemlabel->setPosition(ccp(sprite->getPositionX()+100, sprite->getPositionY()));
        this->addChild(Itemlabel);
    }
    

}
