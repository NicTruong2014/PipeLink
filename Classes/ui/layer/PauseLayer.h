#pragma once

#include "cocos2d.h"

class PauseLayer : public cocos2d::Layer
{
public:

    static PauseLayer* create()
    {
        PauseLayer* pRet = new(std::nothrow) PauseLayer();

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

    void SetCallback(std::function<void()> callBack)
    {
        _callBack = callBack;
    }

private:
    std::function<void()> _callBack;
};


