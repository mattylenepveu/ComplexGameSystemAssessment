// Include(s)
#include "AudioManager.h"
#include <iostream>
#include <stddef.h>

//--------------------------------------------------------------------------------
// Default Constructor.
//--------------------------------------------------------------------------------
AudioManager::AudioManager() 
{
	m_bIsPlaying = false;
	m_bIsPaused = false;
}

//--------------------------------------------------------------------------------
// Default Destructor (Not Being Used).
//--------------------------------------------------------------------------------
AudioManager::~AudioManager() {}

//--------------------------------------------------------------------------------
// Acts as the AudioManager's constructor by initialising values.
//
// Return:
//		Returns a bool indicating if everything has been created properly.
//--------------------------------------------------------------------------------
bool AudioManager::Create()
{
	m_pSystem = NULL;

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

//--------------------------------------------------------------------------------
// Acts as the AudioManager's Destructor by deleting value's from the heap.
//--------------------------------------------------------------------------------
void AudioManager::Destroy()
{
	m_pSound->release();
	m_pSystem->close();
}

//--------------------------------------------------------------------------------
// Calls the FMOD System's update function.
//--------------------------------------------------------------------------------
void AudioManager::UpdateAudio()
{
	m_pSystem->update();
}

//--------------------------------------------------------------------------------
// Creates the audio and stores the result with any errors found in FMOD result.
//
// Param:
//		pAudioName: A constant array of chars identifying the name of the audio.
//--------------------------------------------------------------------------------
void AudioManager::LoadAudio(const char* pAudioName)
{
	result = m_pSystem->createSound(pAudioName, FMOD_LOOP_NORMAL, 0, &m_pSound);
}

//--------------------------------------------------------------------------------
// Pauses the created audio when called.
//--------------------------------------------------------------------------------
void AudioManager::PauseAudio()
{
	if (m_bIsPlaying)
	{
		m_pChannel->setPaused(true);
		m_bIsPlaying = false;
		m_bIsPaused = true;
	}
}

//--------------------------------------------------------------------------------
// Plays the created audio when called and if the audio has been created.
//--------------------------------------------------------------------------------
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
			m_bIsPlaying = true;  
		}
	}
}

//--------------------------------------------------------------------------------
// Stops the created audio when called and sends audio position back to start.
//--------------------------------------------------------------------------------
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

//--------------------------------------------------------------------------------
// Adjusts the pitch of the audio when called.
//
// Param:
//		fPitch: A float that represents the new pitch of the audio.
//--------------------------------------------------------------------------------
void AudioManager::AdjustPitch(float fPitch)
{
	m_pChannelGroup->setPitch(fPitch);
}

//--------------------------------------------------------------------------------
// Adjusts the volume of the audio when called.
//
// Param:
//		fPitch: A float that represents the changed volume of the audio.
//--------------------------------------------------------------------------------
void AudioManager::AdjustVolume(float fVolume)
{
	m_pChannelGroup->setVolume(fVolume);
}

//--------------------------------------------------------------------------------
// Function calls "release" from the FMOD Sound class.
//--------------------------------------------------------------------------------
void AudioManager::ReleaseSound()
{
	m_pSound->release();
}
