//
//  SelectHero.cpp
//  MyRPG
//
//  Created by RocLee on 14-6-30.
//
//

#include "SelectHero.h"
#include "CCRadioMenu.h"
#include "DBOperations.h"
#include "HelloWorldScene.h"
#include "UserData.h"
#include "Gaming.h"



CCScene* SelectHero::scene(){
    CCScene* scene=CCScene::create();
    SelectHero* layer=SelectHero::create();
    scene->addChild(layer);
    
    return scene;
    
}
bool SelectHero::init(){
    bool sRect=false;
    do {
        CC_BREAK_IF(!CCLayer::init());
        SetupViews();
        sRect=true;
    } while (0);
    return sRect;
    
}

void SelectHero::draw(){
    CCSize winsize=CCDirector::sharedDirector()->getWinSize();
    ccDrawLine(ccp(0, winsize.height/2), ccp(winsize.width, winsize.height/2));

    CHECK_GL_ERROR_DEBUG();
}

void SelectHero::SetupViews(){
    CCSize winsize=CCDirector::sharedDirector()->getWinSize();
    
    //创建英雄选择菜单
    CCRadioMenu* radioMenu=CCRadioMenu::create();
    
    //添加英雄选择状态图案
    CCMenuItemImage* player1=CCMenuItemImage::create("hobit_gray.png", "hobit.png", this, menu_selector(SelectHero::radiomenucallback));
    CCMenuItemImage* player2=CCMenuItemImage::create("lizardman_gray.png", "lizardman.png", this, menu_selector(SelectHero::radiomenucallback));
    CCMenuItemImage* player3=CCMenuItemImage::create("manticore_gray.png", "manticore.png", this, menu_selector(SelectHero::radiomenucallback));
    CCMenuItemImage* player4=CCMenuItemImage::create("spector_gray.png", "spector.png", this, menu_selector(SelectHero::radiomenucallback));
    CCMenuItemImage* player5=CCMenuItemImage::create("cyclops_gray.png", "cyclops.png", this, menu_selector(SelectHero::radiomenucallback));
    
    radioMenu->addChild(player1,1,1);
    radioMenu->addChild(player2,1,2);
    radioMenu->addChild(player3,1,3);
    radioMenu->addChild(player4,1,4);
    radioMenu->addChild(player5,1,5);
    
    radioMenu->setAnchorPoint(ccp(0.5, 1));
    radioMenu->setPosition(ccp(winsize.width/2, winsize.height-150));
    radioMenu->alignItemsHorizontallyWithPadding(10.0f);
    this->addChild(radioMenu);
    
    //读取英雄初始数据表
    
    int result;
    char* errorMsg = NULL;

    
    sqlite3* pDB=DBOperation::openDB();
    result = sqlite3_get_table(pDB, "select * from HeroType", &dbResult, &row, &column, &errorMsg);
    if (result!=SQLITE_OK) {
        CCLOG(errorMsg);
    }
    
    sqlite3_close(pDB);
    
    
    
    //显示默认英雄的数据
    choice=1;
    Name_Label=CCLabelBMFont::create(addchar("NAME:", dbResult[choice*column+1]), "myfont1.fnt");
    HP_Label=CCLabelBMFont::create(addchar("HP:", dbResult[choice*column+3]) , "myfont1.fnt");
    ATK_Label=CCLabelBMFont::create(addchar("ATK:", dbResult[choice*column+4]) , "myfont1.fnt");
    DEF_Label=CCLabelBMFont::create(addchar("DEF:", dbResult[choice*column+5]) , "myfont1.fnt");
    AGI_Label=CCLabelBMFont::create(addchar("AGI:", dbResult[choice*column+6]) , "myfont1.fnt");
    LUK_Label=CCLabelBMFont::create(addchar("LUK:", dbResult[choice*column+7]) , "myfont1.fnt");
    
    
    Name_Label->setAnchorPoint(ccp(0, 0));
    HP_Label->setAnchorPoint(ccp(0, 0));
    ATK_Label->setAnchorPoint(ccp(0, 0));
    DEF_Label->setAnchorPoint(ccp(0, 0));
    AGI_Label->setAnchorPoint(ccp(0, 0));
    LUK_Label->setAnchorPoint(ccp(0, 0));
    
    Name_Label->setScale(0.7f);
    HP_Label->setScale(0.7f);
    ATK_Label->setScale(0.7f);
    DEF_Label->setScale(0.7f);
    AGI_Label->setScale(0.7f);
    LUK_Label->setScale(0.7f);
    
    
    ATK_Label->setPosition(ccp(50, 135));
    HP_Label->setPosition(nextLabelPosition(ATK_Label, true, LABEL_PADDING));
    Name_Label->setPosition(nextLabelPosition(HP_Label, true, LABEL_PADDING));
    
    LUK_Label->setPosition(nextLabelPosition(ATK_Label, false, 50));
    AGI_Label->setPosition(nextLabelPosition(LUK_Label, true, LABEL_PADDING));
    DEF_Label->setPosition(nextLabelPosition(AGI_Label, true, LABEL_PADDING));
    
    
    this->addChild(Name_Label);
    this->addChild(HP_Label);
    this->addChild(ATK_Label);
    this->addChild(DEF_Label);
    this->addChild(AGI_Label);
    this->addChild(LUK_Label);
    
    
    //添加确认和返回按钮
    CCMenu* menu=CCMenu::create();
    
    CCLabelBMFont* oklabel=CCLabelBMFont::create("OK", "myfont1.fnt");
    CCMenuItemLabel* okMenu=CCMenuItemLabel::create(oklabel, this, menu_selector(SelectHero::okmenucallback));
    CCLabelBMFont* backlabel=CCLabelBMFont::create("BACK", "myfont1.fnt");
    CCMenuItemLabel* backMenu=CCMenuItemLabel::create(backlabel, this, menu_selector(SelectHero::okmenucallback));
    
    
    menu->addChild(okMenu,1,6);
    menu->addChild(backMenu,1,7);
    menu->alignItemsVerticallyWithPadding(20.0);
    
    menu->setAnchorPoint(ccp(0, 0));
    menu->setPosition(ccp(winsize.width-150, 250));
    
    this->addChild(menu);
    
}

//英雄选择菜单回调函数,可共用,根据tag判定选择结果.注意:player1是默认选择,需在场景载入时就读入player1数据,回调函数不一定触发
void SelectHero::radiomenucallback(cocos2d::CCObject *pSender){
    choice=((CCMenuItemImage*)pSender)->getTag();
    CCLOG("choose player%d",choice);
    
    Name_Label->setString(addchar("NAME:", dbResult[choice*column+1]));
    HP_Label->setString(addchar("HP:", dbResult[choice*column+3]));
    ATK_Label->setString(addchar("ATK:", dbResult[choice*column+4]));
    DEF_Label->setString(addchar("DEF:", dbResult[choice*column+5]));
    AGI_Label->setString(addchar("AGI:", dbResult[choice*column+6]));
    LUK_Label->setString(addchar("LUK:", dbResult[choice*column+7]));
    
    
    
    
}

CCPoint SelectHero::nextLabelPosition(cocos2d::CCNode *preLabel, bool vertical, int padding){
    CCPoint position;
    if (vertical) {
        position=ccpAdd(preLabel->getPosition(), ccp(0, preLabel->getContentSize().height+padding));
    }
    else{
        position=ccpAdd(preLabel->getPosition(), ccp(preLabel->getContentSize().width+padding,0));
    }
    return position;
                                
}

const char* SelectHero::addchar(const char *a, char *b){
    CCString* ca=CCString::createWithFormat("%s%s",a,b);
    return ca->getCString();
}

void SelectHero::onExit(){
    
    sqlite3_free_table(dbResult);
    CCLOG("table released");
    CCLayer::onExit();
    
}

void SelectHero::okmenucallback(cocos2d::CCObject *pSender){
    int tag=((CCMenuItemLabel*)pSender)->getTag();
    if (tag==6) {
        //点击"OK",将英雄初始数据复制给CCUserDefault
        USER_DEFAULT->setStringForKey("Name", dbResult[choice*column+1]);
        USER_DEFAULT->setStringForKey("Pic", dbResult[choice*column+2]);
        USER_DEFAULT->setFloatForKey("HP", atof(dbResult[choice*column+3]));
        USER_DEFAULT->setFloatForKey("ATK", atof(dbResult[choice*column+4]));
        USER_DEFAULT->setFloatForKey("DEF", atof(dbResult[choice*column+5]));
        USER_DEFAULT->setFloatForKey("AGI", atof(dbResult[choice*column+6]));
        USER_DEFAULT->setFloatForKey("LUK", atof(dbResult[choice*column+7]));
        USER_DEFAULT->setFloatForKey("HPPerPoint", atof(dbResult[choice*column+8]));
        USER_DEFAULT->setFloatForKey("ATKPerPoint", atof(dbResult[choice*column+9]));
        USER_DEFAULT->setFloatForKey("DEFPerPoint", atof(dbResult[choice*column+10]));
        USER_DEFAULT->setFloatForKey("AGIPerPoint", atof(dbResult[choice*column+11]));
        USER_DEFAULT->setFloatForKey("LUKPerPoint", atof(dbResult[choice*column+12]));
        USER_DEFAULT->setIntegerForKey ("PointPerLevel", atoi(dbResult[choice*column+13]));
        
        //以下是新建的默认值
        USER_DEFAULT->setIntegerForKey("GameTimes", 30);
        USER_DEFAULT->setIntegerForKey("SparePoint", 0);
        USER_DEFAULT->setIntegerForKey("Level", 1);
        USER_DEFAULT->setIntegerForKey("EXP", 0);
        USER_DEFAULT->setIntegerForKey("PositionX", 100);
        USER_DEFAULT->setIntegerForKey("PositionY", 100);
        USER_DEFAULT->setIntegerForKey("MapOffsetX", 0);
        USER_DEFAULT->setIntegerForKey("MapOffsetY", 0);
        USER_DEFAULT->setIntegerForKey("MapArea", 0);
        USER_DEFAULT->setStringForKey("Map", "Tiledmap.tmx");
        
        USER_DEFAULT->setStringForKey("EquipBag", "0;2:1;3:1;4:10;5:1");
        USER_DEFAULT->setStringForKey("Equipments","0;2:1;3:1;4:1;4:1;4:1;4:1;4:1;4:1");
        
        USER_DEFAULT->flush();
        
        
        
//        CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f,Gaming::scene()));
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f,Gaming::scene()));


    }
    else {
        //点击"back",返回至开始界面
//        CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f,HelloWorld::scene()));
        CCDirector::sharedDirector()->popScene();
    }
}
