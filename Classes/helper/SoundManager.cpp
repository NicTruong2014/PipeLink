#include "SoundManager.h"
#include "cocos2d.h"
#include "AudioEngine.h"
#include "Constant.h"

USING_NS_CC;
using namespace experimental;

void SoundManager::init()
{
	preloadSoundEffectAndMusic();
}

void SoundManager::playSoundCard()
{
	auto nameSound = "sound/hit.mp3";

	if (isSoundEffectEnable())
	{
		auto id = AudioEngine::play2d(nameSound);
		AudioEngine::setVolume(id, 1);
	}
}

void SoundManager::playLoseEffect()
{
	if (isSoundEffectEnable())
	{
		AudioEngine::play2d("sound/lose_sfx.mp3");
	}
}

void SoundManager::playWinEffect()
{
	if (isSoundEffectEnable())
	{
		AudioEngine::play2d("sound/You Win.mp3");
	}
}

void SoundManager::playClickEffect()
{
	if (isSoundEffectEnable()) 
	{
		AudioEngine::play2d("sound/beep_sfx.mp3");
	}
}

void SoundManager::playPopEffect()
{
	if (isSoundEffectEnable())
	{
		AudioEngine::play2d(Constant::effectPop);
	}
}

static int gameID = -1;
static int menuID = -1;

static bool s_isGameMusic = false;

void SoundManager::playMainMenuMusic(bool isGameMusic)
{
	if (!isMusicEffectEnable())
	{
		return;
	}

	s_isGameMusic = isGameMusic;

	AudioEngine::stop(gameID);
	AudioEngine::stop(menuID);

	gameID = -1;
	menuID = AudioEngine::play2d("sound/mainmenu-bgm.mp3", true);
    AudioEngine::setVolume(gameID, 0.2f);
}

void SoundManager::playGameMusic(bool isGameMusic)
{
	if (!isMusicEffectEnable())
	{
		return;
	}

	AudioEngine::stop(gameID);
	AudioEngine::stop(menuID);

	s_isGameMusic = isGameMusic;

	menuID = -1;
	gameID = AudioEngine::play2d("sound/music_gameplay_1.mp3", true);
	AudioEngine::setVolume(gameID, 0.5f);
}

void SoundManager::pauseAllBackgroundMusics()
{
	AudioEngine::pause(gameID);
	AudioEngine::pause(menuID);
}

void SoundManager::pauseAllSoundEffects()
{
}

void SoundManager::resumeAllBackgroundMusics()
{
	if(!s_isGameMusic)
	{
		playMainMenuMusic(true);
		return;
	}

	if(isMusicEffectEnable())
	{
		if(gameID != -1)
		{
			AudioEngine::resume(gameID);
		}
		else if(menuID != -1)
		{
			AudioEngine::resume(menuID);
		}
	}
}

void SoundManager::resumeAllSoundEffects()
{
}

void SoundManager::stopAllBackgroundMusics()
{
	AudioEngine::stop(gameID);
	AudioEngine::stop(menuID);
}

void SoundManager::stopAllSoundEffects()
{
}

void SoundManager::preloadSoundEffectAndMusic()
{
	AudioEngine::preload("");
}

bool SoundManager::isSoundEffectEnable()
{
	return UserDefault::getInstance()->getBoolForKey(IS_SOUND_KEY_ON, true);
}

bool SoundManager::isMusicEffectEnable()
{
	return UserDefault::getInstance()->getBoolForKey(IS_MUSIC_KEY_ON, true);
}

void SoundManager::ResumeGamePlayMusic()
{
	if(!s_isGameMusic)
	{
		playGameMusic(true);
		return;
	}

	if(isMusicEffectEnable())
	{
		if(gameID != -1)
		{
			AudioEngine::resume(gameID);
		}
		else if(menuID != -1)
		{
			AudioEngine::resume(menuID);
		}
	}
}
