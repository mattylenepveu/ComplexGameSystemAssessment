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

	m_pSystem->createChannelGroup("MyChannelGroup", &m_pChannelGroup);

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
}

void AudioManager::LoadAudio(const char* pAudioName)
{
	result = m_pSystem->createSound(pAudioName, FMOD_LOOP_NORMAL, 0, &m_pSound);
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
			result = m_pSystem->playSound(m_pSound, m_pChannelGroup, false, &m_pChannel);
			result = m_pSystem->recordStart(0, m_pSound, false);
			m_bIsPlaying = true;  
		}
	}
}

void AudioManager::StopAudio()
{
	if (m_bIsPlaying)
	{
		result = m_pSystem->recordStop(0);
		m_pChannel->setPaused(true);
		m_bIsPlaying = false;
	}

	if (m_bIsPaused)
	{
		m_bIsPaused = false;
	}
}

void AudioManager::AdjustPitch(float fPitch)
{
	m_pChannelGroup->setPitch(fPitch);
}

void AudioManager::AdjustVolume(float fVolume)
{
	m_pChannelGroup->setVolume(fVolume);
}

void AudioManager::ReleaseSound()
{
	m_pSound->release();
}
