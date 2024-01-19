#pragma once

#include "cocos2d.h"

class LeaderboardLayer : public cocos2d::Layer
{
public:

    CREATE_FUNC(LeaderboardLayer);

    static cocos2d::Scene* createScene();

    static void UpdateUserGem(int gem);
    
    static void IncreaseUserGem(int gem);

    static void DecreaseUserGem(int gem);

    static int GetUserGem() {
       return cocos2d::UserDefault::getInstance()->getIntegerForKey("user_gem", 0);
    }

    static int GetUserLevel() {
        return cocos2d::UserDefault::getInstance()->getIntegerForKey("user_level", 1);
    }

    static int GetUserMaxBoat() {
        return cocos2d::UserDefault::getInstance()->getIntegerForKey("user_max_boat", 8);
    }

    void updateHighScore(int newScore);
    void updateHighScore();
    void setCallBackHide(std::function<void()> callBack) { _callBack = callBack; }

private:
    virtual bool init() override;

    std::function<void()> _callBack;
};


