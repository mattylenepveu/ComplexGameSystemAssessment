#include "Window.h"
#include <iostream>

static const float VLPITCH = 0.5f;
static const float LPITCH = 0.75f;
static const float APITCH = 1.0f;
static const float HPITCH = 1.25f;
static const float VHPITCH = 1.5f;

static const float VLVOLUME = 0.1f;
static const float LVOLUME = 0.25f;
static const float AVOLUME = 0.5f;
static const float HVOLUME = 0.75f;
static const float VHVOLUME = 1.0f;

Window::Window()
{
	// Initializes the Audio Manager pointer
	audioManager = new AudioManager();

	// Boots up the FMOD system
	audioManager->Create();

	m_chBuf = new char[100]{ "Filename Here" };
	m_chFileDir = new char[32]{ "../bin/audio/" };

	boxSize = ImVec2(90, 90);
	buttonSize = ImVec2(50, 20);

	m_bMuted = false;
	m_bLoad = false;
	m_bLoaded = false;
	m_bPlaying = false;

	for (int i = 0; i < 5; ++i)
	{
		if (i == 2)
		{
			m_abPitch[2] = true;
			m_abVol[2] = true;
		}
		else
		{
			m_abPitch[i] = false;
			m_abVol[i] = false;
		}
	}
}

Window::~Window()
{
	audioManager->Destroy();

	delete audioManager;
	delete m_chBuf;
}

void Window::UpdateWindow(char* filename, bool open)
{
	ImGui::SetNextWindowSize(ImVec2(900.0f, 500.0f));
	ImGui::Begin(filename, &open, ImGuiWindowFlags_NoResize);

	// Updates the Audio Manager every frame
	audioManager->UpdateAudio();

	ImGui::BeginMenuBar();

	if (ImGui::BeginMenu("File"))
	{
		if (ImGui::MenuItem("New Project"))
		{
			// Load a New Project
		}

		if (ImGui::MenuItem("Load Audio"))
		{
			if (m_bPlaying)
			{
				audioManager->StopAudio();
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
	bool bPause = ImGui::Button("PAUSE", buttonSize);

	ToolTip("Pauses the audio when the audio is playing");

	if (bPause)
	{
		m_bPlaying = false;
		audioManager->PauseAudio();
	}

	ImGui::SameLine();
	ImGui::Indent(100.0f);
	bool bPlay = ImGui::Button("PLAY", buttonSize);

	ToolTip("Plays the audio if the audio isn't already playing and records the audio");

	if (bPlay && m_bLoaded)
	{
		m_bPlaying = true;

		// Plays the audio from the audio manager
		audioManager->PlayAudio();
	}

	ImGui::SameLine();
	ImGui::Indent(100.0f);
	bool bStop = ImGui::Button("STOP", buttonSize);

	ToolTip("Stops the audio and resets audio time back to the start");

	if (bStop)
	{
		m_bPlaying = false;
		audioManager->StopAudio();
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
	bool bMute = ImGui::Button("MUTE", buttonSize);

	ToolTip("Turns the audio down to zero");

	if (bMute)
	{
		if (!m_bMuted)
		{
			audioManager->AdjustVolume(0.0f);
			m_bMuted = true;
		}
		else
		{
			if (m_abVol[0])
			{
				audioManager->AdjustVolume(VLVOLUME);
			}

			if (m_abVol[1])
			{
				audioManager->AdjustVolume(LVOLUME);
			}

			if (m_abVol[2])
			{
				audioManager->AdjustVolume(AVOLUME);
			}

			if (m_abVol[3])
			{
				audioManager->AdjustVolume(HVOLUME);
			}

			if (m_abVol[4])
			{
				audioManager->AdjustVolume(VHVOLUME);
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

void Window::LoadSound()
{
	ImGui::InputText("Directory", m_chBuf, 50);

	ImGui::SameLine();
	if (ImGui::Button("Load", buttonSize))
	{
		for (int i = 0; i < 3; ++i)
		{
			audioManager->ReleaseSound();

			std::string FileDir = m_chFileDir;
			std::string FileName = m_chBuf;
			std::string FullFile = FileDir + FileName;

			const char* chFullFile = FullFile.c_str();
			audioManager->LoadAudio(chFullFile);
		}

		m_bLoad = false;
		m_bLoaded = true;
	}
}

void Window::ToolTip(char* pToolTip)
{
	if (ImGui::IsItemHovered())
	{
		ImGui::SetTooltip(pToolTip);
	}
}

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

	ImGui::ListBoxHeader(" ", boxSize);
	bool bPitchVL = ImGui::Selectable("Very Low", m_abPitch[0]);

	if (bPitchVL && !m_abPitch[0])
	{
		audioManager->AdjustPitch(VLPITCH);
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
		audioManager->AdjustPitch(LPITCH);
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
		audioManager->AdjustPitch(APITCH);
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
		audioManager->AdjustPitch(HPITCH);

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
		audioManager->AdjustPitch(VHPITCH);
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

	ImGui::ListBoxHeader("  ", boxSize);
	bool bVolVL = ImGui::Selectable("Very Low", m_abVol[0]);

	if (bVolVL && !m_abVol[0])
	{
		audioManager->AdjustVolume(VLVOLUME);
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
		audioManager->AdjustVolume(LVOLUME);
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
		audioManager->AdjustVolume(AVOLUME);
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
		audioManager->AdjustVolume(HVOLUME);
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
		audioManager->AdjustVolume(VHVOLUME);
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
