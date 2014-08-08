//
//  CCRadioMenu.cpp
//  MyRPG
//
//  Created by RocLee on 14-6-30.
//
//

#include "CCRadioMenu.h"


CCRadioMenu* CCRadioMenu::create()
{
	return CCRadioMenu::create(NULL, NULL);
}

CCRadioMenu * CCRadioMenu::create(CCMenuItem* item, ...)
{
	va_list args;
	va_start(args, item);
    
	CCRadioMenu *pRet = CCRadioMenu::createWithItems(item, args);
    
	va_end(args);
    
	return pRet;
}

CCRadioMenu* CCRadioMenu::createWithArray(CCArray* pArrayOfItems)
{
	CCRadioMenu *pRet = new CCRadioMenu();
	if (pRet && pRet->initWithArray(pArrayOfItems))
	{
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}
    
	return pRet;
}

CCRadioMenu* CCRadioMenu::createWithItems(CCMenuItem* item, va_list args)
{
	CCArray* pArray = NULL;
	if (item)
	{
		pArray = CCArray::create(item, NULL);
		CCMenuItem *i = va_arg(args, CCMenuItem*);
		while (i)
		{
			pArray->addObject(i);
			i = va_arg(args, CCMenuItem*);
		}
	}
    
	return CCRadioMenu::createWithArray(pArray);
}

CCRadioMenu* CCRadioMenu::createWithItem(CCMenuItem* item)
{
	return CCRadioMenu::create(item, NULL);
}

void CCRadioMenu::onEnter()
{
	CCMenu::onEnter();
	if (m_pChildren->count()>0){
        //初始状态第一个MenuItem被选中
        if (!m_pLastSelectedItem){
            CCMenuItem* pFirstItem=(CCMenuItem*)(m_pChildren->objectAtIndex(0));
            pFirstItem->selected();
            m_pLastSelectedItem = pFirstItem;
        }
	}
}

bool CCRadioMenu::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	CC_UNUSED_PARAM(event);
	if (m_eState != kCCMenuStateWaiting || !m_bVisible /*|| !m_bEnabled*/)
	{
		return false;
	}
    
	for (CCNode *c = this->m_pParent; c != NULL; c = c->getParent())
	{
		if (c->isVisible() == false)
		{
			return false;
		}
	}
    
	m_pSelectedItem = this->itemForTouch(touch);
	if (m_pSelectedItem)
	{
		m_eState = kCCMenuStateTrackingTouch;
		m_pSelectedItem->selected();
        //上一个被选中的改为未被选中
		if (m_pLastSelectedItem&&m_pLastSelectedItem!=m_pSelectedItem)
		{
			m_pLastSelectedItem->unselected();
		}
		
		return true;
	}
	return false;
}

void CCRadioMenu::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	CC_UNUSED_PARAM(touch);
	CC_UNUSED_PARAM(event);
	CCAssert(m_eState == kCCMenuStateTrackingTouch, "[Menu ccTouchEnded] -- invalid state");
	if (m_pSelectedItem)
	{
        //这里注释掉触摸松开后还是处于被选中状态
		//m_pSelectedItem->unselected();
		m_pSelectedItem->activate();
		m_pLastSelectedItem = m_pSelectedItem;
	}
	m_eState = kCCMenuStateWaiting;
}
