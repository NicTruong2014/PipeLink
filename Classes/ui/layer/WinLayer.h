#pragma once

#include "cocos2d.h"

class WinLayer : public cocos2d::Layer
{
public:

    static WinLayer* create(int score, int star)
    {
        WinLayer* pRet = new(std::nothrow) WinLayer();

        if (pRet && pRet->init(score, star))
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

    virtual bool init(int score, int star);
    void SetCallback(std::function<void()> callBack)
    {
        _callBack = callBack;
    }

private:
    void LoadStar(int star);

    std::function<void()> _callBack;
    cocos2d::Sprite* _spriteStar3;
};