#include "LevelManager.h"
#include "DataManager.h"

#define LEFT Director::getInstance()->getVisibleSize().width / 2 - 250
#define RIGHT Director::getInstance()->getVisibleSize().width / 2 + 250

std::vector<LevelConfig> _levelConfigs =
{              //1 2 3 4 5 6 7 8 9 1 1 1
    {{1,5,0,0}, {2,1,0,0,0,0,4,0,1,0,0,0}}, // 1
    {{1,2,0,0}, {2,1,1,1,1,1,6,1,1,1,1,1}},
    {{4,2,0,0}, {0,0,2,0,0,0,3,2,0,0,0,0}},
    {{0,1,5,0}, {2,1,1,0,0,0,4,2,1,0,0,0}},
    {{0,0,4,2}, {4,2,0,0,0,0,1,0,1,0,0,0}},
    {{0,0,1,1}, {2,1,3,0,0,0,0,4,1,0,0,0}},
    {{5,0,0,4}, {4,1,2,0,0,0,1,1,1,0,0,0}},
    {{1,1,4,0}, {4,0,0,1,0,0,4,0,0,0,0,0}},
    {{0,0,1,4}, {9,1,1,0,0,0,1,1,1,0,0,0}},
    {{3,1,0,0}, {2,1,1,0,0,0,3,1,1,0,0,0}}, // 10



    {{1,5,0,0}, {2,1,0,0,0,0,4,0,1,0,0,0}}, // 1
    {{1,2,0,0}, {2,1,1,1,1,1,6,1,1,1,1,1}},
    {{4,2,0,0}, {0,0,2,0,0,0,3,2,0,0,0,0}},
    {{0,1,5,0}, {2,1,1,0,0,0,4,2,1,0,0,0}},
    {{0,0,4,2}, {4,2,0,0,0,0,1,0,1,0,0,0}},
    {{0,0,1,1}, {2,1,3,0,0,0,0,4,1,0,0,0}},
    {{5,0,0,4}, {4,1,2,0,0,0,1,1,1,0,0,0}},
    {{1,1,4,0}, {4,0,0,1,0,0,4,0,0,0,0,0}},
    {{0,0,1,4}, {9,1,1,0,0,0,1,1,1,0,0,0}},
    {{3,1,0,0}, {2,1,1,0,0,0,3,1,1,0,0,0}}, // 10



    {{1,5,0,0}, {2,1,0,0,0,0,4,0,1,0,0,0}}, // 1
    {{1,2,0,0}, {2,1,1,1,1,1,6,1,1,1,1,1}},
    {{4,2,0,0}, {0,0,2,0,0,0,3,2,0,0,0,0}},
    {{0,1,5,0}, {2,1,1,0,0,0,4,2,1,0,0,0}},
    {{0,0,4,2}, {4,2,0,0,0,0,1,0,1,0,0,0}},
    {{0,0,1,1}, {2,1,3,0,0,0,0,4,1,0,0,0}},
    {{5,0,0,4}, {4,1,2,0,0,0,1,1,1,0,0,0}},
    {{1,1,4,0}, {4,0,0,1,0,0,4,0,0,0,0,0}},
    {{0,0,1,4}, {9,1,1,0,0,0,1,1,1,0,0,0}},
    {{3,1,0,0}, {2,1,1,0,0,0,3,1,1,0,0,0}}, // 10



    {{1,5,0,0}, {2,1,0,0,0,0,4,0,1,0,0,0}}, // 1
    {{1,2,0,0}, {2,1,1,1,1,1,6,1,1,1,1,1}},
    {{4,2,0,0}, {0,0,2,0,0,0,3,2,0,0,0,0}},
    {{0,1,5,0}, {2,1,1,0,0,0,4,2,1,0,0,0}},
    {{0,0,4,2}, {4,2,0,0,0,0,1,0,1,0,0,0}},
    {{0,0,1,1}, {2,1,3,0,0,0,0,4,1,0,0,0}},
    {{5,0,0,4}, {4,1,2,0,0,0,1,1,1,0,0,0}},
    {{1,1,4,0}, {4,0,0,1,0,0,4,0,0,0,0,0}},
    {{0,0,1,4}, {9,1,1,0,0,0,1,1,1,0,0,0}},
    {{3,1,0,0}, {2,1,1,0,0,0,3,1,1,0,0,0}}, // 10



    {{1,5,0,0}, {2,1,0,0,0,0,4,0,1,0,0,0}}, // 1
    {{1,2,0,0}, {2,1,1,1,1,1,6,1,1,1,1,1}},
    {{4,2,0,0}, {0,0,2,0,0,0,3,2,0,0,0,0}},
    {{0,1,5,0}, {2,1,1,0,0,0,4,2,1,0,0,0}},
    {{0,0,4,2}, {4,2,0,0,0,0,1,0,1,0,0,0}},
    {{0,0,1,1}, {2,1,3,0,0,0,0,4,1,0,0,0}},
    {{5,0,0,4}, {4,1,2,0,0,0,1,1,1,0,0,0}},
    {{1,1,4,0}, {4,0,0,1,0,0,4,0,0,0,0,0}},
    {{0,0,1,4}, {9,1,1,0,0,0,1,1,1,0,0,0}},
    {{3,1,0,0}, {2,1,1,0,0,0,3,1,1,0,0,0}}, // 10



    {{1,5,0,0}, {2,1,0,0,0,0,4,0,1,0,0,0}}, // 1
    {{1,2,0,0}, {2,1,1,1,1,1,6,1,1,1,1,1}},
    {{4,2,0,0}, {0,0,2,0,0,0,3,2,0,0,0,0}},
    {{0,1,5,0}, {2,1,1,0,0,0,4,2,1,0,0,0}},
    {{0,0,4,2}, {4,2,0,0,0,0,1,0,1,0,0,0}},
    {{0,0,1,1}, {2,1,3,0,0,0,0,4,1,0,0,0}},
    {{5,0,0,4}, {4,1,2,0,0,0,1,1,1,0,0,0}},
    {{1,1,4,0}, {4,0,0,1,0,0,4,0,0,0,0,0}},
    {{0,0,1,4}, {9,1,1,0,0,0,1,1,1,0,0,0}},
    {{3,1,0,0}, {2,1,1,0,0,0,3,1,1,0,0,0}}, // 10



    {{1,5,0,0}, {2,1,0,0,0,0,4,0,1,0,0,0}}, // 1
    {{1,2,0,0}, {2,1,1,1,1,1,6,1,1,1,1,1}},
    {{4,2,0,0}, {0,0,2,0,0,0,3,2,0,0,0,0}},
    {{0,1,5,0}, {2,1,1,0,0,0,4,2,1,0,0,0}},
    {{0,0,4,2}, {4,2,0,0,0,0,1,0,1,0,0,0}},
    {{0,0,1,1}, {2,1,3,0,0,0,0,4,1,0,0,0}},
    {{5,0,0,4}, {4,1,2,0,0,0,1,1,1,0,0,0}},
    {{1,1,4,0}, {4,0,0,1,0,0,4,0,0,0,0,0}},
    {{0,0,1,4}, {9,1,1,0,0,0,1,1,1,0,0,0}},
    {{3,1,0,0}, {2,1,1,0,0,0,3,1,1,0,0,0}}, // 10



    {{1,5,0,0}, {2,1,0,0,0,0,4,0,1,0,0,0}}, // 1
    {{1,2,0,0}, {2,1,1,1,1,1,6,1,1,1,1,1}},
    {{4,2,0,0}, {0,0,2,0,0,0,3,2,0,0,0,0}},
    {{0,1,5,0}, {2,1,1,0,0,0,4,2,1,0,0,0}},
    {{0,0,4,2}, {4,2,0,0,0,0,1,0,1,0,0,0}},
    {{0,0,1,1}, {2,1,3,0,0,0,0,4,1,0,0,0}},
    {{5,0,0,4}, {4,1,2,0,0,0,1,1,1,0,0,0}},
    {{1,1,4,0}, {4,0,0,1,0,0,4,0,0,0,0,0}},
    {{0,0,1,4}, {9,1,1,0,0,0,1,1,1,0,0,0}},
    {{3,1,0,0}, {2,1,1,0,0,0,3,1,1,0,0,0}}, // 10
};

LevelManager::LevelManager()
{
}

void LevelManager::InitLevel()
{
    auto currentLevel = DataManager::getInstance()->GetCurrentLevel();
    _levelConfig = _levelConfigs[currentLevel - 1];
}

LevelConfig LevelManager::GetCurrentLevelConfig()
{
    return _levelConfig;
}

void LevelManager::LevelUp()
{
    auto currentLevel = DataManager::getInstance()->GetCurrentLevel();
    currentLevel++;

    DataManager::getInstance()->SetCurrentLevel(currentLevel);
    DataManager::getInstance()->UnlockLevel(currentLevel);
}
