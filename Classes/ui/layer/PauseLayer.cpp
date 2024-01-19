#include "PauseLayer.h"
#include "HelperManager.h"
#include "SoundManager.h"
#include "GameScene.h"
#include "MainMenuScene.h"

USING_NS_CC;

bool PauseLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }

    Director::getInstance()->getScheduler()->setTimeScale(0.0f);
    SoundManager::GetInstance()->pauseAllBackgroundMusics();

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto scale = 1.0f;
    HelperManager::GetInstance()->addLockLayer(this);

    auto background = ui::Scale9Sprite::create("Sprites/News/popup/pl_popup_pause.png");

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
        _callBack();
        Director::getInstance()->getScheduler()->setTimeScale(1.0f);
        SOUND_MANAGER->playClickEffect();
        SoundManager::GetInstance()->ResumeGamePlayMusic();
        this->removeFromParent();
    });
    background->addChild(closeButton);

    auto resumeButton = cocos2d::ui::Button::create("Sprites/News/icon/pl_icon_play.png");
    resumeButton->setPosition(Vec2(background->getContentSize().width / 2, resumeButton->getContentSize().height + 28));
    resumeButton->setPressedActionEnabled(true);
    resumeButton->addClickEventListener([=](Ref* sender)
    {
        SOUND_MANAGER->playClickEffect();
        Director::getInstance()->getScheduler()->setTimeScale(1.0f);
        SoundManager::GetInstance()->ResumeGamePlayMusic();
        this->removeFromParent();
        _callBack();
    });
    background->addChild(resumeButton);

    auto retryButton = cocos2d::ui::Button::create("Sprites/News/icon/pl_icon_replay.png");
    retryButton->setPosition(Vec2(background->getContentSize().width / 2 - retryButton->getContentSize().width - 20, resumeButton->getContentSize().height + 28));
    retryButton->setPressedActionEnabled(true);
    retryButton->addClickEventListener([=](Ref* sender)
    {
        SOUND_MANAGER->playClickEffect();
        this->removeFromParent();
        Director::getInstance()->replaceScene(GameScene::createScene());
    });
    background->addChild(retryButton);

    auto menuButton = cocos2d::ui::Button::create("Sprites/News/icon/pl_icon_home.png");
    menuButton->setPosition(Vec2(background->getContentSize().width / 2 + retryButton->getContentSize().width + 20, resumeButton->getContentSize().height + 28));
    menuButton->setPressedActionEnabled(true);
    menuButton->addClickEventListener([=](Ref* sender)
    {
        SOUND_MANAGER->playClickEffect();
        this->removeFromParent();
        Director::getInstance()->replaceScene(MainMenuScene::createScene());
    });
    background->addChild(menuButton);

    auto isSoundOn = UserDefault::getInstance()->getBoolForKey(IS_SOUND_KEY_ON, true);
    auto isMusicOn = UserDefault::getInstance()->getBoolForKey(IS_MUSIC_KEY_ON, true);
    auto soundButton = cocos2d::ui::Button::create();
    auto pathSoundOn = "Sprites/News/ui/pl_icon_sound_on.png";
    auto pathSoundOff = "Sprites/News/ui/pl_button_sound_off.png";
    auto pathMusicOn = "Sprites/News/ui/pl_button_music_on.png";
    auto pathMusicOff = "Sprites/News/ui/pl_button_music_off.png";

    auto textureSound = isSoundOn ? pathSoundOn : pathSoundOff;
    auto textureMusic = isMusicOn ? pathMusicOn : pathMusicOff;

    soundButton->loadTextures(textureSound, "", textureSound);
    soundButton->setPosition(Vec2(background->getContentSize().width / 2 - retryButton->getContentSize().width + 74, resumeButton->getContentSize().height + 350));
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
    musicButton->setPosition(Vec2(background->getContentSize().width / 2 - retryButton->getContentSize().width + 74, resumeButton->getContentSize().height + 250));
    musicButton->setPressedActionEnabled(true);
    musicButton->addClickEventListener([=](Ref* sender)
    {
        SOUND_MANAGER->playClickEffect();
        auto isSoundOnL = UserDefault::getInstance()->getBoolForKey(IS_MUSIC_KEY_ON, true);
        isSoundOnL = !isSoundOnL;

        UserDefault::getInstance()->setBoolForKey(IS_MUSIC_KEY_ON, isSoundOnL);

        if (SOUND_MANAGER->isMusicEffectEnable()) {

            SoundManager::GetInstance()->ResumeGamePlayMusic();
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
