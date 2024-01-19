#include "LevelManager.h"

#define LEFT Director::getInstance()->getVisibleSize().width / 2 - 250
#define RIGHT Director::getInstance()->getVisibleSize().width / 2 + 250

std::vector<LevelConfig> _levelConfigs =
{
    {{1,2,0,0}, {2,1,1,1,1,1,6,1,1,1,1,1}},
};

LevelManager::LevelManager()
{
}

void LevelManager::InitLevel()
{
    auto currentLevel = cocos2d::UserDefault::getInstance()->getIntegerForKey("Level", 1);
    if (currentLevel > _levelConfigs.size())
    {
        auto random = 1 + rand() % _levelConfigs.size();
        currentLevel = random;
    }

    _levelConfig = _levelConfigs[currentLevel - 1];
}

LevelConfig LevelManager::GetCurrentLevelConfig()
{
    return _levelConfig;
}

void LevelManager::LevelUp()
{
    auto currentLevel = cocos2d::UserDefault::getInstance()->getIntegerForKey("Level");
    currentLevel++;
    cocos2d::UserDefault::getInstance()->setIntegerForKey("Level", currentLevel);
}
