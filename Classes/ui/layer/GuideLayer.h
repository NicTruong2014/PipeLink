#pragma once
#include "cocos2d.h"

class GuideLayer : public cocos2d::Layer
{
public:

    static GuideLayer* create()
    {
        GuideLayer* pRet = new(std::nothrow) GuideLayer();

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
    std::vector<cocos2d::Texture2D*> _sprites;
    int _index;
    cocos2d::Sprite* _background;
    std::function<void()> _callBack;
};


