#include "LoseLayer.h"
#include "HelperManager.h"
#include "SoundManager.h"
#include "GameScene.h"
#include "MainMenuScene.h"
#include "DataManager.h"
#include "LeaderboardLayer.h"

USING_NS_CC;

bool LoseLayer::init(int score)
{
    if (!Layer::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto scale = 1.0f;
    HelperManager::GetInstance()->addLockLayer(this);

    auto background = ui::Scale9Sprite::create("Sprites/News/popup/pl_popup_lose.png");
    background->setScale(scale);
    background->setName("background");
    background->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background);

    auto rankButton = cocos2d::ui::Button::create("Sprites/News/icon/pl_icon_rank.png");
    rankButton->setPosition(Vec2(background->getContentSize().width / 2 + rankButton->getContentSize().width + 20, rankButton->getContentSize().height + 28));
    rankButton->setPressedActionEnabled(true);
    rankButton->addClickEventListener([=](Ref* sender)
        {
            SOUND_MANAGER->playClickEffect();
            Director::getInstance()->getScheduler()->setTimeScale(1.0f);
            auto leaderBoard = LeaderboardLayer::create();
            addChild(leaderBoard);
        });
    background->addChild(rankButton);

    auto nextButton = cocos2d::ui::Button::create("Sprites/News/icon/pl_icon_replay.png");
    nextButton->setPosition(Vec2(background->getContentSize().width / 2, rankButton->getContentSize().height + 28));
    nextButton->setPressedActionEnabled(true);
    nextButton->addClickEventListener([=](Ref* sender)
        {
            _callBack();
            SOUND_MANAGER->playClickEffect();
            this->removeFromParent();
            Director::getInstance()->replaceScene(GameScene::createScene());
        });
    background->addChild(nextButton);

    auto menuButton = cocos2d::ui::Button::create("Sprites/News/icon/pl_icon_home.png");
    menuButton->setPosition(Vec2(background->getContentSize().width / 2 - rankButton->getContentSize().width - 20, rankButton->getContentSize().height + 28));
    menuButton->setPressedActionEnabled(true);
    menuButton->addClickEventListener([=](Ref* sender)
        {
            SOUND_MANAGER->playClickEffect();
            this->removeFromParent();
            Director::getInstance()->replaceScene(MainMenuScene::createScene());
        });
    background->addChild(menuButton);

    auto rectLv = cocos2d::Sprite::create("Sprites/News/ui/pl_ui_level.png");
    rectLv->setPosition(Vec2(background->getContentSize().width / 2, background->getContentSize().height / 2 + 100));
    background->addChild(rectLv);

    auto level = DataManager::getInstance()->GetLevel();
    auto labelLv = cocos2d::Label::createWithTTF("Leader Board", "fonts/SVNMergeBold.ttf", 40);
    labelLv->setString(std::to_string(level));
    labelLv->setPosition(Vec2(background->getContentSize().width / 2 + 50, background->getContentSize().height / 2 + 105));
    background->addChild(labelLv);

    _spriteStar3 = cocos2d::Sprite::create("Sprites/News/ui/pl_ui_star.png");
    _spriteStar3->setPosition(Vec2(background->getContentSize().width / 2, background->getContentSize().height / 2 - 35));
    background->addChild(_spriteStar3);

    for (auto i = 0; i < 3; i++)
    {
        auto star = Sprite::create("Sprites/News/ui/pl_ui_star_off.png");

        star->setPosition(Vec2(_spriteStar3->getContentSize().width / 2 + i * 65 - 15, _spriteStar3->getContentSize().height / 2 + 5));
        _spriteStar3->addChild(star);
    }

    LoadStar(0);

    return true;
}

void LoseLayer::LoadStar(int star)
{
    for (auto i = 0; i < star; i++)
    {
        auto star = Sprite::create("Sprites/News/ui/pl_ui_star_on.png");

        star->setPosition(Vec2(_spriteStar3->getContentSize().width / 2 + i * 65 - 15, _spriteStar3->getContentSize().height / 2 + 5));
        _spriteStar3->addChild(star);
    }
}