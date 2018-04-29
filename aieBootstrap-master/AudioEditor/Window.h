#pragma once
#include "Imgui.h"

class Window
{
public:
	Window();
	~Window();

	bool ConsoleWindow(char* filename, bool open);
	bool DrawFolder(char* selected, bool returnOnSelection = false);

	void SetCurrentFolder(char* CurrentFolder);
	char* GetCurrentFolder();

private:
	ImVec2 boxSize;
	char* CurrentFolder;
};

