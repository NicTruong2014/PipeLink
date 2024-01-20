#pragma once
#include "cocos2d.h"

class SelectLevelLayer : public cocos2d::Layer
{
public:

    static SelectLevelLayer* create()
    {
        SelectLevelLayer* pRet = new(std::nothrow) SelectLevelLayer();

        if (pRet && pRet->init())
        {
            pRet->autorelease();
            return pRet;
        }
        else
        {
            delete pRet;
            pRet = nullptr;
            return nullptr;
        }
    }

    virtual bool init();
    void InitLevel(int page);

private:
    int _index;
    cocos2d::Sprite* _background;
};


