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

Equipment::~Equipment(){
    equipmentsarray->release();
    bagarray->release();
}

CCSize Equipment::getWinsize(){
    return CCDirector::sharedDirector()->getWinSize();
}

void Equipment::draw(){
    ccDrawLine(ccp(getWinsize().width/3,getWinsize().height/3+150), ccp(getWinsize().width/3, getWinsize().height));
    CHECK_GL_ERROR_DEBUG();
    ccDrawLine(ccp(0,getWinsize().height/3+150), ccp(getWinsize().width, getWinsize().height/3+150));
    CHECK_GL_ERROR_DEBUG();
    ccDrawLine(ccp(0, getWinsize().height/5), ccp(getWinsize().width, getWinsize().height/5));
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
    
    //装备栏展示
    refreshequip();
    
    //注册触摸
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 10, true);

    //装备介绍
    ItemIntro=CCLabelTTF::create();
    ItemIntro->setScale(2.5f);
    ItemIntro->setDimensions(CCSizeMake(1000, 0));
    ItemIntro->setAnchorPoint(ccp(0, 1));
    ItemIntro->setPosition(ccp(20, getWinsize().height/5-20));
    this->addChild(ItemIntro);
    
    CCLabelBMFont* equiplabel=CCLabelBMFont::create("Equip", "myfont1.fnt");
    CCMenuItemLabel* equipitemlabel=CCMenuItemLabel::create(equiplabel, this, menu_selector(Equipment::equipmenucallback));
    CCLabelBMFont* oklabel=CCLabelBMFont::create("OK", "myfont1.fnt");
    CCMenuItemLabel* okitemlabel=CCMenuItemLabel::create(oklabel, this, menu_selector(Equipment::okmenucallback));
    
    CCMenu* menu=CCMenu::create(equipitemlabel,okitemlabel,NULL);
    menu->alignItemsHorizontallyWithPadding(30);
    menu->setAnchorPoint(ccp(0, 0));
    menu->setPosition(ccp(500, 50));
    this->addChild(menu);

}

bool Equipment::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    //循环判断点击位置并添加新显示
    CCObject* equipobj;
    CCARRAY_FOREACH(equipmentsarray, equipobj){
        CCSprite* equipsprite=(CCSprite*)equipobj;
        if (equipsprite->boundingBox().containsPoint(pTouch->getLocation())) {
            equipflag=equipsprite->getTag();
            CCLOG("equipflag:%d",equipflag);
            switch (equipflag) {
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
            ItemIntro->setString(ItemData::getItemData(bagsprite->getTag()-100)->getIntroduction());
            touchitemid=bagsprite->getTag()-100;
            CCLOG("touchitemid:%d",touchitemid);
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
            sprite->setPosition(ccp(i*75, getWinsize().height/3-sprite->getContentSize().height+100));
            sprite->setScale(3.0);
            //100以上的tag给bag使用,由于bag里的装备不存在重复可能,直接用itemid+100作为tag
            this->addChild(sprite,10,item->getItemID()+100);
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
    //移除当前显示
    if (equipmentsarray!=NULL) {
        CCObject* pobject;
        CCARRAY_FOREACH_REVERSE(equipmentsarray, pobject){
            ((CCSprite*)pobject)->removeFromParent();
        }
        equipmentsarray->removeAllObjects();
    }
    
    //添加装备栏展示
    CCDictionary* equipdic=USER_DATA->getEquipments();
    CCDictElement* pelement;
    CCDICT_FOREACH(equipdic, pelement){
        ItemData* item=(ItemData*)pelement->getObject();
        CCLog("pic name:%s",item->getItemPic());
        CCSprite* sprite=CCSprite::create(item->getItemPic());
        sprite->setAnchorPoint(ccp(0, 0.5));
        sprite->setPosition(ccp(getWinsize().width/3+50, getWinsize().height-100-pelement->getIntKey()*60));
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

void Equipment::equipmenucallback(cocos2d::CCObject *pSender){
    CCLOG("equipflag:%d  touchitemid:%d",equipflag,touchitemid);
    changeequipment(equipflag, touchitemid);
    refreshequip();
    switch (equipflag) {
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

void Equipment::okmenucallback(cocos2d::CCObject *pSender){
    
}

void Equipment::changeequipment(int equipflag, int itemid){
    //背包内itemid的装备-1
    changebag(itemid, false);
    //取equipflag对应装备的信息
    ItemData* item=(ItemData*)(USER_DATA->getEquipments()->objectForKey(equipflag));
    //背包内对应equipflag的装备+1
    changebag(item->getItemID(), true);
    //equipflag的装备设置为itemid
    USER_DATA->getEquipments()->setObject(ItemData::getItemData(itemid), equipflag);
}

//背包变更函数,isadd区分是加一件装备还是减一件装备至背包,加装备时判定是否已存在,存在则加数量,不存在则新建项.减装备时先减数量,减完为0的话删除此项.
void Equipment::changebag(int itemid, bool isadd){
    CCDictionary* bagdic=USER_DATA->getEquipBag();
    CCDictElement* pelement;
    if (isadd) {
        bool isexistinbag=false;
        CCDICT_FOREACH(bagdic, pelement){
            ItemData* item=(ItemData*)pelement;
            if (item->getItemID()==itemid) {
                item->setItemcount(item->getItemcount()+1);
                isexistinbag=true;
            }
        }
        if (isexistinbag==false) {
            bagdic->setObject(ItemData::getItemData(itemid), bagdic->count());
        }
    }
    else {
        CCDICT_FOREACH(bagdic, pelement){
            ItemData* item=(ItemData*)pelement;
            CCLOG("itemid:%d",item->getItemID());
            if (item->getItemID()==itemid) {
                item->setItemcount(item->getItemcount()-1);
                if (item->getItemcount()==0) {
                    bagdic->removeObjectForKey(pelement->getIntKey());
                }
            }
        }
        
    }
}
