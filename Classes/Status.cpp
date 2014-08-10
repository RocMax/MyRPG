//
//  Status.cpp
//  MyRPG
//
//  Created by RocLee on 14-8-5.
//
//

#include "Status.h"
#include "Battle.h"
#include "SelectHero.h"


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
    sp=ud->getSparePoint();
    HP=(int)ud->getHP();
    ATK=(int)ud->getATK();
    DEF=(int)ud->getDEF();
    AGI=(int)ud->getAGI();
    LUK=(int)ud->getLUK();
    
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
    
    sparepoint=CCLabelAtlas::create(Battle::IntToChar(sp), "number.png", 24, 34, 48);
    sparepoint->setPosition(ccp(getWinsize().width/2+pointlabel->getContentSize().width/2+50, getWinsize().height-220));
    this->addChild(sparepoint);
    
    //添加各项属性的增减界面
    CCLabelBMFont* HPlabel=CCLabelBMFont::create("HP  :", "myfont1.fnt");
    CCLabelBMFont* ATKlabel=CCLabelBMFont::create("ATK :", "myfont1.fnt");
    CCLabelBMFont* DEFlabel=CCLabelBMFont::create("DEF :", "myfont1.fnt");
    CCLabelBMFont* AGIlabel=CCLabelBMFont::create("AGI :", "myfont1.fnt");
    CCLabelBMFont* LUKlabel=CCLabelBMFont::create("LUK :", "myfont1.fnt");
    
    LUKlabel->setPosition(ccp(100, getWinsize().height/5));
    AGIlabel->setPosition(SelectHero::nextLabelPosition(LUKlabel, true, LABEL_PADDING*5));
    DEFlabel->setPosition(SelectHero::nextLabelPosition(AGIlabel, true, LABEL_PADDING*5));
    ATKlabel->setPosition(SelectHero::nextLabelPosition(DEFlabel, true, LABEL_PADDING*5));
    HPlabel->setPosition(SelectHero::nextLabelPosition(ATKlabel, true, LABEL_PADDING*5));
    
    this->addChild(HPlabel);
    this->addChild(ATKlabel);
    this->addChild(DEFlabel);
    this->addChild(AGIlabel);
    this->addChild(LUKlabel);
    
    CCLabelBMFont* addbmfont1=CCLabelBMFont::create("+", "myfont1.fnt");
    CCLabelBMFont* addbmfont2=CCLabelBMFont::create("+", "myfont1.fnt");
    CCLabelBMFont* addbmfont3=CCLabelBMFont::create("+", "myfont1.fnt");
    CCLabelBMFont* addbmfont4=CCLabelBMFont::create("+", "myfont1.fnt");
    CCLabelBMFont* addbmfont5=CCLabelBMFont::create("+", "myfont1.fnt");
    
    CCMenuItemLabel* addmenuitem1=CCMenuItemLabel::create(addbmfont1, this, menu_selector(Status::addmeuncallback));
    CCMenuItemLabel* addmenuitem2=CCMenuItemLabel::create(addbmfont2, this, menu_selector(Status::addmeuncallback));
    CCMenuItemLabel* addmenuitem3=CCMenuItemLabel::create(addbmfont3, this, menu_selector(Status::addmeuncallback));
    CCMenuItemLabel* addmenuitem4=CCMenuItemLabel::create(addbmfont4, this, menu_selector(Status::addmeuncallback));
    CCMenuItemLabel* addmenuitem5=CCMenuItemLabel::create(addbmfont5, this, menu_selector(Status::addmeuncallback));

    CCLabelBMFont* subbmfont1=CCLabelBMFont::create("-", "myfont1.fnt");
    CCLabelBMFont* subbmfont2=CCLabelBMFont::create("-", "myfont1.fnt");
    CCLabelBMFont* subbmfont3=CCLabelBMFont::create("-", "myfont1.fnt");
    CCLabelBMFont* subbmfont4=CCLabelBMFont::create("-", "myfont1.fnt");
    CCLabelBMFont* subbmfont5=CCLabelBMFont::create("-", "myfont1.fnt");
    
    CCMenuItemLabel* submenuitem1=CCMenuItemLabel::create(subbmfont1, this, menu_selector(Status::submenucallback));
    CCMenuItemLabel* submenuitem2=CCMenuItemLabel::create(subbmfont2, this, menu_selector(Status::submenucallback));
    CCMenuItemLabel* submenuitem3=CCMenuItemLabel::create(subbmfont3, this, menu_selector(Status::submenucallback));
    CCMenuItemLabel* submenuitem4=CCMenuItemLabel::create(subbmfont4, this, menu_selector(Status::submenucallback));
    CCMenuItemLabel* submenuitem5=CCMenuItemLabel::create(subbmfont5, this, menu_selector(Status::submenucallback));
    
    CCMenu* addmenu=CCMenu::create();
    addmenu->addChild(addmenuitem1, 1, 11);
    addmenu->addChild(addmenuitem2, 1, 12);
    addmenu->addChild(addmenuitem3, 1, 13);
    addmenu->addChild(addmenuitem4, 1, 14);
    addmenu->addChild(addmenuitem5, 1, 15);
    
    CCMenu* submenu=CCMenu::create();
    submenu->addChild(submenuitem1, 1, 21);
    submenu->addChild(submenuitem2, 1, 22);
    submenu->addChild(submenuitem3, 1, 23);
    submenu->addChild(submenuitem4, 1, 24);
    submenu->addChild(submenuitem5, 1, 25);
    
    addmenu->alignItemsVerticallyWithPadding(LABEL_PADDING*5);
    submenu->alignItemsVerticallyWithPadding(LABEL_PADDING*5);

    
    statunum1=CCLabelAtlas::create(Battle::IntToChar(HP), "number.png", 24, 34, 48);
    statunum2=CCLabelAtlas::create(Battle::IntToChar(ATK), "number.png", 24, 34, 48);
    statunum3=CCLabelAtlas::create(Battle::IntToChar(DEF), "number.png", 24, 34, 48);
    statunum4=CCLabelAtlas::create(Battle::IntToChar(AGI), "number.png", 24, 34, 48);
    statunum5=CCLabelAtlas::create(Battle::IntToChar(LUK), "number.png", 24, 34, 48);
    
    statunum1->setPosition(HPlabel->getPositionX()+250,HPlabel->getPositionY());
    statunum2->setPosition(HPlabel->getPositionX()+250,ATKlabel->getPositionY());
    statunum3->setPosition(HPlabel->getPositionX()+250,DEFlabel->getPositionY());
    statunum4->setPosition(HPlabel->getPositionX()+250,AGIlabel->getPositionY());
    statunum5->setPosition(HPlabel->getPositionX()+250,LUKlabel->getPositionY());
    
    this->addChild(statunum1,1,31);
    this->addChild(statunum2,1,32);
    this->addChild(statunum3,1,33);
    this->addChild(statunum4,1,34);
    this->addChild(statunum5,1,35);
    
    submenu->setPosition(ccp(DEFlabel->getPositionX()+DEFlabel->getContentSize().width/2+100, DEFlabel->getPositionY()));
    this->addChild(submenu);
    
    addmenu->setPosition(ccp(statunum3->getPositionX()+statunum3->getContentSize().width/2+100, statunum3->getPositionY()));
    this->addChild(addmenu);
    
    
    this->scheduleUpdate();
}

void Status::addmeuncallback(cocos2d::CCNode *pSender){
    int tag=pSender->getTag();
    switch (tag) {
        case 11:
            flag=11;
            break;
        case 12:
            flag=21;
            break;
        case 13:
            flag=31;
            break;
        case 14:
            flag=41;
            break;
        case 15:
            flag=51;
            break;
        default:

            break;
    }
    
}

void Status::submenucallback(cocos2d::CCNode *pSender){
    int tag=pSender->getTag();
    switch (tag) {
        case 21:
            flag=12;
            break;
        case 22:
            flag=22;
            break;
        case 23:
            flag=32;
            break;
        case 24:
            flag=42;
            break;
        case 25:
            flag=52;
            break;
        default:
            
            break;
    }
}

void Status::update(float t){
    if (atoi(sparepoint->getString())<=sp&&atoi(sparepoint->getString())>0) {
        switch (flag) {
            case 11:
                labelchange(statunum1, true);
                labelchange(sparepoint, false);
                break;
            case 21:
                labelchange(statunum2, true);
                labelchange(sparepoint, false);
                break;
            case 31:
                labelchange(statunum3, true);
                labelchange(sparepoint, false);
            case 41:
                labelchange(statunum4, true);
                labelchange(sparepoint, false);
                break;
            case 51:
                labelchange(statunum5, true);
                labelchange(sparepoint, false);
                break;
            default:
                break;
        }
    }
    if (atoi(sparepoint->getString())<sp&&atoi(sparepoint->getString())>=0){
        switch (flag) {
            case 12:
                if (atoi(statunum1->getString())>HP) {
                    labelchange(statunum1, false);
                    labelchange(sparepoint, true);
                }
                break;
            case 22:
                if (atoi(statunum2->getString())>ATK) {
                    labelchange(statunum2, false);
                    labelchange(sparepoint, true);
                }
                break;
            case 32:
                if (atoi(statunum3->getString())>DEF) {
                    labelchange(statunum3, false);
                    labelchange(sparepoint, true);
                }
                break;
            case 42:
                if (atoi(statunum4->getString())>AGI) {
                    labelchange(statunum4, false);
                    labelchange(sparepoint, true);
                }
                break;
            case 52:
                if (atoi(statunum5->getString())>LUK) {
                    labelchange(statunum5, false);
                    labelchange(sparepoint, true);
                }
                break;
            default:
                break;
        }
    }
    
    
}

void Status::labelchange(cocos2d::CCLabelAtlas *label, bool isadd){
    const char* str=label->getString();
    if (isadd) {
        label->setString(Battle::IntToChar(atoi(str)+1));
    }
    else label->setString(Battle::IntToChar(atoi(str)-1));
}
