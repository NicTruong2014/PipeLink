#include "MainMenuScene.h"
#include "GameScene.h"
#include "SoundManager.h"
#include "TutorialLayer.h"
#include "LeaderboardLayer.h"
#include "DataManager.h"
#include "SelectLevelLayer.h"
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
    Director::getInstance()->getScheduler()->setTimeScale(1.0f);
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    auto background = Sprite::create("Sprites/News/pl_background_home.png");
    background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    background->setScale(1.2f);
    this->addChild(background);

    auto logo = Sprite::create("Sprites/News/logo/logo_game.png");
    logo->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 100));
    this->addChild(logo);

    auto moveUp = MoveBy::create(1.0f, Vec2(0, 20));
    auto moveDown = moveUp->reverse();
    auto bounce = Sequence::create(moveUp, moveDown, nullptr);

    auto easeBounce = EaseSineInOut::create(bounce);
    auto repeatBounce = RepeatForever::create(easeBounce);
    logo->runAction(repeatBounce);

    auto playButton = cocos2d::ui::Button::create("Sprites/News/button_home/pl_button_home_play.png");
    playButton->setPosition(Vec2(background->getContentSize().width / 2, background->getContentSize().height / 2 - 300));
    playButton->setPressedActionEnabled(true);
    playButton->setScale(1.2f);
    playButton->addClickEventListener([=](Ref* sender)
    {
        SOUND_MANAGER->playClickEffect();
        auto layer = SelectLevelLayer::create();
        this->addChild(layer);
    });
    background->addChild(playButton);

    auto tutorialButton = cocos2d::ui::Button::create("Sprites/News/button_home/pl_button_home_tutorial.png");
    tutorialButton->setScale(1.2f);
    tutorialButton->setPosition(Vec2(playButton->getPositionX() + 280, playButton->getPositionY()));
    tutorialButton->setPressedActionEnabled(true);
    tutorialButton->addClickEventListener([=](Ref* sender)
    {
        SOUND_MANAGER->playClickEffect();
        auto layer = TutorialLayer::create();
        this->addChild(layer);
    });
    background->addChild(tutorialButton);

    auto rankButton = cocos2d::ui::Button::create("Sprites/News/button_home/pl_button_home_rank.png");
    rankButton->setScale(1.2f);
    rankButton->setPosition(Vec2(playButton->getPositionX() - 280, playButton->getPositionY()));
    rankButton->setPressedActionEnabled(true);
    rankButton->addClickEventListener([=](Ref* sender)
    {
        SOUND_MANAGER->playClickEffect();
        auto layer = LeaderboardLayer::create();
        this->addChild(layer);
    });
    background->addChild(rankButton);

    auto settingButton = cocos2d::ui::Button::create("Sprites/News/button_home/pl_button_home_setting.png");
    settingButton->setScale(1.2f);
    settingButton->setPosition(Vec2(visibleSize.width - 150, visibleSize.height - 150));
    settingButton->setPressedActionEnabled(true);
    settingButton->addClickEventListener([=](Ref* sender)
    {
        SOUND_MANAGER->playClickEffect();
        auto layer = SettingsLayer::create();
        this->addChild(layer);
    });
    background->addChild(settingButton);
}