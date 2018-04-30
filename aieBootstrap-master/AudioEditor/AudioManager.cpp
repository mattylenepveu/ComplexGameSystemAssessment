#include "AudioManager.h"
#include <iostream>
#include <stddef.h>

AudioManager::AudioManager()
{
}

AudioManager::~AudioManager()
{
}

bool AudioManager::Create()
{
	m_pSystem = NULL;
	m_bIsPlaying = false;
	m_bIsPaused = false;

	result = FMOD::System_Create(&m_pSystem);

	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result);
		return false;
	}

	result = m_pSystem->init(512, FMOD_INIT_NORMAL, 0);

	m_pSystem->getChannel(0, &m_pChannel);

	m_pChannelGroup->getChannel(0, &m_pChannel);

	// Initialize FMOD with 512 channels
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result);
		return false;
	}

	return true;
}

void AudioManager::Destroy()
{
	m_pSound->release();
	m_pSystem->close();
}

void AudioManager::UpdateAudio()
{
	m_pSystem->update();
	float* p1 =0;
	m_pChannel->setPitch(0.5f);
	m_pChannel->getPitch(p1);
	std::cout << p1 << std::endl;
}

void AudioManager::LoadAudio(const char* pAudioName)
{
	result = m_pSystem->createSound(pAudioName, FMOD_DEFAULT, 0, &m_pSound);
}

void AudioManager::PauseAudio()
{
	if (m_bIsPlaying)
	{
		m_pChannel->setPaused(true);
		m_bIsPlaying = false;
		m_bIsPaused = true;
	}
}

void AudioManager::PlayAudio()
{
	if (!m_bIsPlaying)
	{
		if (m_bIsPaused)
		{
			m_pChannel->setPaused(false);
			m_bIsPlaying = true;
			m_bIsPaused = false;
		}
		else
		{
			result = m_pSystem->playSound(m_pSound, 0, false, &m_pChannel);
			m_bIsPlaying = true;
		}
	}
}

void AudioManager::StopAudio()
{
	if (m_bIsPlaying)
	{
		m_pChannel->setPaused(true);
		m_bIsPlaying = false;
	}

	if (m_bIsPaused)
	{
		m_bIsPaused = false;
	}
}

void AudioManager::AdjustFrequency(float fFrequency)
{
	m_pChannel->setFrequency(fFrequency);
}

void AudioManager::AdjustPitch(float fPitch)
{
	m_pChannel->setPitch(fPitch);
}
