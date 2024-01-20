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

void DataManager::SaveLeaderBoard(int score)
{
	auto index = MAX_LEADERBOARD_ITEM - 1;
	const std::string keyScore = cocos2d::StringUtils::format("rank_%d_score", index);
	cocos2d::UserDefault::getInstance()->setIntegerForKey(keyScore.c_str(), score);
}

int DataManager::GetCurrentLevel()
{
	const std::string keyScore = cocos2d::StringUtils::format("current_level");
	return cocos2d::UserDefault::getInstance()->getIntegerForKey(keyScore.c_str());
}

void DataManager::SetCurrentLevel(int level)
{
	const std::string keyScore = cocos2d::StringUtils::format("current_level");
	cocos2d::UserDefault::getInstance()->setIntegerForKey(keyScore.c_str(), level);
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

void DataManager::UnlockLevel(int level)
{
	SetDataLevel(TypeSelectLevel::Star0, level);
}

void DataManager::SetDataLevel(TypeSelectLevel type, int level)
{
	const std::string key = cocos2d::StringUtils::format("type_select_level_%d", level);
	cocos2d::UserDefault::getInstance()->setIntegerForKey(key.c_str(), (int)type);
}

TypeSelectLevel DataManager::GetDataLevel(int level)
{
	const std::string key = cocos2d::StringUtils::format("type_select_level_%d", level);
	return (TypeSelectLevel)cocos2d::UserDefault::getInstance()->getIntegerForKey(key.c_str(), (int)TypeSelectLevel::Block);
}
