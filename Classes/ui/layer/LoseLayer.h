#pragma once

#include "cocos2d.h"

class LoseLayer : public cocos2d::Layer
{
public:

    static LoseLayer* create(int score)
    {
        LoseLayer* pRet = new(std::nothrow) LoseLayer();

        if (pRet && pRet->init(score))
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

    virtual bool init(int score);

    void SetCallback(std::function<void()> callBack)
    {
        _callBack = callBack;
    }

private:
    void LoadStar(int star);
    std::function<void()> _callBack;
    cocos2d::Sprite* _spriteStar3;
};