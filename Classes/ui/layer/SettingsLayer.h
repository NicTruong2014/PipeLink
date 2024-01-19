#pragma once

#include "cocos2d.h"

class SettingsLayer : public cocos2d::Layer
{
public:

    CREATE_FUNC(SettingsLayer);

    static cocos2d::Scene* createScene();

    virtual bool init() override;

    static void playVibration();
};


