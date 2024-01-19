#include "SettingsLayer.h"
#include "HelperManager.h"
#include "MainMenuScene.h"
#include "SoundManager.h"

USING_NS_CC;

Scene* SettingsLayer::createScene()
{
    auto scene = Scene::create();

    if (scene)
    {
        auto view = SettingsLayer::create();
        scene->addChild(view);
    }
    else
    {
        CC_SAFE_DELETE(scene);
    }
    
    return scene;
}

bool SettingsLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto scale = 0.8f;
    auto layer = cocos2d::LayerColor::create(cocos2d::Color4B(255, 255, 255, 255*0.5f), visibleSize.width, visibleSize.height);
    this->addChild(layer);

    auto backLayer = cocos2d::ui::Button::create();
    backLayer->setScale9Enabled(true);
    backLayer->ignoreContentAdaptWithSize(true);
    backLayer->setContentSize(visibleSize);
    backLayer->setPressedActionEnabled(true);
    backLayer->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(backLayer);

    auto background = ui::Scale9Sprite::create("Sprites/popup/sh_popup_setting.png");
    background->setScale(scale);
    background->setName("background");
    background->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background);

    auto closeButton = cocos2d::ui::Button::create("Sprites/icon/sh_icon_cancel.png");
    closeButton->setPosition(Vec2(background->getContentSize().width - closeButton->getContentSize().width / 4 + 5,
        background->getContentSize().height - closeButton->getContentSize().height - 10));
    closeButton->setPressedActionEnabled(true);
    closeButton->addClickEventListener([=](Ref* sender)
    {
        Director::getInstance()->getScheduler()->setTimeScale(1.0f);
        SOUND_MANAGER->playClickEffect();
        this->removeFromParent();
    });
    background->addChild(closeButton);

    auto isSoundOn = UserDefault::getInstance()->getBoolForKey(IS_SOUND_KEY_ON, true);
    auto isMusicOn = UserDefault::getInstance()->getBoolForKey(IS_MUSIC_KEY_ON, true);
    auto soundButton = cocos2d::ui::Button::create();
    auto textureSound = isSoundOn ? "Sprites/button/sh_button_sound_on.png" : "Sprites/button/sh_button_sound_off.png";
    auto textureMusic = isMusicOn ? "Sprites/button/sh_button_music_on.png" : "Sprites/button/sh_button_music_off.png";

    soundButton->loadTextures(textureSound, "", textureSound);
    soundButton->setPosition(Vec2(background->getContentSize().width / 2, background->getContentSize().height / 2 + 20));
    soundButton->setPressedActionEnabled(true);
    soundButton->addClickEventListener([=](Ref* sender)
    {
        SOUND_MANAGER->playClickEffect();
        auto isSoundOnL = UserDefault::getInstance()->getBoolForKey(IS_SOUND_KEY_ON, true);
        isSoundOnL = !isSoundOnL;

        UserDefault::getInstance()->setBoolForKey(IS_SOUND_KEY_ON, isSoundOnL);

        if (SOUND_MANAGER->isSoundEffectEnable()) {

            SOUND_MANAGER->resumeAllSoundEffects();
        }
        else
        {
            SOUND_MANAGER->pauseAllSoundEffects();
        }

        auto textureSoundL = isSoundOnL ? "Sprites/button/sh_button_sound_on.png" : "Sprites/button/sh_button_sound_off.png";
        soundButton->loadTextures(textureSoundL, "", textureSoundL);
    });
    background->addChild(soundButton);

    auto musicButton = cocos2d::ui::Button::create();
    musicButton->loadTextures(textureMusic, "", textureMusic);
    musicButton->setPosition(Vec2(background->getContentSize().width / 2, background->getContentSize().height / 2 - 80 ));
    musicButton->setPressedActionEnabled(true);
    musicButton->addClickEventListener([=](Ref* sender)
    {
        SOUND_MANAGER->playClickEffect();
        auto isSoundOnL = UserDefault::getInstance()->getBoolForKey(IS_MUSIC_KEY_ON, true);
        isSoundOnL = !isSoundOnL;

        UserDefault::getInstance()->setBoolForKey(IS_MUSIC_KEY_ON, isSoundOnL);

        if (SOUND_MANAGER->isMusicEffectEnable()) {

            SOUND_MANAGER->resumeAllBackgroundMusics();
        }
        else
        {
            SOUND_MANAGER->pauseAllBackgroundMusics();
        }

        auto textureMusicL = isSoundOnL ? "Sprites/button/sh_button_music_on.png" : "Sprites/button/sh_button_music_off.png";
        musicButton->loadTextures(textureMusicL, "", textureMusicL);
    });
    background->addChild(musicButton);

    return true;
}


void SettingsLayer::playVibration() {

	auto isVibrationOn = UserDefault::getInstance()->getBoolForKey("key_is_vibration_on", true);

	if (isVibrationOn) 
    {
		cocos2d::Device::vibrate(0.25);
	}
}