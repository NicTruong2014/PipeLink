#include "WinLayer.h"
#include "HelperManager.h"
#include "SoundManager.h"
#include "GameScene.h"
#include "MainMenuScene.h"
#include "DataManager.h"
#include "LeaderboardLayer.h"

USING_NS_CC;

bool WinLayer::init(int score, int star)
{
    if (!Layer::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto scale = 0.8f;
    HelperManager::GetInstance()->addLockLayer(this);

    auto background = ui::Scale9Sprite::create("Sprites/popup/sh_popup_win.png");
    background->setScale(scale);
    background->setName("background");
    background->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    background->setContentSize(Size(background->getContentSize().width + 50, background->getContentSize().height + 50));
    background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background);

    auto rankButton = cocos2d::ui::Button::create("Sprites/icon/sh_icon_rank.png");
    rankButton->setPosition(Vec2(background->getContentSize().width / 2 + rankButton->getContentSize().width + 20, rankButton->getContentSize().height + 86));
    rankButton->setPressedActionEnabled(true);
    rankButton->addClickEventListener([=](Ref* sender)
    {
        SOUND_MANAGER->playClickEffect();
        Director::getInstance()->getScheduler()->setTimeScale(1.0f);
        auto leaderBoard = LeaderboardLayer::create();
        addChild(leaderBoard);
    });
    background->addChild(rankButton);

    auto nextButton = cocos2d::ui::Button::create("Sprites/icon/sh_icon_next.png");
    nextButton->setPosition(Vec2(background->getContentSize().width / 2, rankButton->getContentSize().height + 86));
    nextButton->setPressedActionEnabled(true);
    nextButton->addClickEventListener([=](Ref* sender)
    {
        _callBack();
        SOUND_MANAGER->playClickEffect();
        this->removeFromParent();
        Director::getInstance()->replaceScene(GameScene::createScene());
    });
    background->addChild(nextButton);

    auto menuButton = cocos2d::ui::Button::create("Sprites/icon/sh_icon_home.png");
    menuButton->setPosition(Vec2(background->getContentSize().width / 2 - rankButton->getContentSize().width - 20, rankButton->getContentSize().height + 86));
    menuButton->setPressedActionEnabled(true);
    menuButton->addClickEventListener([=](Ref* sender)
    {
        SOUND_MANAGER->playClickEffect();
        this->removeFromParent();
        Director::getInstance()->replaceScene(MainMenuScene::createScene());
    });
    background->addChild(menuButton);

    auto rectLv = cocos2d::Sprite::create("Sprites/player/sh_player_bar_level.png");
    rectLv->setPosition(Vec2(background->getContentSize().width / 2, background->getContentSize().height / 2 + 150));
    background->addChild(rectLv);
 
    auto level = DataManager::getInstance()->GetLevel();
    auto labelLv = cocos2d::Label::createWithTTF("Leader Board", "fonts/SVNMergeBold.ttf", 30);
    labelLv->setString(std::to_string(level));
    labelLv->setPosition(Vec2(background->getContentSize().width / 2 - 40, background->getContentSize().height / 2 + 150));
    background->addChild(labelLv);

    _spriteStar3 = cocos2d::Sprite::create("Sprites/player/sh_player_star_3.png");
    _spriteStar3->setPosition(Vec2(background->getContentSize().width / 2 + 63, background->getContentSize().height / 2 + 150));
    background->addChild(_spriteStar3);

    auto txtScore = cocos2d::Label::createWithTTF("111", "fonts/SVNMergeBold.ttf", 45);
    txtScore->setAnchorPoint({ 0.5,0.5 });
    txtScore->setPosition(Vec2(background->getContentSize().width / 2, background->getContentSize().height / 2 - 70));
    txtScore->setString(std::to_string(score));
    background->addChild(txtScore);

    LoadStar(star);

    return true;
}

void WinLayer::LoadStar(int star)
{
    if (star == 3)
    {
        auto getTextureCache = Director::getInstance()->getTextureCache();
        _spriteStar3->setTexture(getTextureCache->addImage("Sprites/fruit/sh_player_star_3.png"));
    }
    else if (star == 2)
    {
        auto getTextureCache = Director::getInstance()->getTextureCache();
        _spriteStar3->setTexture(getTextureCache->addImage("Sprites/fruit/sh_player_star_2.png"));
    }
    else
    {
        auto getTextureCache = Director::getInstance()->getTextureCache();
        _spriteStar3->setTexture(getTextureCache->addImage("Sprites/fruit/sh_player_star_1.png"));
    }
}
