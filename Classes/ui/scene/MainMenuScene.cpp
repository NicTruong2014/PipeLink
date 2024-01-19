#include "MainMenuScene.h"
#include "GameScene.h"
#include "SoundManager.h"
#include "TutorialLayer.h"
#include "LeaderboardLayer.h"
#include "DataManager.h"
#include "SettingsLayer.h"

cocos2d::Scene* MainMenuScene::createScene()
{
    auto scene = Scene::createWithPhysics();
    if (scene)
    {
        auto view = MainMenuScene::create();
        scene->addChild(view);
    }
    else
    {
        CC_SAFE_DELETE(scene);
    }

    return scene;
}

bool MainMenuScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    InitUI();

    return true;
}

void MainMenuScene::InitUI()
{
    SOUND_MANAGER->playMainMenuMusic(false);

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    auto parentNode = Node::create();
    parentNode->setContentSize(visibleSize);
    parentNode->setAnchorPoint(Vec2(0.5f, 0.5f));
    this->addChild(parentNode);

    auto background = Sprite::create("Sprites/background_home_2.png");
    background->setPosition(Vec2(visibleSize.width / 2 + origin.x, 350 + origin.y));
    parentNode->addChild(background);

    auto logo = Sprite::create("Sprites/logo/logo_game.png");
    logo->setScale(0.78f);
    logo->setPosition(Vec2(visibleSize.width / 2 + origin.x, 500 + origin.y));
    parentNode->addChild(logo);

    auto centerOfParent = Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
    parentNode->setPosition(centerOfParent);
    parentNode->setScale(0.7f);

    auto playButton = cocos2d::ui::Button::create("Sprites/button/sh_button_play.png");
    //playButton->setScale(1.2f);
    playButton->setPosition(Vec2(background->getContentSize().width / 2, 200));
    playButton->setPressedActionEnabled(true);
    playButton->addClickEventListener([=](Ref* sender)
    {
        SOUND_MANAGER->playClickEffect();
        Director::getInstance()->replaceScene(GameScene::createScene());
    });
    background->addChild(playButton);

    auto tutorialButton = cocos2d::ui::Button::create("Sprites/icon/sh_icon_tutorial.png");
    tutorialButton->setScale(1.2f);
    tutorialButton->setPosition(Vec2(playButton->getPositionX() - 340, playButton->getPositionY()));
    tutorialButton->setPressedActionEnabled(true);
    tutorialButton->addClickEventListener([=](Ref* sender)
    {
        SOUND_MANAGER->playClickEffect();
        auto layer = TutorialLayer::create();
        this->addChild(layer);
    });
    background->addChild(tutorialButton);

    auto rankButton = cocos2d::ui::Button::create("Sprites/icon/sh_icon_rank.png");
    rankButton->setScale(1.2f);
    rankButton->setPosition(Vec2(playButton->getPositionX() - 240, playButton->getPositionY()));
    rankButton->setPressedActionEnabled(true);
    rankButton->addClickEventListener([=](Ref* sender)
    {
        SOUND_MANAGER->playClickEffect();
        auto layer = LeaderboardLayer::create();
        this->addChild(layer);
    });
    background->addChild(rankButton);

    auto settingButton = cocos2d::ui::Button::create("Sprites/icon/sh_icon_setting.png");
    settingButton->setScale(1.2f);
    settingButton->setPosition(Vec2(playButton->getPositionX() + 340, playButton->getPositionY()));
    settingButton->setPressedActionEnabled(true);
    settingButton->addClickEventListener([=](Ref* sender)
    {
        SOUND_MANAGER->playClickEffect();
        auto layer = SettingsLayer::create();
        this->addChild(layer);
    });
    background->addChild(settingButton);
}