#pragma once
#include "cocos2d.h"
#include "Constant.h"

class DataManager
{
public:
    static DataManager* getInstance() {
        static DataManager instance;
        return &instance;
    }

    int GetTotalLeaderBoard() { return _totalLeaderBoard; }
    void SetTotalLeaderBoard(int value) { _totalLeaderBoard = value; }
    void SaveLeaderBoard(int score, int time);
    void SetLevel(int level);
    int GetLevel();

    void SetScore(int value);
    int GetScore();

    void SetMoney(int value);
    float GetMoney();

    void SetLive(int value);
    int GetLive();
   
private:
    DataManager();
    ~DataManager();

    int _totalLeaderBoard;
};