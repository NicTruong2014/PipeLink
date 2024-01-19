#pragma once
#include "BaseSingleton.h"
#include "Pipe.h"

#define SOUND_MANAGER SoundManager::GetInstance()

#define IS_MUSIC_KEY_ON "key_is_music_on"

#define IS_SOUND_KEY_ON "key_is_sound_on"

class SoundManager : public BaseSingleton<SoundManager>
{
public:

	 void init();

	 void playSoundCard();

	 void playLoseEffect();

	 void playWinEffect();

	 void playClickEffect();

	 void playPopEffect();

	 void playCollisionEffect();
	 
	 void playMainMenuMusic(bool isGameMusic = false);

	 void playGameMusic(bool isGameMusic);

	 void pauseAllBackgroundMusics();

	 void pauseAllSoundEffects();

	 void resumeAllBackgroundMusics();

	 void resumeAllSoundEffects();

	 void stopAllBackgroundMusics();

	 void stopAllSoundEffects();

	 void preloadSoundEffectAndMusic();

	 bool isSoundEffectEnable();

	 bool isMusicEffectEnable();

	 void ResumeGamePlayMusic();
};