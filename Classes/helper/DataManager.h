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
    void SaveLeaderBoard(int score);

    int GetCurrentLevel();
    void SetCurrentLevel(int level);

    void SetScore(int value);
    int GetScore();

    void UnlockLevel(int level);

    void SetDataLevel(TypeSelectLevel type, int level);
    TypeSelectLevel GetDataLevel(int level);
   
private:
    DataManager();
    ~DataManager();

    int _totalLeaderBoard;
};