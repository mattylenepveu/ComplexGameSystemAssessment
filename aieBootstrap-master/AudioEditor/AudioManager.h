#pragma once

// Include(s)
#include "fmod.h"
#include "fmod.hpp"

//--------------------------------------------------------------------------------
// AudioManager class managers the status and properties of any audio.
//--------------------------------------------------------------------------------
class AudioManager
{
public:
	//--------------------------------------------------------------------------------
	// Default Constructor (Not Being Used).
	//--------------------------------------------------------------------------------
	AudioManager();

	//--------------------------------------------------------------------------------
	// Default Destructor (Not Being Used).
	//--------------------------------------------------------------------------------
	~AudioManager();

	//--------------------------------------------------------------------------------
	// Acts as the AudioManager's constructor by initialising values.
	//
	// Return:
	//		Returns a bool indicating if everything has been created properly.
	//--------------------------------------------------------------------------------
	bool Create();

	//--------------------------------------------------------------------------------
	// Acts as the AudioManager's Destructor by deleting value's from the heap.
	//--------------------------------------------------------------------------------
	void Destroy();

	//--------------------------------------------------------------------------------
	// Calls the FMOD System's update function.
	//--------------------------------------------------------------------------------
	void UpdateAudio();

	//--------------------------------------------------------------------------------
	// Creates the audio and stores the result with any errors found in FMOD result.
	//
	// Param:
	//		pAudioName: A constant array of chars identifying the name of the audio.
	//--------------------------------------------------------------------------------
	void LoadAudio(const char* pAudioName);

	//--------------------------------------------------------------------------------
	// Pauses the created audio when called.
	//--------------------------------------------------------------------------------
	void PauseAudio();

	//--------------------------------------------------------------------------------
	// Plays the created audio when called and if the audio has been created.
	//--------------------------------------------------------------------------------
	void PlayAudio();

	//--------------------------------------------------------------------------------
	// Stops the created audio when called and sends audio position back to start.
	//--------------------------------------------------------------------------------
	void StopAudio();

	//--------------------------------------------------------------------------------
	// Adjusts the pitch of the audio when called.
	//
	// Param:
	//		fPitch: A float that represents the new pitch of the audio.
	//--------------------------------------------------------------------------------
	void AdjustPitch(float fPitch);

	//--------------------------------------------------------------------------------
	// Adjusts the volume of the audio when called.
	//
	// Param:
	//		fPitch: A float that represents the changed volume of the audio.
	//--------------------------------------------------------------------------------
	void AdjustVolume(float fVolume);

	//--------------------------------------------------------------------------------
	// Function calls "release" from the FMOD Sound class.
	//--------------------------------------------------------------------------------
	void ReleaseSound();

private:
	// Represents pointers to the System, Sound, Channel, ChannelGroup and DSP of FMOD
	FMOD::System* m_pSystem;
	FMOD::Sound* m_pSound;
	FMOD::Channel* m_pChannel;
	FMOD::ChannelGroup* m_pChannelGroup;
	FMOD::DSP* m_pDSP;

	// FMOD_RESULT used to store the outcome of calling various FMOD functions
	FMOD_RESULT result;

	// Bool indicates if audio is playing
	bool m_bIsPlaying;

	// Bool used to find out if the audio is set to paused
	bool m_bIsPaused;

	// Float used to store the frequency of the audio into
	float m_fFrequency;

	// The pitch of the audio is stores in the float
	float m_fPitch;
};
