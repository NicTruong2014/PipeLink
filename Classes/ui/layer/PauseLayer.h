#pragma once

#include "cocos2d.h"

class PauseLayer : public cocos2d::Layer
{
public:

    static PauseLayer* create(std::function<void()> callBack)
    {
        PauseLayer* pRet = new(std::nothrow) PauseLayer();

        if (pRet && pRet->init(callBack))
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

    bool init(std::function<void()> callBack);

private:
};


