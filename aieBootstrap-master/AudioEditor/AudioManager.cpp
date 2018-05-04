// Include(s)
#include "AudioManager.h"
#include <iostream>
#include <stddef.h>

//--------------------------------------------------------------------------------
// Default Constructor.
//--------------------------------------------------------------------------------
AudioManager::AudioManager() 
{
	// Initializes playing and paused bools to false
	m_bIsPlaying = false;
	m_bIsPaused = false;
}

//--------------------------------------------------------------------------------
// Acts as the AudioManager's constructor by initialising values.
//
// Return:
//		Returns a bool indicating if everything has been created properly.
//--------------------------------------------------------------------------------
bool AudioManager::Create()
{
	// Sets the FMOD system pointer to a null value rather than garbage memory
	m_pSystem = NULL;

	// Creates the FMOD System and stores any error result in FMOD result
	result = FMOD::System_Create(&m_pSystem);

	// Checks if any errors have occured
	if (result != FMOD_OK)
	{
		// Prints the error to console and returns false for failing to startup
		printf("FMOD error! (%d) %s\n", result);
		return false;
	}

	// Initialize FMOD with 512 channels and stores any errors in FMOD result
	result = m_pSystem->init(512, FMOD_INIT_NORMAL, 0);

	// Creates a new Channel Group for the FMOD system
	m_pSystem->createChannelGroup("MyChannelGroup", &m_pChannelGroup);

	// Checks if any errors have occured
	if (result != FMOD_OK)
	{
		// Prints the error to console and returns false for failing to startup
		printf("FMOD error! (%d) %s\n", result);
		return false;
	}

	// Returns true as AudioManager must have started up correctly
	return true;
}

//--------------------------------------------------------------------------------
// Acts as the AudioManager's Destructor by deleting value's from the heap.
//--------------------------------------------------------------------------------
void AudioManager::Destroy()
{
	// Calls release to release sound and closes FMOD system
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
	// Checks if audio is currently playing
	if (m_bIsPlaying)
	{
		// Sets paused to true via the channel
		m_pChannel->setPaused(true);

		// Sets playing bool to false and paused bool to true
		m_bIsPlaying = false;
		m_bIsPaused = true;
	}
}

//--------------------------------------------------------------------------------
// Plays the created audio when called and if the audio has been created.
//--------------------------------------------------------------------------------
void AudioManager::PlayAudio()
{
	// Checks if audio isn't playing
	if (!m_bIsPlaying)
	{
		// Checks if the audio is paused
		if (m_bIsPaused)
		{
			// Sets paused to false via the channel
			m_pChannel->setPaused(false);

			// Sets playing bool to true and paused bool to false
			m_bIsPlaying = true;
			m_bIsPaused = false;
		}
		else
		{
			// If audio isn't paused, system plays the sound and stores errors in result
			result = m_pSystem->playSound(m_pSound, m_pChannelGroup, false, &m_pChannel);

			// Sets playing bool to be true
			m_bIsPlaying = true;  
		}
	}
}

//--------------------------------------------------------------------------------
// Stops the created audio when called and sends audio position back to start.
//--------------------------------------------------------------------------------
void AudioManager::StopAudio()
{
	// Checks if any audio is playing
	if (m_bIsPlaying)
	{
		// Sets paused to be true via the channel
		m_pChannel->setPaused(true);

		// Sets is playing bool to be false
		m_bIsPlaying = false;
	}

	// If audio is paused, then set paused bool to false
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
	// Calls set pitch function from the Channel Group passing in the new pitch
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
	// Calls set volume function from the Channel Group passing in the new volume
	m_pChannelGroup->setVolume(fVolume);
}

//--------------------------------------------------------------------------------
// Function calls "release" from the FMOD Sound class.
//--------------------------------------------------------------------------------
void AudioManager::ReleaseSound()
{
	m_pSound->release();
}
