//
//  SelectHero.h
//  MyRPG
//
//  Created by RocLee on 14-6-30.
//
//

#ifndef __MyRPG__SelectHero__
#define __MyRPG__SelectHero__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

#define LABEL_PADDING 10

class SelectHero:public CCLayer{
public:
    virtual bool init();
    static CCScene* scene();
    CREATE_FUNC(SelectHero);
    char** dbResult;    //char[][]用来存放结果
    int row;
    int column;
    
    CCLabelBMFont* Name_Label;
    CCLabelBMFont* HP_Label;
    CCLabelBMFont* ATK_Label;
    CCLabelBMFont* DEF_Label;
    CCLabelBMFont* AGI_Label;
    CCLabelBMFont* LUK_Label;
    
    int choice;
    
    static CCPoint nextLabelPosition(CCNode* preLabel,bool vertical,int padding);
    
private:
    void SetupViews();
    void radiomenucallback(CCObject* pSender);
    virtual void draw();
    
    
    const char* addchar(const char* a,char* b);
    
    virtual void onExit();
    
    void okmenucallback(CCObject* pSender);
    
};

#endif /* defined(__MyRPG__SelectHero__) */
