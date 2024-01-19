#pragma once

#include "cocos2d.h"
#include "Pipe.h"
#include "Plumping.h"

struct LevelConfig
{
public:
    LevelConfig() :PlumpingPlaces(), Pipes(){}
    LevelConfig(std::vector<int> plumpingPlaces, std::vector<int> pipes)
        : PlumpingPlaces(plumpingPlaces), Pipes(pipes) {}

    std::vector<int> PlumpingPlaces;
    std::vector<int> Pipes;
};

class LevelManager {
public:
    static LevelManager* getInstance() {
        static LevelManager instance;
        return &instance;
    }

    LevelManager();
    LevelConfig GetCurrentLevelConfig();
    void LevelUp();
    void InitLevel();

private:

    LevelConfig _levelConfig;
};