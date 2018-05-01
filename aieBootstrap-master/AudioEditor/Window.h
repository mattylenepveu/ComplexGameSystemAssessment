#pragma once
#include "Imgui.h"
#include "AudioManager.h"

class Window
{
public:
	Window();
	~Window();

	void UpdateWindow(char* filename, bool open);

	void LoadSound();
	void ToolTip(char* pToolTip);
	void AdjustSound();

private:
	AudioManager* audioManager;
	ImVec2 boxSize;
	ImVec2 buttonSize;

	char* m_chBuf;
	char* m_chFileDir;

	bool m_bMuted;
	bool m_bLoad;

	bool m_abPitch[5];
	bool m_abVol[5];
};
