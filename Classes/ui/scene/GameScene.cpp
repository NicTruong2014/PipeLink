﻿#include "GameScene.h"
#include "PauseLayer.h"
#include "SettingsLayer.h"
#include "LeaderboardLayer.h"
#include "SoundManager.h"
#include "AnimationManager.h"
#include "LevelManager.h"
#include "DataManager.h"
#include "Utils.h"
#include "WinLayer.h"
#include "LoseLayer.h"
#include "GuideLayer.h"
#include "TutorialLayer.h"
#include "HelperManager.h"

USING_NS_CC;

#define ORDER_POPUP 3
#define ORDER_POPUP 999
#define ORDER_UI 3
#define DEBUG_ 0

Scene* GameScene::createScene()
{
    auto scene = Scene::createWithPhysics();

#if DEBUG_PHYSIC
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
#endif //  DEBUG

    if (scene)
    {
        auto view = GameScene::create();
        scene->addChild(view);
    }
    else
    {
        CC_SAFE_DELETE(scene);
    }

    return scene;
}

void GameScene::StartGame()
{
    SOUND_MANAGER->stopAllBackgroundMusics();

    _countdown = 3;

    if(Utils::IsIPadAspectRatio())
    {
        _scale = 0.66f;
    }

    auto backgroundLayer = cocos2d::LayerColor::create(cocos2d::Color4B(0, 0, 0, 150));
    this->addChild(backgroundLayer);

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    auto levelConfig = LevelManager::getInstance()->GetCurrentLevelConfig();

    SOUND_MANAGER->playGameMusic(true);

    InitFruit();
    InitPlayer();
    InitBarrier();

    _totalTime = 120;

    this->schedule(schedule_selector(GameScene::updateTime), 1.0f);
}

void GameScene::InitListener()
{
    auto touchListener = EventListenerTouchOneByOne::create();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto sensivetive = 1.2f;
    std::string labelText = "";
    auto label = cocos2d::Label::createWithSystemFont(labelText, "Arial", 20);
    label->setPosition(cocos2d::Vec2(100, 100)); // Đặt chữ giữa hình chữ nhật
    this->addChild(label);

    touchListener->onTouchMoved = [=](const Touch* touch, Event* event)
    {
        auto touchPos = touch->getLocation();
        auto previousTouchPos = touch->getPreviousLocation();
        auto touchDelta = touchPos - previousTouchPos;
        auto convertBox = _board->convertToNodeSpace(touchPos);
#if DEBUG_
        label->setString(StringUtils::format("%d %d", (int)convertBox.x, (int)convertBox.y));
#endif
        if (_pipe == NULL)
        {
            return true;
        }

        if (_isGameOver)
        {
            return true;
        }

        _pipe->setZOrder(10);
        _pipe->setPosition(convertBox);

        return true;
    };

    touchListener->onTouchBegan = [=](const Touch* touch, Event* event)
    {
        if (_isGameOver)
        {
            return true;
        }

        auto touchPos = touch->getLocation();
        for (auto i = 0; i < _pipeSelections.size(); i++)
        {
            auto pipe = _pipeSelections[i];
            auto box = Rect(pipe->getPosition().x - SizePipe.x / 2, pipe->getPosition().y - SizePipe.y / 2, SizePipe.x, SizePipe.y);
            auto convertBox = _board->convertToNodeSpace(touchPos);
            
            if (box.containsPoint(convertBox))
            {
                _pipe = pipe;
                _pipe->SetNeibour(false);

                UpdateLabelPipe(_pipe, -1);

                auto locationMatrix = pipe->GetLocationMatrix();
                if (locationMatrix.x > 0 && locationMatrix.x < 6 && locationMatrix.y > 0 && locationMatrix.y < 6)
                {
                    _matrix[locationMatrix.x][locationMatrix.y] = NULL;
                    _pipe->SetVisied(false);
                    _pipe->SetNeibour(false);

                    CheckNeibourDrag(_pipe);
                    UpdateScore();

                    _pipe->SetLocationMatrix(Vec2(-1, -1));

                    break;
                }

                break;
            }
        }

        return true;
    };

    touchListener->onTouchEnded = [=](const Touch* touch, Event* event)
    {
        if (_isGameOver)
        {
            return false;
        }

        if (_pipe == NULL)
        {
            return true;
        }

        _pipe->setLocalZOrder(1);
        CheckDropPipe();

        return true;
    };

    touchListener->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    auto contactListener = cocos2d::EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}

void GameScene::InitFruit()
{
    auto levelConfig = LevelManager::getInstance()->GetCurrentLevelConfig();
}

void GameScene::InitBarrier()
{
}

void GameScene::InitPlayer()
{
}

void GameScene::InitBackGround()
{
    _matrixPipeSpawnLocation.resize(7, std::vector<Vec2>(0, Vec2::ZERO));
    _matrixPipe.resize(7, std::vector<Rect>(0, Rect()));
    _matrix.resize(7, std::vector<Entity*>(7, NULL));
    _pipeSelections.resize(0);

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    _board = Sprite::create("Sprites/News/ui/pl_ui_board.png");
    _board->setScale(_scale);
    _board->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    _board->setLocalZOrder(1);
    this->addChild(_board);

    //initmatrix
    auto defaultSpawnX = _board->getContentSize().width / 2 + -5 * SizePipe.x;
    auto defaultSpawnY = _board->getContentSize().height / 2 + -1 * SizePipe.y;
    auto indexBlock = 1;

    for (auto i = 0; i < 4; i++)
    {
        for (auto j = 0; j < 3; j++)
        {
            if (i == 2)
            {
                defaultSpawnX = _board->getContentSize().width / 2 + 2 * SizePipe.x;
            }

            auto x = defaultSpawnX + i * SizePipe.x + i * 10;
            auto y = defaultSpawnY + j * SizePipe.y + j * 60;

            _matrixPipeSpawnLocation[i].push_back(Vec2(x,y));

            auto block = Sprite::create(StringUtils::format("Sprites/News/pipe/pl_pad_block_%d.png", indexBlock));
            block->setPosition(Vec2(x, y));
            _board->addChild(block);
            indexBlock++;
        }
    }

    auto defaultX = _board->getContentSize().width / 2 + -4 * SizePipe.x + SizePipe.x / 2;
    auto defaultY = _board->getContentSize().height / 2 + -3 * SizePipe.y - SizePipe.y / 2;
    auto drawNode = cocos2d::DrawNode::create();

    _board->addChild(drawNode);

    for (auto i = 0; i < 7; i++)
    {
        for (auto j = 0; j < 7; j++)
        {
            auto x = defaultX + i * SizePipe.x;
            auto y = defaultY + j * SizePipe.y;

            _matrixPipe[i].push_back(Rect(x, y, SizePipe.x, SizePipe.y));

#if DEBUG_
            float width = 120;
            float height = 120;

            cocos2d::Color4F borderColor(1.0f, 1.0f, 1.0f, 1.0f); // RGBA (1, 1, 1, 1) - màu trắng

            drawNode->drawRect(cocos2d::Vec2(x, y), cocos2d::Vec2(x + width, y + height), borderColor);

            std::string labelText = StringUtils::format("%d %d", i, j);
            auto label = cocos2d::Label::createWithSystemFont(labelText, "Arial", 20);
            label->setPosition(cocos2d::Vec2(x + width / 2, y + height / 2)); // Đặt chữ giữa hình chữ nhật
            _board->addChild(label);

            std::string labelText2 = StringUtils::format("%d %d", (int)x, (int)y);
            auto label2 = cocos2d::Label::createWithSystemFont(labelText2, "Arial", 20);
            label2->setPosition(cocos2d::Vec2(x + width / 2, y + height / 3)); // Đặt chữ giữa hình chữ nhật
            _board->addChild(label2);
#endif
        }
    }

    //init pipe
    auto levelManager = LevelManager::getInstance();
    auto levelConfig = levelManager->GetCurrentLevelConfig();
    auto pipesRow = levelConfig.Pipes;
    auto indexRow = 0;
    auto indexCol = 0;

    for (auto i = 0 ; i < pipesRow.size(); i++)
    {
        auto pipeRow = pipesRow[i];

        if (indexRow == 3)
        {
            indexRow = 0;
            indexCol++;
        }

        auto index = i + 1;
        auto number = cocos2d::Label::createWithTTF("1", "fonts/SVNMergeBold.ttf", 40);

        number->setPosition(Vec2(_matrixPipeSpawnLocation[indexCol][indexRow].x, _matrixPipeSpawnLocation[indexCol][indexRow].y + 85));
        number->setMaxLineWidth(4);
        _board->addChild(number);
        _labelPipes.insert(std::make_pair(TypePipe(index), number));

        if (pipeRow != 0)
        {
            for (auto j = 0; j < pipeRow;j++)
            {
                auto pipe = Pipe::create(TypePipe(index));
                auto x = _matrixPipeSpawnLocation[indexCol][indexRow].x;
                auto y = _matrixPipeSpawnLocation[indexCol][indexRow].y;

                pipe->SetLocationMatrix(Vec2(-1, -1));
                pipe->SetLocationSpawn(Vec2(x, y));
                pipe->setPosition(Vec2(x, y));

                _board->addChild(pipe);
                _pipeSelections.push_back(pipe);
            }
        }

        _amountPipes.insert(std::make_pair(TypePipe(index), pipeRow));
        _labelPipes.at(TypePipe(index))->setString(std::to_string(pipeRow));
        indexRow++;
    }

    //init plumping
    auto plumpingPlaces = levelConfig.PlumpingPlaces;

    if (plumpingPlaces[0] != 0)
    {
        //Left
        auto plumping = Plumping::create(TypePipe::PlumpingLeft);
        auto row = plumpingPlaces[0];
        auto delta = Vec2(SizePipe.x / 2 + 22, SizePipe.y / 2);

        _board->addChild(plumping);
        plumping->setPosition(_matrixPipe[0][row].origin + delta);
        plumping->SetLocationMatrix(Vec2(0, row));

        _matrix[0][row] = plumping;
        _plumpings.push_back(plumping);
    }
    if (plumpingPlaces[1] != 0)
    {
        //right
        auto plumping = Plumping::create(TypePipe::PlumpingRight);
        auto row = plumpingPlaces[1];
        auto delta = Vec2(SizePipe.x / 2 - 22, SizePipe.y / 2);

        _board->addChild(plumping);
        plumping->setPosition(_matrixPipe[6][row].origin + delta);
        plumping->SetLocationMatrix(Vec2(6, row));

        _matrix[6][row] = plumping;
        _plumpings.push_back(plumping);
    }
    if (plumpingPlaces[2] != 0)
    {
        //Top
        auto plumping = Plumping::create(TypePipe::PlumpingTop);
        auto col = plumpingPlaces[2];
        auto delta = Vec2(SizePipe.x / 2, SizePipe.y / 2 - 22);

        _board->addChild(plumping);
        plumping->setPosition(_matrixPipe[col][6].origin + delta);
        plumping->SetLocationMatrix(Vec2(col, 6));

        _matrix[col][6] = plumping;
        _plumpings.push_back(plumping);
    }
    if (plumpingPlaces[3] != 0)
    {
        //Bottom
        auto plumping = Plumping::create(TypePipe::PlumpingBottom);
        auto col = plumpingPlaces[3];
        auto delta = Vec2(SizePipe.x / 2, SizePipe.y / 2 + 22);

        _board->addChild(plumping);
        plumping->setPosition(_matrixPipe[col][0].origin + delta);
        plumping->SetLocationMatrix(Vec2(col, 0));

        _matrix[col][0] = plumping;
        _plumpings.push_back(plumping);
    }
}

void GameScene::InitUI()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto level = DataManager::getInstance()->GetCurrentLevel();

    auto posTopTime = Vec2(-158, 0);
    auto posTopLevel = Vec2(-424, 0);
    auto posTopStar = Vec2(160, 0);
    auto posTopRank = Vec2(508, 0);
    auto posTopPause = Vec2(758, 0);

    //Time
    auto topTime = Sprite::create("Sprites/News/ui/pl_ui_time.png");
    topTime->setScale(_scale);
    topTime->setPosition(Vec2(visibleSize.width / 2 + posTopTime.x, visibleSize.height - topTime->getContentSize().height + 20));
    topTime->setZOrder(ORDER_UI);
    this->addChild(topTime);

    auto totalTime = (int)_totalTime;
    auto formattedTime = StringUtils::format("%02d:%02d", totalTime / 60, totalTime % 60);
    _txtTime = cocos2d::Label::createWithTTF("00:00", "fonts/SVNMergeBold.ttf", 40);
    _txtTime->setString(formattedTime);
    _txtTime->setPosition(Vec2(topTime->getContentSize().width / 2 + 50, topTime->getContentSize().height / 2 + 5));
    _txtTime->setAnchorPoint({ 0.5,0.5 });
    _txtTime->setZOrder(ORDER_UI);
    topTime->addChild(_txtTime);

    //Top
    auto topLv = Sprite::create("Sprites/News/ui/pl_ui_level.png");
    topLv->setScale(_scale);
    topLv->setPosition(Vec2(visibleSize.width / 2 + posTopLevel.x, visibleSize.height - topTime->getContentSize().height + 20));
    topLv->setLocalZOrder(ORDER_UI);
    this->addChild(topLv);

    auto labelLevel = cocos2d::Label::createWithTTF("999999", "fonts/SVNMergeBold.ttf", 40);
    labelLevel->setPosition(Vec2(topLv->getContentSize().width / 2 + 50, topLv->getContentSize().height / 2 + 5));
    labelLevel->setAnchorPoint({ 0.5,0.5 });
    labelLevel->setString(std::to_string(level));
    labelLevel->setZOrder(ORDER_UI);
    topLv->addChild(labelLevel);

    _levelStar = Sprite::create("Sprites/News/ui/pl_ui_star.png");
    _levelStar->setScale(_scale);
    _levelStar->setPosition(Vec2(visibleSize.width / 2 + posTopStar.x, visibleSize.height - topTime->getContentSize().height + 20));
    _levelStar->setZOrder(ORDER_UI);
    this->addChild(_levelStar);

    for (auto i = 0; i < 3; i++)
    {
        auto star = Sprite::create("Sprites/News/ui/pl_ui_star_off.png");

        star->setPosition(Vec2(_levelStar->getContentSize().width / 2 + i * 65 - 15, _levelStar->getContentSize().height / 2 + 5));
        _levelStar->addChild(star);
    }

    //Rank
    auto topRank = Sprite::create("Sprites/News/ui/pl_ui_score.png");
    topRank->setScale(_scale);
    topRank->setPosition(Vec2(visibleSize.width / 2 + posTopRank.x, visibleSize.height - topTime->getContentSize().height + 20));
    topRank->setZOrder(ORDER_UI);
    this->addChild(topRank);

    _txtScore = cocos2d::Label::createWithTTF("1", "fonts/SVNMergeBold.ttf", 40);
    _txtScore->setAnchorPoint({ 0.5,0.5 });
    _txtScore->setPosition(Vec2(topRank->getContentSize().width / 2 + 50, topRank->getContentSize().height / 2 + 5));
    _txtScore->enableOutline(Color4B(0, 0, 0, 255), 1);
    _txtScore->setString(std::to_string(_score));
    _txtScore->setZOrder(ORDER_UI);
    topRank->addChild(_txtScore);

    auto pauseButton = cocos2d::ui::Button::create("Sprites/News/icon/pl_icon_pause.png");
    pauseButton->setZOrder(ORDER_UI);
    pauseButton->setScale(_scale);
    pauseButton->setPressedActionEnabled(true);
    pauseButton->setPosition(Vec2(visibleSize.width / 2 + posTopPause.x, visibleSize.height - topTime->getContentSize().height + 20));
    pauseButton->addClickEventListener([=](Ref* sender)
    {
        SOUND_MANAGER->playClickEffect();
        if (_isGameOver)
        {
            return;
        }

        auto layer = PauseLayer::create();

        layer->setLocalZOrder(ORDER_POPUP);
        layer->setName("PauseLayer");
        this->addChild(layer);

        ANIMATION_MANAGER->transitionSlideIn(AnimationManager::Direction::LEFT, 0.25f, utils::findChild(layer, "background"));

    });

    this->addChild(pauseButton);

    LoadStar();
}

void GameScene::LoadStar()
{
    auto level = DataManager::getInstance()->GetCurrentLevel();
    auto levelData = DataManager::getInstance()->GetDataLevel(level);

    for (auto i = 0; i < (int)levelData; i++)
    {
        auto star = Sprite::create("Sprites/News/ui/pl_ui_star_on.png");

        star->setPosition(Vec2(_levelStar->getContentSize().width / 2 + i * 65 - 15, _levelStar->getContentSize().height / 2 + 5));
        _levelStar->addChild(star);
    }
}

void GameScene::ResetVisited()
{
    for (auto i = 0; i < 7; i++)
    {
        for (auto j = 0; j < 7; j++)
        {
            auto pipe = _matrix[i][j];
            if (pipe != NULL)
            {
                pipe->SetVisied(false);
            }
        }
    }
}

void GameScene::NeibourDrop(Entity* pipe, std::vector<Entity*>& entities, bool& isFoundPlumping)
{
    auto left = Vec2(-1, 0);
    auto right = Vec2(1, 0);
    auto top = Vec2(0, 1);
    auto bottom = Vec2(0, -1);
    auto locationMatrix = pipe->GetLocationMatrix();
    auto directions = pipe->GetDirections();
    vector<Entity*> lstEntities;

    if (pipe->GetVisited())
    {
        return;
    }

    pipe->SetVisied(true);
    
    for (auto direction : directions)
    {
        if (direction == TypeDirection::Left)
        {
            //left
            auto location = Vec2(locationMatrix.x + left.x, locationMatrix.y + left.y);
            if (Utils::IsValidLocation(location))
            {
                auto leftPipe = _matrix[location.x][location.y];
                if (leftPipe != NULL)
                {
                    if (Utils::CanNeibour(direction, leftPipe->GetTypePipe()))
                    {
                        if (Utils::IsPlumping(leftPipe->GetTypePipe()))
                        {
                            isFoundPlumping = true;
                        }

                        pipe->SetFullDirection(direction, true);
                        entities.push_back(leftPipe);
                        lstEntities.push_back(leftPipe);
                    }
                    else pipe->SetFullDirection(direction, false);
                }
                else pipe->SetFullDirection(direction, false);
            }
            else pipe->SetFullDirection(direction, false);
        }
        else if (direction == TypeDirection::Right)
        {
            auto location = Vec2(locationMatrix.x + right.x, locationMatrix.y + right.y);
            if (Utils::IsValidLocation(location))
            {
                auto rightPipe = _matrix[location.x][location.y];
                if (rightPipe != NULL)
                {
                    if (Utils::CanNeibour(direction, rightPipe->GetTypePipe()))
                    {
                        if (Utils::IsPlumping(rightPipe->GetTypePipe()))
                        {
                            isFoundPlumping = true;
                        }

                        pipe->SetFullDirection(direction, true);
                        entities.push_back(rightPipe);
                        lstEntities.push_back(rightPipe);
                    }
                    else pipe->SetFullDirection(direction, false);
                }
                else pipe->SetFullDirection(direction, false);
            }
            else pipe->SetFullDirection(direction, false);
        }
        else if (direction == TypeDirection::Top)
        {
            auto location = Vec2(locationMatrix.x + top.x, locationMatrix.y + top.y);
            if (Utils::IsValidLocation(location))
            {
                auto topPipe = _matrix[location.x][location.y];
                if (topPipe != NULL)
                {
                    if (Utils::CanNeibour(direction, topPipe->GetTypePipe()))
                    {
                        if (Utils::IsPlumping(topPipe->GetTypePipe()))
                        {
                            isFoundPlumping = true;
                        }

                        pipe->SetFullDirection(direction, true);
                        entities.push_back(topPipe);
                        lstEntities.push_back(topPipe);
                    }
                    else pipe->SetFullDirection(direction, false);
                }
                else pipe->SetFullDirection(direction, false);
            }
            else pipe->SetFullDirection(direction, false);
        }
        else if (direction == TypeDirection::Bottom)
        {
            auto location = Vec2(locationMatrix.x + bottom.x, locationMatrix.y + bottom.y);
            if (Utils::IsValidLocation(location))
            {
                auto bottomPipe = _matrix[location.x][location.y];
                if (bottomPipe != NULL)
                {
                    if (Utils::CanNeibour(direction, bottomPipe->GetTypePipe()))
                    {
                        if (Utils::IsPlumping(bottomPipe->GetTypePipe()))
                        {
                            isFoundPlumping = true;
                        }

                        pipe->SetFullDirection(direction, true);
                        entities.push_back(bottomPipe);
                        lstEntities.push_back(bottomPipe);
                    }
                    else pipe->SetFullDirection(direction, false);
                }
                else pipe->SetFullDirection(direction, false);
            }
            else pipe->SetFullDirection(direction, false);
        }
    }

    for (auto lstEntity : lstEntities)
    {
        NeibourDrop(lstEntity, entities, isFoundPlumping);
    }
}

void GameScene::NeibourDrag(Entity* pipe)
{
    auto left = Vec2(-1, 0);
    auto right = Vec2(1, 0);
    auto top = Vec2(0, 1);
    auto bottom = Vec2(0, -1);
    auto locationMatrix = pipe->GetLocationMatrix();
    auto directions = pipe->GetDirections();
    vector<Entity*> lstEntities;

    if (pipe->GetVisited())
    {
        return;
    }

    pipe->SetVisied(true);

    for (auto direction : directions)
    {
        if (direction == TypeDirection::Left)
        {
            //left
            auto location = Vec2(locationMatrix.x + left.x, locationMatrix.y + left.y);
            if (Utils::IsValidLocation(location))
            {
                auto leftPipe = _matrix[location.x][location.y];
                if (leftPipe != NULL)
                {
                    if (Utils::CanNeibour(direction, leftPipe->GetTypePipe()))
                    {

                        lstEntities.push_back(leftPipe);
                    }
                }
            }
        }
        else if (direction == TypeDirection::Right)
        {
            auto location = Vec2(locationMatrix.x + right.x, locationMatrix.y + right.y);
            if (Utils::IsValidLocation(location))
            {
                auto rightPipe = _matrix[location.x][location.y];
                if (rightPipe != NULL)
                {
                    if (Utils::CanNeibour(direction, rightPipe->GetTypePipe()))
                    {
                        lstEntities.push_back(rightPipe);
                    }
                }
            }
        }
        else if (direction == TypeDirection::Top)
        {
            auto location = Vec2(locationMatrix.x + top.x, locationMatrix.y + top.y);
            if (Utils::IsValidLocation(location))
            {
                auto topPipe = _matrix[location.x][location.y];
                if (topPipe != NULL)
                {
                    if (Utils::CanNeibour(direction, topPipe->GetTypePipe()))
                    {
                        lstEntities.push_back(topPipe);

                    }
                }
            }
           
        }
        else if (direction == TypeDirection::Bottom)
        {
            auto location = Vec2(locationMatrix.x + bottom.x, locationMatrix.y + bottom.y);
            if (Utils::IsValidLocation(location))
            {
                auto bottomPipe = _matrix[location.x][location.y];
                if (bottomPipe != NULL)
                {
                    if (Utils::CanNeibour(direction, bottomPipe->GetTypePipe()))
                    {
                        lstEntities.push_back(bottomPipe);
                    }
                }
            }
        }
    }

    for (auto lstEntity : lstEntities)
    {
        CheckNeibourDrop(lstEntity);
    }
}

void GameScene::CheckNeibourDrop(Entity* pipe)
{
    std::vector<Entity*> entities;
    bool isFound = false;

    ResetVisited();

    entities.push_back(pipe);
    NeibourDrop(pipe, entities, isFound);

    std::vector<Entity*> plumpings;
    for (auto entity : entities)
    {
        entity->SetNeibour(isFound);
    }
}

void GameScene::CheckNeibourDrag(Entity* pipe)
{
    ResetVisited();
    NeibourDrag(pipe);
}

void GameScene::CheckDropPipe()
{
    for (auto i = 0; i < 7; i++)
    {
        for (auto j = 0; j < 7; j++)
        {
            auto centerPos = _pipe->getPosition();
            auto box = Rect(_matrixPipe[i][j].origin.x, _matrixPipe[i][j].origin.y, _matrixPipe[i][j].size.width, _matrixPipe[i][j].size.height);

            if (box.containsPoint(centerPos))
            {
                auto pipe = _pipe;
                if (i == 0 || i == 6 || j == 0 || j == 6)
                {
                    continue;
                }

                if (_matrix[i][j] != NULL)
                {
                    break;
                }

                pipe->SetLocationMatrix(Vec2(i, j));
                _pipe->setPosition(_matrixPipe[i][j].origin + Vec2(SizePipe.x / 2, SizePipe.y / 2));
                _matrix[i][j] = _pipe;

                CheckNeibourDrop(_pipe);
                UpdateScore();
                CheckEndGame(_pipe);

                _pipe = NULL;
                return;
            }
        }
    }

    ((Pipe*)_pipe)->DropPipe();
    _pipe->SetLocationMatrix(Vec2(-1, -1));

    CheckNeibourDrag(_pipe);
    UpdateScore();
    UpdateLabelPipe(_pipe, 1);

    _pipe = NULL;
}

void GameScene::UpdateScore()
{
    auto score = 0;
    for (auto i = 0; i < 7; i++)
    {
        for (auto j = 0; j < 7; j++)
        {
            auto pipe = _matrix[i][j];
            if (pipe != NULL && pipe->GetNeibour() && Utils::IsPipe(pipe->GetTypePipe()))
            {
                score += 1000;
            }
        }
    }

    _score = score;
    _txtScore->setString(std::to_string(score));
}

void GameScene::GameOver()
{
    _isGameOver = true;
    StopEntities();

    this->runAction(Sequence::create(DelayTime::create(0.5f), CallFunc::create([=]() {
        AddLeaderBoard();
        SoundManager::GetInstance()->pauseAllBackgroundMusics();

        Director::getInstance()->getScheduler()->setTimeScale(0.0f);

        auto loseLayer = LoseLayer::create(_score);
        loseLayer->SetCallback([=]()
        {
            Director::getInstance()->getScheduler()->setTimeScale(1.0f);
        });
        loseLayer->setZOrder(ORDER_POPUP);
        this->addChild(loseLayer);
    }), nullptr));
}

void GameScene::Victory()
{
    _isGameOver = true;

    StopEntities();

    SoundManager::GetInstance()->stopAllBackgroundMusics();
    LevelManager::getInstance()->LevelUp();
    
    this->runAction(Sequence::create(DelayTime::create(0.5f), CallFunc::create([=]() {
        AddLeaderBoard();

        Director::getInstance()->getScheduler()->setTimeScale(0.0f);

        SoundManager::GetInstance()->playWinEffect();
        auto winLayer = WinLayer::create(_score, 3);
        winLayer->SetCallback([=]() 
        {
            Director::getInstance()->getScheduler()->setTimeScale(1.0f);
        });
        winLayer->setZOrder(ORDER_POPUP);
        this->addChild(winLayer);
    }), nullptr));
}

void GameScene::WaitingGameDone()
{
    
}

void GameScene::CheckEndGame(Entity* pipe)
{
    std::vector<Entity*> entities;
    bool isFound = false;
    bool isFullDirection = true;

    ResetVisited();
    entities.push_back(pipe);
    NeibourDrop(pipe, entities, isFound);

    std::vector<Entity*> plumpings;
    for (auto entity : entities)
    {
        if (!entity->IsFullDirection())
        {
            isFullDirection = false;
            break;
        }

        //Check End Game
        if (Utils::IsPlumping(entity->GetTypePipe()))
        {
            bool isFoundPlumping = false;
            for (auto i = 0; i < plumpings.size();i++)
            {
                if (plumpings[i]->GetTypePipe() == entity->GetTypePipe())
                {
                    isFoundPlumping = true;
                    break;
                }
            }

            if (!isFoundPlumping) plumpings.push_back(entity);
        }
    }

    //Check End Game
    if (!isFullDirection)
    {
        return;
    }

    if (plumpings.size() == _plumpings.size())
    {
        Victory();
    }
}

void GameScene::StopEntities()
{
    for (auto i = 0; i < _entities.size(); i++)
    {
        auto entity = _entities.at(i);
        if (entity != nullptr && entity->IsAlive)
        {
            entity->CustomPause();

            auto blink = cocos2d::Blink::create(0.25f, 3);
            entity->runAction(Sequence::create(blink, CallFunc::create([=]() {
            }), nullptr));
        }
    }
}

void GameScene::updateTime(float dt)
{
    _totalTime--;
    auto totalTime = (int)_totalTime;
    auto formattedTime = StringUtils::format("%02d:%02d", totalTime / 60, totalTime % 60);
    _txtTime->setString((formattedTime));
    if (_totalTime <= 0)
    {
        unschedule(schedule_selector(GameScene::updateTime));
        GameOver();
    }
}

void GameScene::update(float dt)
{
    if (_isGameOver) 
    {
        return;
    }
}

void GameScene::AddLeaderBoard()
{
    auto score = _score;
    auto dataManager = DataManager::getInstance();
    auto totalLeaderBoard = dataManager->GetTotalLeaderBoard();

    dataManager->SaveLeaderBoard(_score);
}

void GameScene::UpdateLabelPipe(Entity* pipe, int value)
{
    if (pipe->GetLocationMatrix() != Vec2(-1, -1)) return;

    auto amount = _amountPipes.at(pipe->GetTypePipe());
    amount += value;

    _amountPipes.at(pipe->GetTypePipe()) = amount;
    _labelPipes.at(pipe->GetTypePipe())->setString(std::to_string(amount));
}

bool GameScene::onContactBegin(cocos2d::PhysicsContact& contact)
{
    auto node1 = contact.getShapeA()->getBody();
    auto node2 = contact.getShapeB()->getBody();


    return true;
}

void GameScene::onEnter()
{
    Node::onEnter();
}

void GameScene::onExit()
{
    //_eventDispatcher->removeCustomEventListeners(Constant::EquipSkinUI);
    
    this->removeAllChildrenWithCleanup(true);
    Node::onExit();
}

bool GameScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    LevelManager::getInstance()->InitLevel();
    Director::getInstance()->getScheduler()->setTimeScale(1.0f);
    this->scheduleUpdate();

    InitBackGround();
    InitListener();
    InitUI();

    StartGame();

    return true;
}