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
    auto scale = 1.0f;
    auto layer = cocos2d::LayerColor::create(cocos2d::Color4B(255, 255, 255, 255*0.5f), visibleSize.width, visibleSize.height);
    this->addChild(layer);

    auto backLayer = cocos2d::ui::Button::create();
    backLayer->setScale9Enabled(true);
    backLayer->ignoreContentAdaptWithSize(true);
    backLayer->setContentSize(visibleSize);
    backLayer->setPressedActionEnabled(true);
    backLayer->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(backLayer);

    auto background = ui::Scale9Sprite::create("Sprites/News/popup/pl_popup_setting.png");
    HelperManager::GetInstance()->addLockLayer(this, background);

    background->setScale(scale);
    background->setName("background");
    background->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background);

    auto isSoundOn = UserDefault::getInstance()->getBoolForKey(IS_SOUND_KEY_ON, true);
    auto isMusicOn = UserDefault::getInstance()->getBoolForKey(IS_MUSIC_KEY_ON, true);
    auto soundButton = cocos2d::ui::Button::create();
    auto pathSoundOn = "Sprites/News/icon/pl_icon_sound_on.png";
    auto pathSoundOff = "Sprites/News/icon/pl_icon_sound_off.png";
    auto pathMusicOn = "Sprites/News/icon/pl_icon_mussic_on.png";
    auto pathMusicOff = "Sprites/News/icon/pl_icon_mussic_off.png";

    auto textureSound = isSoundOn ? pathSoundOn : pathSoundOff;
    auto textureMusic = isMusicOn ? pathMusicOn : pathMusicOff;

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

        auto textureSoundL = isSoundOnL ? pathSoundOn : pathSoundOff;
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

        auto textureMusicL = isSoundOnL ? pathMusicOn : pathMusicOff;
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