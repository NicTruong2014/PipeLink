#include "SelectLevelLayer.h"
#include "HelperManager.h"
#include "SoundManager.h"
#include "DataManager.h"
#include "GameScene.h"

USING_NS_CC;

bool SelectLevelLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }

    auto getTextureCache = Director::getInstance()->getTextureCache();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto scale = 1.0f;

    _background = Sprite::create("Sprites/News/popup/pl_popup_level.png");
    HelperManager::GetInstance()->addLockLayer(this, _background);

    _background->setScale(scale);
    _background->setName("background");
    _background->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    _background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    this->addChild(_background);

    auto backButton = cocos2d::ui::Button::create("Sprites/News/icon/pl_icon_back.png");
    backButton->setPosition(Vec2(0 - 60, _background->getContentSize().height / 2));
    backButton->setPressedActionEnabled(true);

    auto nextButton = cocos2d::ui::Button::create("Sprites/News/icon/pl_icon_next.png");
    nextButton->setPosition(Vec2(_background->getContentSize().width + 60, _background->getContentSize().height / 2));
    nextButton->setPressedActionEnabled(true);
    nextButton->addClickEventListener([=](Ref* sender)
    {
        SOUND_MANAGER->playClickEffect();
        _index++;
        if (_index >= 10)
        {
            nextButton->setPressedActionEnabled(false);
            nextButton->loadTextureNormal("Sprites/News/icon/pl_icon_next_block.png");
            _index = 10;
        }

        InitLevel(_index);

        backButton->setPressedActionEnabled(true);
        backButton->loadTextureNormal("Sprites/News/icon/pl_icon_back.png");
    });

    backButton->addClickEventListener([=](Ref* sender)
        {
            SOUND_MANAGER->playClickEffect();
            _index--;
            if (_index <= 0)
            {
                backButton->setPressedActionEnabled(false);
                backButton->loadTextureNormal("Sprites/News/icon/pl_icon_back_block.png");
                _index = 0;
            }

            InitLevel(_index);

            nextButton->setPressedActionEnabled(true);
            nextButton->loadTextureNormal("Sprites/News/icon/pl_icon_next.png");
        });

    _background->addChild(nextButton);
    _background->addChild(backButton);

    //default
    InitLevel(_index);
    backButton->setPressedActionEnabled(false);
    backButton->loadTextureNormal("Sprites/News/icon/pl_icon_back_block.png");

    return true;
}

void SelectLevelLayer::InitLevel(int page)
{
    //init level
    int level = 1 + 18 * page;

    for (auto i = 0; i < 3; i++)
    {
        for (auto j = 0; j < 6; j++)
        {
            auto deltaX = 122 + j * 150;
            auto deltaY = 100 - i * 150;
            auto levelButton2 = Button::create("Sprites/News/popup/pl_popup_level_block.png");
            auto dataLevel = DataManager::getInstance()->GetDataLevel(level);

            auto labelLv = cocos2d::Label::createWithTTF("Leader Board", "fonts/SVNMergeBold.ttf", 40);
            labelLv->setColor(Color3B::WHITE);
            labelLv->setString(std::to_string(level));
            labelLv->setPosition(Vec2(levelButton2->getContentSize().width / 2, levelButton2->getContentSize().height / 2 + 30));
            levelButton2->addChild(labelLv);

            if (dataLevel == TypeSelectLevel::Block)
            {
                levelButton2->setEnabled(false);
                labelLv->setVisible(false);
            }
            else
            {
                levelButton2->loadTextureNormal(StringUtils::format("Sprites/News/popup/pl_popup_level_%d.png", dataLevel));
            }

            levelButton2->setPosition(Vec2(0 + deltaX, _background->getContentSize().height / 2 + deltaY));
            levelButton2->addClickEventListener([=](Ref* sender)
                {
                    DataManager::getInstance()->SetCurrentLevel(level);
                    Director::getInstance()->replaceScene(GameScene::createScene());
                });
            _background->addChild(levelButton2);

            level++;
        }
    }
}
