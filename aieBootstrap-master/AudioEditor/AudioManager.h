#pragma once
#include "fmod.h"
#include "fmod.hpp"

class AudioManager
{
public:
	AudioManager();
	~AudioManager();

	bool SystemStart();
	void LoadSound();

private:
	FMOD::System* m_pSystem;
	FMOD::Sound* m_pSound;
	FMOD::Channel* m_pChannel;
	FMOD::ChannelGroup* m_pChannelGroup;
	FMOD::DSP* m_pDSP;
	FMOD_RESULT result;
};
