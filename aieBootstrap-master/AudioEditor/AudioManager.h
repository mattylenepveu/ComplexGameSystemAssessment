#pragma once
#include "fmod.h"
#include "fmod.hpp"

class AudioManager
{
public:
	AudioManager();
	~AudioManager();

	bool Create();
	void Destroy();

	void UpdateAudio();
	void LoadAudio(const char* pAudioName);

	void PauseAudio();
	void PlayAudio();
	void StopAudio();

	void AdjustFrequency(float fFrequency);
	void AdjustPitch(float fPitch);

private:
	FMOD::System* m_pSystem;
	FMOD::Sound* m_pSound;
	FMOD::Channel* m_pChannel;
	FMOD::ChannelGroup* m_pChannelGroup;
	FMOD::DSP* m_pDSP;
	FMOD_RESULT result;

	bool m_bIsPlaying;
	bool m_bIsPaused;

	float m_fFrequency;
	float m_fPitch;
};
