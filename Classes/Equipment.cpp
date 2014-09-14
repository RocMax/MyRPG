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
    //添加主角形象
    CCSprite* player=CCSprite::create(USER_DATA->getPic());
    player->setAnchorPoint(ccp(0,1));
    player->setPosition(ccp(0, getWinsize().height-150));
    player->setScale(2.0f);
    this->addChild(player);
    
    //添加装备和bag的CCArray
    equipmentsarray=CCArray::create();
    bagarray=CCArray::create();
    equipmentsarray->retain();
    bagarray->retain();
    
    
    //注册触摸
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 10, true);
    
    


}

bool Equipment::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    //循环判断点击位置并添加新显示
    CCObject* equipobj;
    CCARRAY_FOREACH(equipmentsarray, equipobj){
        CCSprite* equipsprite=(CCSprite*)equipobj;
        if (equipsprite->boundingBox().containsPoint(pTouch->getLocation())) {
            int tag=equipsprite->getTag();
            switch (tag) {
                case 0:
                    refreshbag(1);
                    break;
                case 1:
                    refreshbag(2);
                    break;
                default:
                    refreshbag(3);
                    break;
            }
        }
    }
    CCObject* bagobj;
    CCARRAY_FOREACH(bagarray, bagobj){
        CCSprite* bagsprite=(CCSprite*)bagobj;
        if (bagsprite->boundingBox().containsPoint(pTouch->getLocation())) {
            CCLOG("item name:%s",((ItemData*)(USER_DATA->getEquipBag()->objectForKey(bagsprite->getTag()-100)))->getItemName());
            
            
        }
    }
    
    
    
    return true;
}


void Equipment::refreshbag(int itemtype){
    //移除当前显示
    CCObject* pobject;
    CCARRAY_FOREACH_REVERSE(bagarray, pobject){
        ((CCSprite*)pobject)->removeFromParent();
    }
    bagarray->removeAllObjects();
    //按照装备类别填充bagarray
    CCDictElement* pelement;
    CCDictionary* bagdic=USER_DATA->getEquipBag();
    int i=0;
    CCDICT_FOREACH(bagdic, pelement){
        ItemData* item=(ItemData*)pelement->getObject();
        if (item->getEquipType()==itemtype) {
            CCSprite* sprite=CCSprite::create(item->getItemPic());
            sprite->setAnchorPoint(ccp(0, 0));
            sprite->setPosition(ccp(i*75, getWinsize().height/3-sprite->getContentSize().height-50));
            sprite->setScale(3.0);
            //100以上的tag给bag使用
            this->addChild(sprite,10,pelement->getIntKey()+100);
            bagarray->addObject(sprite);
            CCLabelTTF* itemnum=CCLabelTTF::create(CCString::createWithFormat("%d", item->getItemcount())->getCString(), "Arial", 10);
            itemnum->setColor(ccRED);
            itemnum->setAnchorPoint(ccp(0, 0));
            sprite ->addChild(itemnum);
            i++;
        }
    }
}

void Equipment::refreshequip(){
    //添加装备栏展示
    CCDictionary* equipdic=USER_DATA->getEquipments();
    CCDictElement* pelement;
    CCDICT_FOREACH(equipdic, pelement){
        ItemData* item=(ItemData*)pelement->getObject();
        CCLog("pic name:%s",item->getItemPic());
        CCSprite* sprite=CCSprite::create(item->getItemPic());
        sprite->setAnchorPoint(ccp(0, 0.5));
        sprite->setPosition(ccp(getWinsize().width/3+50, getWinsize().height-100-pelement->getIntKey()*80));
        sprite->setScale(2.0);
        equipmentsarray->addObject(sprite);
        this->addChild(sprite, 1, pelement->getIntKey());
        CCLOG("sprite tag:%d",sprite->getTag());
        CCLabelTTF* Itemlabel=CCLabelTTF::create(item->getItemName(), "Arial", 25);
        Itemlabel->setAnchorPoint(ccp(0, 0.5));
        Itemlabel->setPosition(ccp(sprite->getPositionX()+100, sprite->getPositionY()));
        this->addChild(Itemlabel);
    }

}