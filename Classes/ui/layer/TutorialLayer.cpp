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
    auto scale = 0.8f;

    HelperManager::GetInstance()->addLockLayer(this);

    _sprites.push_back(getTextureCache->addImage("Sprites/popup/tutorial/sh_popup_tutorial_1.png"));
    _sprites.push_back(getTextureCache->addImage("Sprites/popup/tutorial/sh_popup_tutorial_2.png"));
    _sprites.push_back(getTextureCache->addImage("Sprites/popup/tutorial/sh_popup_tutorial_3.png"));

    _background = Sprite::create("Sprites/popup/tutorial/sh_popup_tutorial_1.png");
    _background->setScale(scale);
    _background->setName("background");
    _background->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    _background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    this->addChild(_background);

    auto closeButton = cocos2d::ui::Button::create("Sprites/icon/sh_icon_cancel.png");
    closeButton->setPosition(Vec2(_background->getContentSize().width - closeButton->getContentSize().width / 4,
        _background->getContentSize().height - closeButton->getContentSize().height - 10));
    closeButton->setPressedActionEnabled(true);
    closeButton->addClickEventListener([=](Ref* sender)
    {
        SOUND_MANAGER->playClickEffect();
        this->removeFromParent();
    });
    _background->addChild(closeButton);

    auto backButton = cocos2d::ui::Button::create("Sprites/icon/sh_icon_back.png");
    backButton->setPosition(Vec2(0 - 30, _background->getContentSize().height / 2));
    backButton->setPressedActionEnabled(true);
    backButton->addClickEventListener([=](Ref* sender)
    {
        SOUND_MANAGER->playClickEffect();
        _index--;
        if (_index < 0)
        {
            _index = _sprites.size() - 1;
        }

        _background->setTexture(_sprites[_index]);
    });

    _background->addChild(backButton);

    auto nextButton = cocos2d::ui::Button::create("Sprites/icon/sh_icon_next.png");
    nextButton->setPosition(Vec2(_background->getContentSize().width + 30, _background->getContentSize().height / 2));
    nextButton->setPressedActionEnabled(true);
    nextButton->addClickEventListener([=](Ref* sender)
    {
        SOUND_MANAGER->playClickEffect();
        _index++;
        if (_index >= _sprites.size())
        {
            _index = 0;
        }

        _background->setTexture(_sprites[_index]);
    });

    _background->addChild(nextButton);

    return true;
}
