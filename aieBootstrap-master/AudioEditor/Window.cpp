#include "Window.h"

Window::Window()
{
	// Initializes the Audio Manager pointer
	audioManager = new AudioManager();

	// Boots up the FMOD system
	audioManager->Create();

	// Loads audio from the audio manager
	audioManager->LoadAudio("../bin/audio/background_music.ogg");

	boxSize = ImVec2(90, 90);
}

Window::~Window()
{
	audioManager->Destroy();
	delete audioManager;
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
		ImGui::MenuItem("New Project");

		if (ImGui::MenuItem("Load Audio"))
		{
			ImGui::OpenPopup(filename);
		}

		bool result = false;

		ImGui::MenuItem("Save Audio");
		ImGui::MenuItem("Save Audio As");
		ImGui::EndMenu();
	}

	int verticalSpacing = 70;
	for (int i = 0; i < verticalSpacing; ++i)
	{
		ImGui::Spacing();
	}

	ImGui::Indent(300.0f);
	bool bPause = ImGui::Button("PAUSE", ImVec2(50, 20));

	ToolTip("Pauses the audio when the audio is playing");

	if (bPause)
	{
		audioManager->PauseAudio();
	}

	ImGui::SameLine();
	ImGui::Indent(100.0f);
	bool bPlay = ImGui::Button("PLAY", ImVec2(50, 20));

	ToolTip("Plays the audio if the audio isn't already playing");

	if (bPlay)
	{
		// Plays the audio from the audio manager
		audioManager->PlayAudio();
	}

	ImGui::SameLine();
	ImGui::Indent(100.0f);
	bool bStop = ImGui::Button("STOP", ImVec2(50, 20));

	ToolTip("Stops the audio and resets audio time back to the start");

	if (bStop)
	{
		audioManager->StopAudio();
	}

	ImGui::Unindent(513.0f);
	verticalSpacing = 5;
	for (int i = 0; i < verticalSpacing; ++i)
	{
		ImGui::Spacing();
	}

	ImGui::Indent(120.0f);
	ImGui::TextWrapped("FREQUENCY"),

	ImGui::SameLine();
	ImGui::Indent(300.0f);
	ImGui::TextWrapped("PITCH");

	ImGui::SameLine();
	ImGui::Indent(300.0f);
	ImGui::TextWrapped("SPEED");

	ImGui::Spacing();
	ImGui::Unindent(612.0f);

	ImGui::ListBoxHeader("", boxSize);
	ImGui::Selectable("Very Low", false);
	ImGui::Selectable("Low", false);
	ImGui::Selectable("Average", true);
	ImGui::Selectable("High", false);
	ImGui::Selectable("Very High", false);
	ImGui::ListBoxFooter();

	ImGui::SameLine();
	ImGui::Indent(285.0f);

	ImGui::ListBoxHeader(" ", boxSize);
	ImGui::Selectable("Very Low", false);
	ImGui::Selectable("Low", false);
	ImGui::Selectable("Average", true);
	ImGui::Selectable("High", false);
	ImGui::Selectable("Very High", false);
	ImGui::ListBoxFooter();

	ImGui::SameLine();
	ImGui::Indent(300.0f);

	ImGui::ListBoxHeader("  ", boxSize);
	ImGui::Selectable("Very Slow", false);
	ImGui::Selectable("Slow", false);
	ImGui::Selectable("Average", true);
	ImGui::Selectable("Fast", false);
	ImGui::Selectable("Very Fast", false);
	ImGui::ListBoxFooter();

	ImGui::End();
}

void Window::ToolTip(char* pToolTip)
{
	if (ImGui::IsItemHovered())
	{
		ImGui::SetTooltip(pToolTip);
	}
}

void Window::SetCurrentFolder(char* pCurrentFolder)
{
	CurrentFolder = pCurrentFolder;
}

char* Window::GetCurrentFolder()
{
	return CurrentFolder;
}
