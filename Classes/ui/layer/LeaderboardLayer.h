#pragma once

#include "cocos2d.h"

class LeaderboardLayer : public cocos2d::Layer
{
public:

    CREATE_FUNC(LeaderboardLayer);

    static cocos2d::Scene* createScene();

    void updateHighScore(int newScore);
    void updateHighScore();
    void setCallBackHide(std::function<void()> callBack) { _callBack = callBack; }

private:
    virtual bool init() override;

    std::function<void()> _callBack;
};


