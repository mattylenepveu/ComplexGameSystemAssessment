#include "AudioManager.h"
#include <iostream>
#include <stddef.h>

AudioManager::AudioManager()
{
}

AudioManager::~AudioManager()
{
}

bool AudioManager::SystemStart()
{
	m_pSystem = NULL;
	result = FMOD::System_Create(&m_pSystem);

	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result);
		return false;
	}

	result = m_pSystem->init(512, FMOD_INIT_NORMAL, 0);

	// Initialize FMOD with 512 channels
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result);
		return false;
	}

	return true;
}

void AudioManager::LoadSound()
{
	FMOD::Sound* pSound;
	result = m_pSystem->createSound("./audio/powerup.wav", FMOD_DEFAULT, 0, &pSound);
}
