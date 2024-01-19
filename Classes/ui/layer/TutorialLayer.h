#pragma once
#include "cocos2d.h"

class TutorialLayer : public cocos2d::Layer
{
public:

    static TutorialLayer* create()
    {
        TutorialLayer* pRet = new(std::nothrow) TutorialLayer();

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

private:
    std::vector<cocos2d::Texture2D*> _sprites;
    int _index;
    cocos2d::Sprite* _background;
};


