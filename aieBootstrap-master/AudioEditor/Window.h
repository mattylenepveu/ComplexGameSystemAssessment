#pragma once
#include "Imgui.h"
#include "AudioManager.h"

class Window
{
public:
	Window();
	~Window();

	void UpdateWindow(char* filename, bool open);
	void ToolTip(char* pToolTip);

	void SetCurrentFolder(char* CurrentFolder);
	char* GetCurrentFolder();

private:
	AudioManager * audioManager;
	ImVec2 boxSize;
	char* CurrentFolder;
};

