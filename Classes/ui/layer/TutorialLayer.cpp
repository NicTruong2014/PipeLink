#include "TutorialLayer.h"
#include "HelperManager.h"
#include "SoundManager.h"

USING_NS_CC;

bool TutorialLayer ::init()
{
    if (!Layer::init())
    {
        return false;
    }

    auto getTextureCache = Director::getInstance()->getTextureCache();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto scale = 1.0f;

    _background = Sprite::create("Sprites/News/popup/pl_popup_tutorial.png");
    HelperManager::GetInstance()->addLockLayer(this, _background);

    _background->setScale(scale);
    _background->setName("background");
    _background->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    _background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    this->addChild(_background);

    //auto backButton = cocos2d::ui::Button::create("Sprites/icon/sh_icon_back.png");
    //backButton->setPosition(Vec2(0 - 30, _background->getContentSize().height / 2));
    //backButton->setPressedActionEnabled(true);
    //backButton->addClickEventListener([=](Ref* sender)
    //{
    //    SOUND_MANAGER->playClickEffect();
    //    _index--;
    //    if (_index < 0)
    //    {
    //        _index = _sprites.size() - 1;
    //    }

    //    _background->setTexture(_sprites[_index]);
    //});

    //_background->addChild(backButton);

    //auto nextButton = cocos2d::ui::Button::create("Sprites/icon/sh_icon_next.png");
    //nextButton->setPosition(Vec2(_background->getContentSize().width + 30, _background->getContentSize().height / 2));
    //nextButton->setPressedActionEnabled(true);
    //nextButton->addClickEventListener([=](Ref* sender)
    //{
    //    SOUND_MANAGER->playClickEffect();
    //    _index++;
    //    if (_index >= _sprites.size())
    //    {
    //        _index = 0;
    //    }

    //    _background->setTexture(_sprites[_index]);
    //});

    //_background->addChild(nextButton);

    return true;
}
