// Include(s)
#include "Window.h"
#include "Texture.h"
#include <iostream>

// Const floats represent the pitch adjustments the user can make with pitch list
static const float VLPITCH = 0.5f;
static const float LPITCH = 0.75f;
static const float APITCH = 1.0f;
static const float HPITCH = 1.1f;
static const float VHPITCH = 1.5f;

// Const floats indicate the volume adjustments the user can make with volume list
static const float VLVOLUME = 0.1f;
static const float LVOLUME = 0.25f;
static const float AVOLUME = 0.5f;
static const float HVOLUME = 0.75f;
static const float VHVOLUME = 1.0f;

//--------------------------------------------------------------------------------
// Default Constructor.
//--------------------------------------------------------------------------------
Window::Window()
{
	// Initializes the Audio Manager pointer
	m_pAudioManager = new AudioManager();

	// Calls the AudioManager's create function to initialize FMOD 
	m_pAudioManager->Create();

	// Initializes the Box and Button size as ImVec2
	m_v2BoxSize = ImVec2(90, 90);
	m_v2ButtonSize = ImVec2(50, 20);

	// Initializes a "new" array of chars with a default string
	m_chBuf = new char[100]{ "Filename Here with File Extension" };

	// Initializes a "new" array of chars which is the file directory for audio
	m_chFileDir = new char[32]{ "../bin/audio/" };

	// Sets all bools to false when class is first called
	m_bMuted = false;
	m_bLoad = false;
	m_bLoaded = false;
	m_bPlaying = false;

	// For loop runs for the array of bools
	for (int i = 0; i < 5; ++i)
	{
		// Sets the middle choice in the pitch and volume list to be true
		if (i == 2)
		{
			m_abPitch[2] = true;
			m_abVol[2] = true;
		}

		// Sets every other option in pitch and volume list to bo false
		else
		{
			m_abPitch[i] = false;
			m_abVol[i] = false;
		}
	}
}

//--------------------------------------------------------------------------------
// Default Destructor.
//--------------------------------------------------------------------------------
Window::~Window()
{
	// Calls AudioManager's Destroy function to destroy FMOD's values from the heap
	m_pAudioManager->Destroy();

	// Deletes all values from the Window classes' heap
	delete m_pAudioManager;
	delete m_chBuf;
	delete m_chFileDir;
}

//--------------------------------------------------------------------------------
// Updates all of the mechanics of the window every frame.
//
// Param:
//		pFileName: An array of chars that identifies the window name.
//		bOpen: A bool that checks if the window should open or not.
//--------------------------------------------------------------------------------
void Window::UpdateWindow(char* pFilename, bool bOpen)
{
	// Sets the Window size 
	ImGui::SetNextWindowSize(ImVec2(900.0f, 500.0f));
	ImGui::Begin(pFilename, &bOpen, ImGuiWindowFlags_NoResize);

	// Updates the Audio Manager every frame
	m_pAudioManager->UpdateAudio();

	ImGui::BeginMenuBar();

	if (ImGui::BeginMenu("File"))
	{
		if (ImGui::MenuItem("Load Audio"))
		{
			if (m_bPlaying)
			{
				m_pAudioManager->StopAudio();
				m_bPlaying = false;
			}

			m_bLoad = true;
		}

		ImGui::EndMenu();
	}

	int verticalSpacing;
	if (m_bLoad)
	{
		verticalSpacing = 54;
		LoadSound();
	}
	else
	{
		verticalSpacing = 60;
	}

	for (int i = 0; i < verticalSpacing; ++i)
	{
		ImGui::Spacing();
	}

	ImGui::Indent(300.0f);
	bool bPause = ImGui::Button("PAUSE", m_v2ButtonSize);

	ToolTip("Pauses the audio when the audio is playing");

	if (bPause)
	{
		m_bPlaying = false;
		m_pAudioManager->PauseAudio();
	}

	ImGui::SameLine();
	ImGui::Indent(100.0f);
	bool bPlay = ImGui::Button("PLAY", m_v2ButtonSize);

	ToolTip("Plays the audio if the audio isn't already playing and records the audio");

	if (bPlay && m_bLoaded)
	{
		m_bPlaying = true;

		// Plays the audio from the audio manager
		m_pAudioManager->PlayAudio();
	}

	ImGui::SameLine();
	ImGui::Indent(100.0f);
	bool bStop = ImGui::Button("STOP", m_v2ButtonSize);

	ToolTip("Stops the audio and resets audio time back to the start");

	if (bStop)
	{
		m_bPlaying = false;
		m_pAudioManager->StopAudio();
	}

	ImGui::Unindent(513.0f);

	if (m_bPlaying)
	{
		verticalSpacing = 4;
		ImGui::Indent(375.0f);
		ImGui::Text("Song now playing...");
		ImGui::Unindent(375.0f);
	}
	else
	{
		verticalSpacing = 8;
	}
	
	for (int i = 0; i < verticalSpacing; ++i)
	{
		ImGui::Spacing();
	}

	ImGui::Indent(413.0f);
	bool bMute = ImGui::Button("MUTE", m_v2ButtonSize);

	ToolTip("Turns the audio down to zero");

	if (bMute)
	{
		if (!m_bMuted)
		{
			m_pAudioManager->AdjustVolume(0.0f);
			m_bMuted = true;
		}
		else
		{
			if (m_abVol[0])
			{
				m_pAudioManager->AdjustVolume(VLVOLUME);
			}

			if (m_abVol[1])
			{
				m_pAudioManager->AdjustVolume(LVOLUME);
			}

			if (m_abVol[2])
			{
				m_pAudioManager->AdjustVolume(AVOLUME);
			}

			if (m_abVol[3])
			{
				m_pAudioManager->AdjustVolume(HVOLUME);
			}

			if (m_abVol[4])
			{
				m_pAudioManager->AdjustVolume(VHVOLUME);
			}

			m_bMuted = false;
		}
	}

	ImGui::Unindent(420.0F);
	verticalSpacing = 2;
	for (int i = 0; i < verticalSpacing; ++i)
	{
		ImGui::Spacing();
	}

	AdjustSound();

	ImGui::End();
}

//--------------------------------------------------------------------------------
// Loads the sound into the application.
//--------------------------------------------------------------------------------
void Window::LoadSound()
{
	ImGui::InputText("Directory", m_chBuf, 50);

	ImGui::SameLine();
	if (ImGui::Button("Load", m_v2ButtonSize))
	{
		for (int i = 0; i < 3; ++i)
		{
			m_pAudioManager->ReleaseSound();

			std::string FileDir = m_chFileDir;
			std::string FileName = m_chBuf;
			std::string FullFile = FileDir + FileName;

			const char* chFullFile = FullFile.c_str();
			m_pAudioManager->LoadAudio(chFullFile);
		}

		m_bLoad = false;
		m_bLoaded = true;
	}
}

//--------------------------------------------------------------------------------
// Allows a tool tip to be added to buttons.
//
// Param:
//		pToolTip: An array of chars that indicates what the tool tip should say.
//--------------------------------------------------------------------------------
void Window::ToolTip(char* pToolTip)
{
	if (ImGui::IsItemHovered())
	{
		ImGui::SetTooltip(pToolTip);
	}
}

//--------------------------------------------------------------------------------
// Allows for the loaded in audio to be modified. 
//--------------------------------------------------------------------------------
void Window::AdjustSound()
{
	ImGui::Indent(270.0f);
	ImGui::TextWrapped("PITCH");

	ImGui::SameLine();
	ImGui::Indent(300.0f);
	ImGui::TextWrapped("VOLUME");

	ImGui::Spacing();
	ImGui::Unindent(577.0f);

	ImGui::SameLine();
	ImGui::Indent(250.0f);

	ImGui::ListBoxHeader(" ", m_v2BoxSize);
	bool bPitchVL = ImGui::Selectable("Very Low", m_abPitch[0]);

	if (bPitchVL && !m_abPitch[0])
	{
		m_pAudioManager->AdjustPitch(VLPITCH);
		m_abPitch[0] = true;

		for (int i = 0; i < 5; ++i)
		{
			if (i != 0)
			{
				m_abPitch[i] = false;
			}
		}
	}

	bool bPitchL = ImGui::Selectable("Low", m_abPitch[1]);

	if (bPitchL && !m_abPitch[1])
	{
		m_pAudioManager->AdjustPitch(LPITCH);
		m_abPitch[1] = true;

		for (int i = 0; i < 5; ++i)
		{
			if (i != 1)
			{
				m_abPitch[i] = false;
			}
		}
	}

	bool bPitchA = ImGui::Selectable("Average", m_abPitch[2]);

	if (bPitchA && !m_abPitch[2])
	{
		m_pAudioManager->AdjustPitch(APITCH);
		m_abPitch[2] = true;

		for (int i = 0; i < 5; ++i)
		{
			if (i != 2)
			{
				m_abPitch[i] = false;
			}
		}
	}

	bool bPitchH = ImGui::Selectable("High", m_abPitch[3]);

	if (bPitchH && !m_abPitch[3])
	{
		m_pAudioManager->AdjustPitch(HPITCH);
		m_abPitch[3] = true;

		for (int i = 0; i < 5; ++i)
		{
			if (i != 3)
			{
				m_abPitch[i] = false;
			}
		}
	}

	bool bPitchVH = ImGui::Selectable("Very High", m_abPitch[4]);

	if (bPitchVH && !m_abPitch[4])
	{
		m_pAudioManager->AdjustPitch(VHPITCH);
		m_abPitch[4] = true;

		for (int i = 0; i < 5; ++i)
		{
			if (i != 4)
			{
				m_abPitch[i] = false;
			}
		}
	}
	ImGui::ListBoxFooter();

	ImGui::SameLine();
	ImGui::Indent(300.0f);

	ImGui::ListBoxHeader("  ", m_v2BoxSize);
	bool bVolVL = ImGui::Selectable("Very Low", m_abVol[0]);

	if (bVolVL && !m_abVol[0])
	{
		m_pAudioManager->AdjustVolume(VLVOLUME);
		m_abVol[0] = true;

		for (int i = 0; i < 5; ++i)
		{
			if (i != 0)
			{
				m_abVol[i] = false;
			}
		}
	}

	bool bVolL = ImGui::Selectable("Low", m_abVol[1]);

	if (bVolL && !m_abVol[1])
	{
		m_pAudioManager->AdjustVolume(LVOLUME);
		m_abVol[1] = true;

		for (int i = 0; i < 5; ++i)
		{
			if (i != 1)
			{
				m_abVol[i] = false;
			}
		}
	}

	bool bVolA = ImGui::Selectable("Average", m_abVol[2]);

	if (bVolA && !m_abVol[2])
	{
		m_pAudioManager->AdjustVolume(AVOLUME);
		m_abVol[2] = true;

		for (int i = 0; i < 5; ++i)
		{
			if (i != 2)
			{
				m_abVol[i] = false;
			}
		}
	}

	bool bVolH = ImGui::Selectable("High", m_abVol[3]);

	if (bVolH && !m_abVol[3])
	{
		m_pAudioManager->AdjustVolume(HVOLUME);
		m_abVol[3] = true;

		for (int i = 0; i < 5; ++i)
		{
			if (i != 3)
			{
				m_abVol[i] = false;
			}
		}
	}

	bool bVolVH = ImGui::Selectable("Very High", m_abVol[4]);

	if (bVolVH && !m_abVol[4])
	{
		m_pAudioManager->AdjustVolume(VHVOLUME);
		m_abVol[4] = true;

		for (int i = 0; i < 5; ++i)
		{
			if (i != 4)
			{
				m_abVol[i] = false;
			}
		}
	}

	ImGui::ListBoxFooter();
}
