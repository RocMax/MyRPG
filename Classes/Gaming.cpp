//
//  Gaming.cpp
//  MyRPG
//
//  Created by RocLee on 14-7-4.
//
//

#include "Gaming.h"
#include "Battle.h"
#include "Equipment.h"

bool Gaming::init(){
    bool sRect=false;
    do {
        CC_BREAK_IF(!CCLayer::init());
        SetupViews();
        sRect=true;
    } while (0);
    return sRect;
}

CCScene* Gaming::scene(){
    CCScene* scene=CCScene::create();
    Gaming* layer=Gaming::create();
    scene->addChild(layer);
    
    return scene;
}

void Gaming::SetupViews(){
//    ud=UserData::LoadUserData();
//    ud->RefreshUserData();
    USER_DATA->LoadUserData();
    USER_DATA->RefreshUserData();
    
    CCLog("equipment:%s  bag:%s",USER_DEFAULT->getStringForKey("Equipments").c_str(),USER_DEFAULT->getStringForKey("EquipBag").c_str());

    //生成地图
    tiledMap=CCTMXTiledMap::create(USER_DATA->getMap());
    tiledMap->setAnchorPoint(CCPointZero);
    tiledMap->setPosition(ccp(USER_DATA->getMapOffsetX(), USER_DATA->getMapOffsetY()));
    this->addChild(tiledMap);
    //生成player
    player=CCSprite::create(USER_DATA->getPic());
    player->setScale(0.5f);
    player->setPosition(ccp(USER_DATA->getPositionX(), USER_DATA->getPositionY()));
    tiledMap->addChild(player,10);
    //获取meta层
    metaLayer=tiledMap->layerNamed("Meta");
    metaLayer->setVisible(false);
    //获取level层
    levelLayer=tiledMap->layerNamed("Level");
    levelLayer->setVisible(false);
    //注册触摸
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 10, true);
    //控制移动的schedule
    this->scheduleUpdate();
    //控制遇怪的schedule
    this->schedule(schedule_selector(Gaming::EncounterMonster), 1.0f);
    
    //初始化遇怪数值
    Battle::setRandomSeed();
    EncounterNum=(CCRANDOM_0_1()*100)*(1+USER_DATA->getFinal_EncounterRate());
    CCLog("encounternum=%f",EncounterNum);
    
    //GameTimes
    CCLabelBMFont* Gametimeslable=CCLabelBMFont::create("GameTimes :", "myfont1.fnt");
    Gametimeslable->setAnchorPoint(ccp(1, 1));
    Gametimeslable->setPosition(ccp(GetWinSize().width-100, GetWinSize().height-20));
    this->addChild(Gametimeslable);
    CCLabelAtlas* Gametimesnum=CCLabelAtlas::create(Battle::IntToChar( USER_DATA->getGameTimes()), "number.png", 24, 34, 48);
    Gametimesnum->setAnchorPoint(ccp(0, 1));
    Gametimesnum->setPosition(ccp(Gametimeslable->getPositionX()+20, Gametimeslable->getPositionY()-20));
    this->addChild(Gametimesnum,50,30);
    
    //添加遇怪条
    CCSprite* enbarbg=CCSprite::create("BarBox.png");
    enbarbg->setAnchorPoint(ccp(1,0));
    enbarbg->setPosition(ccp(GetWinSize().width-20, 20));
    this->addChild(enbarbg);
    CCSprite* enBarSprite=CCSprite::create("whitebar.png");
    CCProgressTimer* enBar=CCProgressTimer::create(enBarSprite);
    enBar->setType(kCCProgressTimerTypeBar);
    enBar->setAnchorPoint(ccp(1, 0));
    enBar->setPosition(ccp(GetWinSize().width-20, 20));
    enBar->setMidpoint(ccp(0, 0.5));
    enBar->setBarChangeRate(ccp(1, 0));
//    enBar->setPercentage(100);
    this->addChild(enBar,50,31);
    
    //添加换装界面按钮
    CCLabelBMFont* Equipments=CCLabelBMFont::create("Equipments", "myfont1.fnt");
    CCMenuItemLabel* Equipmentsmenuitem=CCMenuItemLabel::create(Equipments, this, menu_selector(Gaming::EquipmentsMenucallback));
    CCMenu* menu=CCMenu::create();
    menu->addChild(Equipmentsmenuitem);
    menu->setAnchorPoint(ccp(0.5, 0));
    menu->setPosition(ccp(GetWinSize().width/3, 50));
    this->addChild(menu);

}

CCSize Gaming::GetWinSize(){
    return CCDirector::sharedDirector()->getWinSize();
}

bool Gaming::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    touchFlag=true;//设置触摸标记
    targetPoint=convertToWorldSpace(pTouch->getLocation());//将触摸点转为世界坐标
    return true;
}

void Gaming::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){
    targetPoint=convertToWorldSpace(pTouch->getLocation());
}

void Gaming::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){
    touchFlag=false;//触摸停止
}

//在触摸标记为真的情况下移动Player
void Gaming::update(float t){
    CCPoint playerPosition=convertToWorldSpace(player->getPosition());
    tiledMap->setPosition(getOffset(playerPosition));
    if (touchFlag) {
        movePlayer(targetPoint,t);
        //设置遇怪条
        CCProgressTimer* enbar=(CCProgressTimer*)this->getChildByTag(31);
        enbar->setPercentage(enbar->getPercentage()+10*t);

        if (enbar->getPercentage()<=30) {
            enbar->setColor(ccGREEN);
        }
        else if (enbar->getPercentage()>30&&enbar->getPercentage()<=60) {
            enbar->setColor(ccYELLOW);
        
        }
        else if (enbar->getPercentage()>60){
            enbar->setColor(ccRED);
        }
    }
    
}

//计算地图的偏移量
CCPoint Gaming::getOffset(CCPoint viewPoint){
    float x=MAX(viewPoint.x, GetWinSize().width/2);
    float y=MAX(viewPoint.y, GetWinSize().height/2);
    x=MIN(x, (tiledMap->getMapSize().width*tiledMap->getTileSize().width)-GetWinSize().width/2);
    y=MIN(y, (tiledMap->getMapSize().height*tiledMap->getTileSize().height)-GetWinSize().height/2);
    CCPoint mapOffset=ccpSub(ccp(GetWinSize().width/2, GetWinSize().height/2),ccp(x, y));
    return mapOffset;
}

//移动Player
void Gaming::movePlayer(CCPoint targetpos,float t){
    CCPoint curpos=ccpAdd(player->getPosition(), getOffset(player->getPosition()));
    float speed=USER_DATA->getFinal_MoveSpeed();
    if (ccpDistance(curpos, targetpos)>speed) {
        CCPoint normvector=ccpNormalize(ccp(targetpos.x-curpos.x, targetpos.y-curpos.y));
        CCPoint nextposition=ccpSub(ccp(curpos.x+normvector.x*speed, curpos.y+normvector.y*speed), getOffset(player->getPosition()));
        CCPoint nextTiledCoord=getTiledCoord(nextposition);
        
        if (isReachable(nextTiledCoord)) {
            player->setPosition(nextposition);
            USER_DATA->setMapArea(getMapLevel(nextTiledCoord));
        }

        
    }
}

CCPoint Gaming::getTiledCoord(cocos2d::CCPoint position){
    //将坐标转换成瓦片地图中的坐标
    int x =position.x / tiledMap->getTileSize().width;
    int y = ((tiledMap->getMapSize().height * tiledMap->getTileSize().height) - position.y) / tiledMap->getTileSize().height;
    
    CCPoint tileCoord = ccp(x,y);
    return tileCoord;
//    CCLog("tilecoord:%f,%f",tileCoord.x,tileCoord.y);
//    unsigned int tileGid =metaLayer->tileGIDAt(tileCoord);
//    return tileGid;
//    CCLog("GID:%d",tileGid);

    
}

bool Gaming::isReachable(cocos2d::CCPoint tileCoord){
    unsigned int MapGID =metaLayer->tileGIDAt(tileCoord);
    CCDictionary *properties = tiledMap->propertiesForGID(MapGID);
    if (properties)
    {
        const CCString *collision = properties->valueForKey("collidable");
        
        if (collision && (collision->compare("true") ==0)){
            return false;
        }
    }
    else return true;
}

int Gaming::getMapLevel(cocos2d::CCPoint tileCoord){
    unsigned int MapGID =levelLayer->tileGIDAt(tileCoord);
    CCDictionary *properties = tiledMap->propertiesForGID(MapGID);
    if (properties)
    {
        const CCString *collision = properties->valueForKey("Level");
        return collision->intValue();
        }
    else {
        return 0;
        CCLOG("no maplevel");
    }
    
}

void Gaming::EncounterMonster(float t){
    if (touchFlag) {
        EncounterNum-=10;
        if (EncounterNum<=0) {
            this->pauseSchedulerAndActions();
            //添加battle层
            Battle* btlayer=Battle::create();
            this->addChild(btlayer, 50, 11);
            btlayer->ignoreAnchorPointForPosition(false);
            btlayer->setAnchorPoint(ccp(0.5,0.5));
            btlayer->setPosition(ccp(GetWinSize().width/2,GetWinSize().height/2));
            touchFlag=false;
        }
        
    }
    
}

void Gaming::onEnter(){
    CCLayer::onEnter();
    battlelayerexited="BattleLayerExited";
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(Gaming::btlayerExitObserver), battlelayerexited, NULL);
    touchFlag=false;
    
}

void Gaming::onExit(){
//    USER_DATA->SaveUserData();
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, battlelayerexited);
    CCLayer::onExit();
    
}

void Gaming::btlayerExitObserver(){
    if (this->getChildByTag(11)!=NULL) {
        this->removeChildByTag(11, true);
    }
    
    //刷新userdata
//    USER_DATA->LoadUserData();
    USER_DATA->RefreshUserData();
    refreshGameTimes();
    EncounterNum=(CCRANDOM_0_1()*100)*(1+USER_DATA->getFinal_EncounterRate());
    CCLOG("new encounternum=%f",EncounterNum);
    this->resumeSchedulerAndActions();
    CCProgressTimer* enbar=(CCProgressTimer*)this->getChildByTag(31);
    enbar->setPercentage(0);

    
}

void Gaming::refreshGameTimes(){
    CCLabelAtlas* gametimeslabel=(CCLabelAtlas*)this->getChildByTag(30);
    gametimeslabel->setString(Battle::IntToChar(USER_DATA->getGameTimes()));
}

void Gaming::EquipmentsMenucallback(cocos2d::CCObject *pSender){
//    USER_DATA->SaveUserData();
    CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f,Equipment::scene()));
}