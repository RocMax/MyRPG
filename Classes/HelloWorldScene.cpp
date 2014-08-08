#include "HelloWorldScene.h"
#include "SelectHero.h"

USING_NS_CC;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    setupviews();
    
    return true;
}


//void HelloWorld::menuCloseCallback(CCObject* pSender)
//{
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
//	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
//#else
//    CCDirector::sharedDirector()->end();
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    exit(0);
//#endif
//#endif
//}

void HelloWorld::setupviews(){
    CCSize winsize=CCDirector::sharedDirector()->getWinSize();
    CCSprite* pStartNormal=CCSprite::create("menu.png",CCRectMake(0, 0, 126, 33));
    CCSprite* pStartPressed=CCSprite::create("menu.png", CCRectMake(0, 33, 126, 33));
    CCSprite* pStartDisabled=CCSprite::create("menu.png", CCRectMake(0, 66, 126, 33));
    CCMenuItemSprite* startGame=CCMenuItemSprite::create(pStartNormal, pStartPressed, pStartDisabled, this, menu_selector(HelloWorld::startgame_callback));
    
    CCSprite* pOptionNormal=CCSprite::create("menu.png",CCRectMake(126, 0, 126, 33));
    CCSprite* pOptionPressed=CCSprite::create("menu.png", CCRectMake(126, 33, 126, 33));
    CCSprite* pOptionDisabled=CCSprite::create("menu.png", CCRectMake(126, 66, 126, 33));
    CCMenuItemSprite* optionGame=CCMenuItemSprite::create(pOptionNormal, pOptionPressed,pOptionDisabled,this,menu_selector(HelloWorld::option_callback));
    
    CCSprite* pAboutNormal=CCSprite::create("menu.png",CCRectMake(252, 0, 126, 33));
    CCSprite* pAboutPressed=CCSprite::create("menu.png", CCRectMake(252, 33, 126, 33));
    CCSprite* pAboutDisabled=CCSprite::create("menu.png", CCRectMake(252, 66, 126, 33));
    CCMenuItemSprite* aboutGame=CCMenuItemSprite::create(pAboutNormal, pAboutPressed, pAboutDisabled, this, menu_selector(HelloWorld::about_callback));
    
    CCMenu* pMenu=CCMenu::create(startGame,optionGame,aboutGame,NULL);
    
    pMenu->setAnchorPoint(ccp(0, 0));
    pMenu->setScale(1.5f);
    pMenu->setPosition(ccp(winsize.width/2, winsize.height-300));
    pMenu->alignItemsVerticallyWithPadding(20);
    
    
    this->addChild(pMenu);
    
    
}

void HelloWorld::startgame_callback(CCObject* pSender){
    CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f,SelectHero::scene()));

    CCLOG("Game Start");
}
void HelloWorld::option_callback(CCObject* pSender){
//    CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f, OptionLayer::scene()));
    CCLOG("Game Option");
}
void HelloWorld::about_callback(CCObject* pSender){
    CCLOG("About Game");
//   CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f, AboutLayer::scene()));
}

