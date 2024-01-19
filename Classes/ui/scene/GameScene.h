#pragma once
#include "cocos2d.h"
#include "BaseSingleton.h"
#include "Pipe.h"
#include "Plumping.h"

class GameScene : public cocos2d::Scene
{
public:

    static cocos2d::Scene* createScene();
    virtual bool init() override;

    CREATE_FUNC(GameScene);

private:
    void StartGame();

    void InitListener();
    void InitFruit();
    void InitPlayer();
    void InitBarrier();
    void InitBackGround();
    void InitUI();
    void LoadStar();

    void ResetVisited();
    void NeibourDrop(Entity* pipe, std::vector<Entity*>& entities, bool& isFound);
    void NeibourDrag(Entity* pipe);
    void CheckNeibourDrag(Entity* pipe);
    void CheckNeibourDrop(Entity* pipe);
    void CheckDropPipe();
    void UpdateScore(Entity* entity);
    void GameOver();
    void Victory();
    void WaitingGameDone();
    void CheckEndGame(Entity* pipe);
    void StopEntities();
    void AddLeaderBoard();
    
    void update(float dt);
    void updateTime(float dt);

    bool onContactBegin(cocos2d::PhysicsContact& contact);
    void setPhysicsWorld(cocos2d::PhysicsWorld* world) {}

    virtual void onEnter() override;
    virtual void onExit() override;

    Vector<Entity*> _entities;
    Vector<Entity*> _entitiesByTouch;
    Entity* _pipe;

    std::vector<Sprite*> _lives;
    Sprite* _skill;
    Label* _txtScore;
    Label* _txtLevel;
    Label* _txtTime;

    int _score;
    int _countdown = 1;
    bool _isGameOver;
    float _currentTime = 0.0f;
    float _lastTouchMoveTime;

    int _xScore = 1;
    int _totalTime;
    float _scale = 1.0f;
    int _star;

    Sprite* _spriteTop;
    Sprite* _spriteMid;
    Sprite* _spriteBottom;
    Sprite* _topSkillBasket;
    Sprite* _levelStar;
    cocos2d::Label* _txtMoney;

    Sprite* _board;
    std::vector<Entity*> _pipeSelections;
    std::vector<vector<Entity*>> _matrix;
    std::vector<vector<Vec2>> _matrixPipeSpawnLocation;
    std::vector<vector<Rect>> _matrixPipe;
    std::vector<Plumping*> _plumpings;
};


