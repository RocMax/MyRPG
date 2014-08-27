//
//  Battle.cpp
//  MyRPG
//
//  Created by RocLee on 14-7-19.
//
//

#include "Battle.h"
#include "AttackEffect.h"
#include "CCShake.h"
#include "DamageNumber.h"
#include "LevelUpEffect.h"
#include "Status.h"

Battle* Battle::createWithData(UserData *ud){
    Battle* pRet=new Battle();
    if (pRet&&pRet->initWithData(ud)) {
        pRet->autorelease();
        return pRet;
    }
    else{
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}


bool Battle::initWithData(UserData *ud){
    bool sRect=false;
    do {
        CC_BREAK_IF(!CCLayer::init());
        setupViewsWithData(ud);
        sRect=true;
    } while (0);
    return sRect;
    
}

Battle::~Battle(){
    
}

CCSize Battle::GetWinSize(){
    return CCDirector::sharedDirector()->getWinSize();
}

void Battle::setupViewsWithData(UserData *ud){
    userdata=ud;
    blackbg=CCSprite::create("black.png");
    blackbg->setScale(1.3);
    blackbg->setAnchorPoint(ccp(0.5, 0.5));
    blackbg->setPosition(ccp(GetWinSize().width/2, GetWinSize().height/2));
    blackbg->setOpacity(255);
    this->addChild(blackbg);
    
    player=CCSprite::create(ud->getPic());
    blackbg->addChild(player, 1, 11);
    player->setAnchorPoint(ccp(0.5, 0.5));
    player->setPosition(ccp(blackbg->getContentSize().width/2,blackbg->getContentSize().height/4));
    
    pHP=userdata->getFinal_HP();
    //添加player血条
    CCSprite* pHPBarbg=CCSprite::create("BarBox.png");
    pHPBarbg->setAnchorPoint(ccp(0.5, 0.5));
    pHPBarbg->setPosition(ccp(blackbg->getContentSize().width/2,blackbg->getContentSize().height/4-50));
    blackbg->addChild(pHPBarbg,1,13);
    CCSprite* pHPBarSprite=CCSprite::create("HPbar.png");
    pHPBar=CCProgressTimer::create(pHPBarSprite);
    pHPBar->setType(kCCProgressTimerTypeBar);
    pHPBar->setAnchorPoint(ccp(0.5, 0.5));
    pHPBar->setPosition(ccp(blackbg->getContentSize().width/2,blackbg->getContentSize().height/4-50));
    pHPBar->setMidpoint(ccp(0, 0.5));
    pHPBar->setBarChangeRate(ccp(1, 0));
    pHPBar->setPercentage(100);      //一定要设置百分比,默认为0,不显示
    blackbg->addChild(pHPBar,1,12);
    
    
    //获取Monster数据
    mm=MonsterManager::GetMonster(ud->getMapArea());
    mm->retain();
//    CCLOG(mm->getM_Pic());
    monster=CCSprite::create(mm->getM_Pic());
    monster->setAnchorPoint(ccp(0.5, 0.5));
    monster->setPosition(ccp(blackbg->getContentSize().width/2,blackbg->getContentSize().height/4*3));
    blackbg->addChild(monster,1,21);
    
    mHP=mm->getM_HP();
    //添加Monster血条
    CCSprite* mHPBarbg=CCSprite::create("BarBox.png");
    mHPBarbg->setAnchorPoint(ccp(0.5, 0.5));
    mHPBarbg->setPosition(ccp(blackbg->getContentSize().width/2,blackbg->getContentSize().height/4*3-60));
    blackbg->addChild(mHPBarbg,1,23);
    CCSprite* mHPBarSprite=CCSprite::create("HPbar.png");
    mHPBar=CCProgressTimer::create(mHPBarSprite);
    mHPBar->setType(kCCProgressTimerTypeBar);
    mHPBar->setAnchorPoint(ccp(0.5, 0.5));
    mHPBar->setPosition(ccp(blackbg->getContentSize().width/2,blackbg->getContentSize().height/4*3-60));
    mHPBar->setMidpoint(ccp(0, 0.5));
    mHPBar->setBarChangeRate(ccp(1, 0));
    mHPBar->setPercentage(100);      //一定要设置百分比,默认为0,不显示
    blackbg->addChild(mHPBar,1,22);
    
    //修改触屏分发
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    //加载攻击特效
    AttackEffect::atkeffect()->preload();
    //设置战斗状态标志
    isinbattle=false;
    isbattlepaused=true;

    
    startlabel=CCLabelBMFont::create("Click To Start.", "myfont1.fnt");
    startlabel->setPosition(ccp(blackbg->getContentSize().width/2,blackbg->getContentSize().height/2));
    blackbg->addChild(startlabel,1,41);
}

bool Battle::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    CCLog("touch");
    //进入界面，点击开始战斗
    
    if (isinbattle==false&&isbattlepaused==true&&isplayerfailed==false) {
        CCLog("进入战斗界面,点击开始战斗");
        blackbg->removeChildByTag(41,true);
        isinbattle=true;
        isbattlepaused=false;
        isplayerfailed=false;
        maxCombo_player=ComboCheck(userdata->getFinal_ComboRatio());
        CCLOG("new maxCombo_player=%d",maxCombo_player);
        maxCombo_monster=ComboCheck(mm->getM_ComboRatio());
        //        CCLOG("new maxCombo_monster=%d",maxCombo_monster);
        comboNO_player=0;
        comboNO_monster=0;
        //永远由Player发起攻击
        PlayerAttack();
    }
    
    //战斗中，点击暂停
    else if (isinbattle==true&&isbattlepaused==false&&isplayerfailed==false) {
        CCLog("战斗中，点击暂停");
        pauselabel=CCLabelBMFont::create("PAUSED!", "myfont1.fnt");
        pauselabel->setPosition(ccp(blackbg->getContentSize().width/2,blackbg->getContentSize().height/2));
        blackbg->addChild(pauselabel,1,42);
        player->pauseSchedulerAndActions();
        monster->pauseSchedulerAndActions();
        isbattlepaused=true;
        
    }
    
    
    //战斗中，暂停中，点击恢复
    else if (isinbattle==true&&isbattlepaused==true&&isplayerfailed==false) {
        CCLog("战斗中，暂停中，点击恢复");
        blackbg->removeChildByTag(42,true);
        player->resumeSchedulerAndActions();
        monster->resumeSchedulerAndActions();
        isbattlepaused=false;
    }

    //如果player loos，点击退出
    else if (isinbattle==false&&isbattlepaused==false&&isplayerfailed==true) {
        userdata->SaveUserData();
        CCLog("结束画面,点击退出");
        const char*  battlelayerexited="BattleLayerExited";
        CCNotificationCenter::sharedNotificationCenter()->postNotification(battlelayerexited);
        
        //退出画面
    }
    
    return true;
}

void Battle::onExit(){
//    userdata->SaveUserData();
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCLog("battle layer exited");
    CCLayer::onExit();
}

void Battle::setRandomSeed(){
    cc_timeval psv;
    CCTime::gettimeofdayCocos2d(&psv, NULL);
    unsigned long seed = psv.tv_sec*1000 + psv.tv_usec/1000;
    srand(seed);
}

void Battle::PlayerAttack(){
    float damage;
    float criticaldamage;
    bool isCritical=isCriticalHit(userdata->getFinal_CriticalRatio());
    
    //判断是否暴击
    if (isCritical) {
        //monster受到暴击的特效,暂时和不暴击一样
        AttackEffect::atkeffect()->attack(monster->getParent(), monster->getPosition());
        criticaldamage=userdata->getFinal_CriticalDamage();
    }
    else {
        //monster受到普通攻击的特效
        AttackEffect::atkeffect()->attack(monster->getParent(), monster->getPosition());
        criticaldamage=1;
    }
    CCCallFuncN* callback=CCCallFuncN::create(this, callfuncN_selector(Battle::PlayerAttackCallBack));
    monster->runAction(CCSequence::create(CCShake::create(0.4, 5),CCDelayTime::create(1.0),callback,NULL));
    comboNO_player++;
    CCLog("player combo:%d",comboNO_player);
    
    //player对怪的伤害,计算公式:人对怪物伤害=攻击力*(1-伤害减免*级别差修正)*暴击倍率
    damage=userdata->getFinal_ATK()*(1-mm->getM_DamageReduction()*levelCorrection(userdata->getLevel(), mm->getM_Level()))*criticaldamage;
    
    //monster扣血
    mHP-=damage;
    CCLOG("player attack damage=%f monsterhp=%f",damage,mHP);
    
    //monster掉血数字特效
    DamageNumber::shareddamagenumber()->getDanageEffect(monster, isCritical, damage);
    
    //修改Monster的HPbar
    mHPBar->setPercentage(mHP/mm->getM_HP()*100);

    
    
    
}
void Battle::MonsterAttack(){
    float damage;
    float criticaldamage;
    bool isCritical;
    //判断是否暴击
    if (isCriticalHit(mm->getM_CriticalRatio())) {
        //player受到暴击的特效,暂时和不暴击一样
        AttackEffect::atkeffect()->attack(player->getParent(), player->getPosition());
        criticaldamage=mm->getM_CriticalDamage();
        isCritical=true;
    }
    else {
        //player受到普通攻击的特效
        AttackEffect::atkeffect()->attack(player->getParent(), player->getPosition());
        criticaldamage=1;
        isCritical=false;
    }
    CCCallFuncN* callback=CCCallFuncN::create(this, callfuncN_selector(Battle::MonsterAttackCallBack));
    player->runAction(CCSequence::create(CCShake::create(0.4, 5),CCDelayTime::create(1.0),callback,NULL));
    comboNO_monster++;
    
    //计算伤害,公式为:怪物对人伤害=攻击力*(1-伤害减免*级别差修正)*暴击倍率
    damage=mm->getM_ATK()*(1-userdata->getFinal_DamageReduction()*levelCorrection(mm->getM_Level(), userdata->getLevel()))*criticaldamage;
    
    //plaer扣血
    pHP-=damage;
    CCLOG("monster attack damage=%f playerhp=%f",damage,pHP);
    
    //player掉血数字特效
    DamageNumber::shareddamagenumber()->getDanageEffect(player, isCritical, damage);
    
    //修改player的HPbar
    pHPBar->setPercentage(pHP/userdata->getFinal_HP()*100);
    
    

}
void Battle::PlayerAttackCallBack(CCNode* pSender){
    //如果没有完成连击数则继续攻击，完成则换monster攻击
    if (mHP>0) {
        if (comboNO_player<maxCombo_player) {
            PlayerAttack();
        }
        else {
            CCLog("player combo complete");
            comboNO_player=0;
            MonsterAttack();
        }
    }
    else {
        CCLOG("player wins");
        userdata->setGameTimes(userdata->getGameTimes()-1);
        monster->stopAllActions();
        player->stopAllActions();
        //战斗结束
        finalview(true);

    }
}
void Battle::MonsterAttackCallBack(CCNode* pSender){
       if (pHP>0) {
        //如果没有完成连击数则继续攻击，完成则换monster攻击
        if (comboNO_monster<maxCombo_monster) {
            MonsterAttack();
        }
        else {
            CCLog("monster combo complete");
            comboNO_monster=0;
            PlayerAttack();
        }
    }
    else {
        CCLOG("Player loses");
        userdata->setGameTimes(userdata->getGameTimes()-3);
        
        monster->stopAllActions();
        player->stopAllActions();
        //战斗结束画面
        finalview(false);
        isinbattle=false;
        isplayerfailed=true;
    }

}

int Battle::ComboCheck(float ComboRatio){
    int combo=1;
    do {
        
        float random=CCRANDOM_0_1();
        if (random<ComboRatio) {
            combo++;
            ComboRatio=ComboRatio*0.5f;
        }
        else break;
    } while (combo!=100);
    return combo;
}
bool Battle::isCriticalHit(float CriticalRatio){
    if (CCRANDOM_0_1()<CriticalRatio) {
        return true;
        CCLOG("Critical Hit!");
    }
    else return false;
}

float Battle::levelCorrection(int AtkLevel,int DefLevel){
    int SubLevel=AtkLevel-DefLevel;
    if (SubLevel<=-1000) return 0.5;
    else if (SubLevel>-1000&&SubLevel<=-500) return 0.6;
    else if (SubLevel>-500&&SubLevel<=-200) return 0.7;
    else if (SubLevel>-200&&SubLevel<=-100) return 0.8;
    else if (SubLevel>-100&&SubLevel<=-10) return 0.9;
    else return 1.0;
}

void Battle::finalview(bool isPlayerWins){
    isinbattle=false;
    if (isPlayerWins) {
        blackbg->removeChildByTag(21);
        blackbg->removeChildByTag(22);
        blackbg->removeChildByTag(23);
        CCLabelBMFont* playerwinlabel=CCLabelBMFont::create("YOU WIN!", "myfont1.fnt");
        playerwinlabel->setPosition(ccp(blackbg->getContentSize().width/2,blackbg->getContentSize().height/4*3));
        blackbg->addChild(playerwinlabel);
        
        CCLabelBMFont* EXPLabel1=CCLabelBMFont::create("EXP :", "myfont1.fnt");
        EXPLabel1->setPosition(ccp(70,blackbg->getContentSize().height/4*3-100));
        blackbg->addChild(EXPLabel1);
        
        //级别显示
        CCLabelBMFont* lvLabel=CCLabelBMFont::create("LEVEL :","myfont1.fnt");
        lvNumber=CCLabelAtlas::create(IntToChar(userdata->getLevel()), "number.png", 24, 34, 48);
        lvLabel->setPosition(ccp(EXPLabel1->getPositionX(), EXPLabel1->getPositionY()-60));
        lvNumber->setPosition(ccp(blackbg->getContentSize().width/2, EXPLabel1->getPositionY()-75));
        blackbg->addChild(lvLabel);
        blackbg->addChild(lvNumber);
    
        //升级经验条
        CCSprite* EXPBarbg=CCSprite::create("BarBox.png");
        EXPBarbg->setAnchorPoint(ccp(0.5, 0.5));
        EXPBarbg->setPosition(ccp(blackbg->getContentSize().width/2,EXPLabel1->getPositionY()));
        blackbg->addChild(EXPBarbg);
        CCSprite* EXPBarSprite=CCSprite::create("EXPbar.png");
        EXPBar=CCProgressTimer::create(EXPBarSprite);
        EXPBar->setType(kCCProgressTimerTypeBar);
        EXPBar->setAnchorPoint(ccp(0.5, 0.5));
        EXPBar->setPosition(ccp(blackbg->getContentSize().width/2,EXPLabel1->getPositionY()));
        EXPBar->setMidpoint(ccp(0, 0.5));
        EXPBar->setBarChangeRate(ccp(1, 0));
        EXPBar->setPercentage(userdata->getEXP()/pow(userdata->getLevel(), EXP_POWER)*100);
        blackbg->addChild(EXPBar);
        EXPnow=userdata->getEXP();
        //计算打怪所得经验,公式为:经验=怪物经验提供值*random(0.9,1.1)*(1+道具经验加成)
        EXPadd=((float)mm->getM_Exp()*(CCRANDOM_0_1()*0.2+0.9)*(1+userdata->getFinal_ExpRate()));
        EXPmax=pow(userdata->getLevel(), EXP_POWER)+99;
    
        LevelUp();
    }
    else{
        blackbg->removeChildByTag(21);
        blackbg->removeChildByTag(22);
        CCLabelBMFont* playerwinlabel=CCLabelBMFont::create("YOU LOOSE! -3 GameTimes.", "myfont1.fnt");
        playerwinlabel->setPosition(ccp(blackbg->getContentSize().width/2,blackbg->getContentSize().height/4*3));
        blackbg->addChild(playerwinlabel);
        CCLabelBMFont* exitlabel=CCLabelBMFont::create("Click to Exit.", "myfont1.fnt");
        exitlabel->setPosition(ccp(blackbg->getContentSize().width/2,blackbg->getContentSize().height/2));
        blackbg->addChild(exitlabel,1,43);
        player->setRotation(-90);
    }
}

void Battle::LevelUp(){
    if (LevelUpEXP()) {
        CCProgressFromTo* EXPProgressFromTO1=CCProgressFromTo::create(0.3, (float)EXPnow/(float)EXPmax*100, 100);
        CCCallFuncN* callback1=CCCallFuncN::create(this, callfuncN_selector(Battle::EXPBarcallbackLvUp));
        EXPBar->runAction(CCSequence::create(EXPProgressFromTO1,callback1,NULL));
        
    }
    else{
        CCProgressFromTo* EXPProgressFromTO2=CCProgressFromTo::create(0.3, (float)EXPnow/(float)EXPmax*100,((float)EXPnow+(float)EXPadd)/(float)EXPmax*100);
        CCCallFuncN* callback2=CCCallFuncN::create(this, callfuncN_selector(Battle::EXPBarcallbackLv));
        EXPBar->runAction(CCSequence::create(EXPProgressFromTO2,callback2,NULL));
    }
}

bool Battle::LevelUpEXP(){
    if ((EXPnow+EXPadd)<=EXPmax) {
        return false;
    }
    else{
        return true;
    }
}

void Battle::EXPBarcallbackLvUp(cocos2d::CCNode *pSender){
    EXPadd=EXPadd-(EXPmax-EXPnow);
    userdata->setLevel(userdata->getLevel()+1);
    LevelUpEffect::sharedlevleupeffect()->levelup(player);
    lvNumber->setString(IntToChar(userdata->getLevel()));
    userdata->setSparePoint(userdata->getSparePoint()+userdata->getPointPerLevel());
    EXPmax=pow(userdata->getLevel(), EXP_POWER)+99;
    EXPnow=0;
    LevelUp();
}
void Battle::EXPBarcallbackLv(cocos2d::CCNode *pSender){
    EXPnow+=EXPadd;
    EXPadd=0;
    userdata->setEXP(EXPnow);
    CCLabelBMFont* labelmap=CCLabelBMFont::create("MAP", "myfont1.fnt");
    CCLabelBMFont* labelstatus=CCLabelBMFont::create("STATUS", "myfont1.fnt");
    CCMenuItemLabel* clicktomap=CCMenuItemLabel::create(labelmap, this, menu_selector(Battle::menucallback));
    CCMenuItemLabel* clicktostatus=CCMenuItemLabel::create(labelstatus, this, menu_selector(Battle::menucallback));
    
    CCMenu* menu=CCMenu::create();
    menu->addChild(clicktomap,50,41);
    menu->addChild(clicktostatus,50,42);
    
    menu->alignItemsHorizontallyWithPadding(50);
    
    menu->setPosition(ccp(blackbg->getContentSize().width/2,50));
    blackbg->addChild(menu);
}

void Battle::menucallback(cocos2d::CCObject *pSender){
    CCLog("equip:%s   Bag:%s",USER_DEFAULT->getStringForKey("Equipments").c_str(),USER_DEFAULT->getStringForKey("EquipBag").c_str());
    userdata->SaveUserData();
    int tag=((CCMenuItemLabel*)pSender)->getTag();
    if (tag==42) {
        CCDirector::sharedDirector()->pushScene(Status::scene());
    }
    CCLog("退出BattleLayer");
    const char*  battlelayerexited="BattleLayerExited";
    CCNotificationCenter::sharedNotificationCenter()->postNotification(battlelayerexited);
}

//void Battle::ExitNotify(){
//    const char*  battlelayerexited="BattleLayerExited";
//    CCNotificationCenter::sharedNotificationCenter()->postNotification(battlelayerexited);
//}

const char* Battle::IntToChar(int num){
    CCString* csnum=CCString::createWithFormat("%d",num);
    return csnum->getCString();
}