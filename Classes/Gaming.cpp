//
//  Gaming.cpp
//  MyRPG
//
//  Created by RocLee on 14-7-4.
//
//

#include "Gaming.h"
#include "Battle.h"

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
    ud=UserData::LoadUserData();
    ud->RefreshUserData();
    ud->retain();

    //生成地图
    tiledMap=CCTMXTiledMap::create(ud->getMap());
    tiledMap->setAnchorPoint(CCPointZero);
    tiledMap->setPosition(ccp(ud->getMapOffsetX(), ud->getMapOffsetY()));
    this->addChild(tiledMap);
    //生成player
    player=CCSprite::create(ud->getPic());
    player->setScale(0.5f);
    player->setPosition(ccp(ud->getPositionX(), ud->getPositionY()));
    tiledMap->addChild(player,10);
    //获取meta层
    metaLayer=tiledMap->layerNamed("Meta");
    metaLayer->setVisible(false);
    //获取level层
    levelLayer=tiledMap->layerNamed("Level");
    levelLayer->setVisible(true);
    //注册触摸
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 10, true);
    //控制移动的schedule
    this->scheduleUpdate();
    //控制遇怪的schedule
    this->schedule(schedule_selector(Gaming::EncounterMonster), 1.0f);
    
    //初始化遇怪数值
    Battle::setRandomSeed();
    EncounterNum=(CCRANDOM_0_1()*100)*ud->getEncounterNum_a()+ud->getEncounterNum_b();
    CCLog("encounternum=%f ,a=%f,b=%f",EncounterNum,ud->getEncounterNum_a(),ud->getEncounterNum_b());
    
    
    
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
    float speed=ud->getMoveSpeed()*ud->getMultipleSpeed();
    if (ccpDistance(curpos, targetpos)>speed) {
        CCPoint normvector=ccpNormalize(ccp(targetpos.x-curpos.x, targetpos.y-curpos.y));
        CCPoint nextposition=ccpSub(ccp(curpos.x+normvector.x*speed, curpos.y+normvector.y*speed), getOffset(player->getPosition()));
        CCPoint nextTiledCoord=getTiledCoord(nextposition);
        
        if (isReachable(nextTiledCoord)) {
            player->setPosition(nextposition);
            ud->setMapArea(getMapLevel(nextTiledCoord));
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
            Battle* btlayer=Battle::createWithData(ud);
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
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, battlelayerexited);
    CCLayer::onExit();
    
}

void Gaming::btlayerExitObserver(){
    if (this->getChildByTag(11)!=NULL) {
        this->removeChildByTag(11, true);
    }
    
    //刷新userdata
    ud=UserData::LoadUserData();
    ud->RefreshUserData();
    
    EncounterNum=(CCRANDOM_0_1()*100)*ud->getEncounterNum_a()+ud->getEncounterNum_b();
    CCLOG("new encounternum=%f",EncounterNum);
    this->resumeSchedulerAndActions();
    
}

