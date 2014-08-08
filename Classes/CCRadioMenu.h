//
//  CCRadioMenu.h
//  MyRPG
//
//  Created by RocLee on 14-6-30.
//
//

#ifndef __MyRPG__CCRadioMenu__
#define __MyRPG__CCRadioMenu__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class CCRadioMenu : public CCMenu
{
public:
	CCRadioMenu() :m_pLastSelectedItem(NULL){}
	virtual ~CCRadioMenu(){}
	virtual void onEnter();
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
    
    /** creates an empty CCRadioMenu */
    static CCRadioMenu* create();
    
    /** creates a CCRadioMenu with CCMenuItem objects
     * @lua NA
     */
    static CCRadioMenu* create(CCMenuItem* item, ...);
    
    /** creates a CCRadioMenu with a CCArray of CCMenuItem objects
     * @js NA
     */
    static CCRadioMenu* createWithArray(CCArray* pArrayOfItems);
    
    /** creates a CCRadioMenu with it's item, then use addChild() to add
     * other items. It is used for script, it can't init with undetermined
     * number of variables.
     * @js NA
     */
    static CCRadioMenu* createWithItem(CCMenuItem* item);
    
    /** creates a CCRadioMenu with CCMenuItem objects
     * @js NA
     * @lua NA
     */
    static CCRadioMenu* createWithItems(CCMenuItem *firstItem, va_list args);
protected:
	CCMenuItem* m_pLastSelectedItem;
};


#endif /* defined(__MyRPG__CCRadioMenu__) */
