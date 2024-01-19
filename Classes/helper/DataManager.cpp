#include "DataManager.h"
#include "Constant.h"
#include <cocos/base/CCUserDefault.cpp>

#define MAX_LEADERBOARD_ITEM 10

DataManager::~DataManager()
{
}

DataManager::DataManager()
{
}

void DataManager::SaveLeaderBoard(int score, int time)
{
	auto index = MAX_LEADERBOARD_ITEM - 1;
	const std::string keyScore = cocos2d::StringUtils::format("rank_%d_score", index);
	cocos2d::UserDefault::getInstance()->setIntegerForKey(keyScore.c_str(), score);
}

void DataManager::SetLevel(int level)
{
	cocos2d::UserDefault::getInstance()->setIntegerForKey("Level", level);
}

int DataManager::GetLevel()
{
	auto level = cocos2d::UserDefault::getInstance()->getIntegerForKey("Level");
	++level;
	return level;
}

void DataManager::SetLive(int value)
{
	const std::string key = cocos2d::StringUtils::format("live");
	cocos2d::UserDefault::getInstance()->setIntegerForKey(key.c_str(), value);
}

int DataManager::GetLive()
{
	const std::string key = cocos2d::StringUtils::format("live");
	return cocos2d::UserDefault::getInstance()->getIntegerForKey(key.c_str());
}

void DataManager::SetScore(int value)
{
	const std::string keyScore = cocos2d::StringUtils::format("score");
	cocos2d::UserDefault::getInstance()->setIntegerForKey(keyScore.c_str(), value);
}

int DataManager::GetScore()
{
	const std::string keyScore = cocos2d::StringUtils::format("score");
	return cocos2d::UserDefault::getInstance()->getIntegerForKey(keyScore.c_str());
}

void DataManager::SetMoney(int value)
{
	const std::string key = cocos2d::StringUtils::format("money");
	cocos2d::UserDefault::getInstance()->setIntegerForKey(key.c_str(), value);
}

float DataManager::GetMoney()
{
	const std::string key = cocos2d::StringUtils::format("money");
	return cocos2d::UserDefault::getInstance()->getFloatForKey(key.c_str());
}
