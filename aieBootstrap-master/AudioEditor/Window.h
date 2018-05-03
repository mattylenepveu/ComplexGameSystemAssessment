#pragma once

// Include(s)
#include "Imgui.h"
#include "AudioManager.h"
#include "Renderer2D.h"

//--------------------------------------------------------------------------------
// Window class draws and updates the ImGui window that the application will use.
//--------------------------------------------------------------------------------
class Window
{
public:
	//--------------------------------------------------------------------------------
	// Default Constructor.
	//--------------------------------------------------------------------------------
	Window();

	//--------------------------------------------------------------------------------
	// Default Destructor.
	//--------------------------------------------------------------------------------
	~Window();

	//--------------------------------------------------------------------------------
	// Updates all of the mechanics of the window every frame.
	//
	// Param:
	//		pFileName: An array of chars that identifies the window name.
	//		bOpen: A bool that checks if the window should open or not.
	//--------------------------------------------------------------------------------
	void UpdateWindow(char* pFilename, bool bOpen);

	//--------------------------------------------------------------------------------
	// Loads the sound into the application.
	//--------------------------------------------------------------------------------
	void LoadSound();

	//--------------------------------------------------------------------------------
	// Allows a tool tip to be added to buttons.
	//
	// Param:
	//		pToolTip: An array of chars that indicates what the tool tip should say.
	//--------------------------------------------------------------------------------
	void ToolTip(char* pToolTip);

	//--------------------------------------------------------------------------------
	// Allows for the loaded in audio to be modified. 
	//--------------------------------------------------------------------------------
	void AdjustSound();

private:
	// Allows for Window class to access properties from the AudioManager class
	AudioManager* m_pAudioManager;

	// Vector2 indicates the size of the box that contains a list in it
	ImVec2 m_v2BoxSize;

	// Vector2 represents the size of the window's buttons
	ImVec2 m_v2ButtonSize;

	// Array of chars indicates the default message for the "Load Audio" text box
	char* m_chBuf;

	// Array of chars used to store the file directory for loading audio
	char* m_chFileDir;

	// Bool represents if audio is muted or not
	bool m_bMuted;

	// Bool indicates if the user is currently loading audio in to the program
	bool m_bLoad;

	// Bool used for checking if audio is loaded in to the window or not
	bool m_bLoaded;

	// Bool indicates if the audio is currently being played or not
	bool m_bPlaying;

	// Array of bools stores if drop down pitch list options are selected
	bool m_abPitch[5];

	// Array of bools stores if drop down volume list options are selected
	bool m_abVol[5];
};
