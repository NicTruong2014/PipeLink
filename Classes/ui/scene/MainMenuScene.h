#pragma once
#include "cocos2d.h"
#include "BaseSingleton.h"

class MainMenuScene : public cocos2d::Scene
{
public:

    static cocos2d::Scene* createScene();

    virtual bool init() override;

    CREATE_FUNC(MainMenuScene);

private:
    void InitBackGround();
    void InitUI();
};