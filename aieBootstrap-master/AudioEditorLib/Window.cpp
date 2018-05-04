// Include(s)
#include "Window.h"
#include "Texture.h"
#include <iostream>

// Const floats represent the pitch adjustments the user can make with pitch list
static const float VLPITCH = 0.5f;
static const float LPITCH = 0.75f;
static const float APITCH = 1.0f;
static const float HPITCH = 1.25f;
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

	// Initializes vertical spacing int to zero
	verticalSpacing = 0;

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
//--------------------------------------------------------------------------------
void Window::UpdateWindow(const char* pFilename)
{
	// Sets the Window size 
	ImGui::SetNextWindowSize(ImVec2(900.0f, 500.0f));
	ImGui::Begin(pFilename, NULL, ImGuiWindowFlags_NoResize);

	// Updates the Audio Manager every frame
	m_pAudioManager->UpdateAudio();

	// ImGui begins drawing the menu bar 
	ImGui::BeginMenuBar();

	// Checks if "File" is pressed in the menu bar
	if (ImGui::BeginMenu("File"))
	{
		// Checks if "Load Audio" is pressed under "File"
		if (ImGui::MenuItem("Load Audio"))
		{
			// Checks if audio is currently playing
			if (m_bPlaying)
			{
				// Stops audio from playing and sets playing bool to false
				m_pAudioManager->StopAudio();
				m_bPlaying = false;
			}

			// Switches the load bool to be true
			m_bLoad = true;
		}

		// Ends loading items under "File"
		ImGui::EndMenu();
	}

	// Checks if the load bool has been set to true
	if (m_bLoad)
	{
		// Sets vertical spacing to be 54 and calls "LoadSound" function
		verticalSpacing = 54;
		LoadSound();
	}
	else
	{
		// If load bool is false, set vertical spacing to equal 60
		verticalSpacing = 60;
	}

	// Adds spacing in ImGui window by what vertical spacing equals
	for (int i = 0; i < verticalSpacing; ++i)
	{
		ImGui::Spacing();
	}

	// Indents line horizontally by 300
	ImGui::Indent(300.0f);

	// Adds a button called "PAUSE" and stores if it's pressed in local bool
	bool bPause = ImGui::Button("PAUSE", m_v2ButtonSize);

	// Adds a tool tip for the pause button
	std::string toolLabel = "Pauses the audio when the audio is playing";
	ToolTip(toolLabel.c_str());

	// Checks if the pause button was pressed
	if (bPause)
	{
		// Sets playing bool to false and calls AudioManager's "PauseAudio" function
		m_bPlaying = false;
		m_pAudioManager->PauseAudio();
	}

	// Indents line horizontally by 100 on the same line as previous button
	ImGui::SameLine();
	ImGui::Indent(100.0f);

	// Adds a button called "PLAY" and stores if it's pressed in local bool
	bool bPlay = ImGui::Button("PLAY", m_v2ButtonSize);

	// Adds a tool tip for the play button
	ToolTip("Plays the audio if the audio isn't already playing and records the audio");

	// Checks if the play button was pressed and if audio is loaded in
	if (bPlay && m_bLoaded)
	{
		// Sets playing bool to true and plays the audio from the audio manager
		m_bPlaying = true;
		m_pAudioManager->PlayAudio();
	}

	// Indents line horizontally by 100 on the same line as previous button
	ImGui::SameLine();
	ImGui::Indent(100.0f);

	// Adds a button called "PLAY" and stores if it's pressed in local bool
	bool bStop = ImGui::Button("STOP", m_v2ButtonSize);

	// Adds a tool tip for the stop button
	ToolTip("Stops the audio and resets audio time back to the start");

	// Checks if the stop button was pressed
	if (bStop)
	{
		// Sets playing bool to be false and stops the audio in the AudioManager
		m_bPlaying = false;
		m_pAudioManager->StopAudio();
	}

	// Unindents the line horizontally by 513
	ImGui::Unindent(513.0f);

	// Checks if audio is currently playing
	if (m_bPlaying)
	{
		// Sets vertical spacing to equal four and indents line by 375
		verticalSpacing = 4;
		ImGui::Indent(375.0f);

		// Adds text to indicate that audio is currently playing
		ImGui::Text("Song now playing...");

		// Unindents the line back by 375
		ImGui::Unindent(375.0f);
	}
	else
	{
		// Sets vertical spacing to eight if no audio is playing
		verticalSpacing = 8;
	}
	
	// Adds spacing in ImGui window by what vertical spacing equals
	for (int i = 0; i < verticalSpacing; ++i)
	{
		ImGui::Spacing();
	}

	// Indents line horizontally by 413
	ImGui::Indent(413.0f);

	// Adds a button to mute audio and stores if it's pressed in a local bool
	bool bMute = ImGui::Button("MUTE", m_v2ButtonSize);

	// Adds a tool tip for the mute button
	ToolTip("Turns the audio down to zero");

	// Checks if mute button was pressed
	if (bMute)
	{
		// Checks if the audio isn't already muted
		if (!m_bMuted)
		{
			// Adjusts audio volume to zero and sets muted bool to true
			m_pAudioManager->AdjustVolume(0.0f);
			m_bMuted = true;
		}
		else
		{
			// If audio is already muted, check to see what volume was set to and set it back
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

			// Sets the muted bool back to false
			m_bMuted = false;
		}
	}

	// Unindents the line horizontally by 420 and sets vertical spacing to two
	ImGui::Unindent(420.0F);
	verticalSpacing = 2;

	// Adds spacing in ImGui window by what vertical spacing equals
	for (int i = 0; i < verticalSpacing; ++i)
	{
		ImGui::Spacing();
	}

	// Calls the "AdjustSound" function
	AdjustSound();

	// Ends detecting code for ImGui
	ImGui::End();
}

//--------------------------------------------------------------------------------
// Loads the sound into the application.
//--------------------------------------------------------------------------------
void Window::LoadSound()
{
	// Adds a text box with label "Directory", default message and a char limit of 50
	ImGui::InputText("Directory", m_chBuf, 50);

	// Allows for the load button to be on the same line as text box
	ImGui::SameLine();

	// Checks if the "Load" button was pressed
	if (ImGui::Button("Load", m_v2ButtonSize))
	{
		// Releases the audio in the AudioManager
		m_pAudioManager->ReleaseSound();

		// Stores the file directory in an std string
		std::string FileDir = m_chFileDir;

		// Stores the file name in an std string
		std::string FileName = m_chBuf;

		// Creates a complete file directory and stores it in an std string
		std::string FullFile = FileDir + FileName;

		// Converts the complete file directory to a const array of chars
		const char* chFullFile = FullFile.c_str();

		// Loads the audio from the AudioManager passing in the file directory
		m_pAudioManager->LoadAudio(chFullFile);

		// Sets load bool to false but loaded (as in audio loaded in) to true 
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
void Window::ToolTip(const char* pToolTip)
{
	// Checks if cursor is hovering over a button
	if (ImGui::IsItemHovered())
	{
		// If so the set a tool tip with the passed in message
		ImGui::SetTooltip(pToolTip);
	}
}

//--------------------------------------------------------------------------------
// Allows for the loaded in audio to be modified. 
//--------------------------------------------------------------------------------
void Window::AdjustSound()
{
	// Indents line by 270 and adds text "PITCH"
	ImGui::Indent(270.0f);
	ImGui::TextWrapped("PITCH");

	// Indents line by 300 and adds text "VOLUME" on the same line
	ImGui::SameLine();
	ImGui::Indent(300.0f);
	ImGui::TextWrapped("VOLUME");

	// Adds vertical spacing and unindents line by 577
	ImGui::Spacing();
	ImGui::Unindent(577.0f);

	// Indents line by 250 on the same line
	ImGui::SameLine();
	ImGui::Indent(250.0f);

	// Begins creating a List Box header for pitch with no heading and a set box size
	ImGui::ListBoxHeader(" ", m_v2BoxSize);

	// Adds a selectable for "Very Low" pitch and stores if it's pressed in local bool
	bool bPitchVL = ImGui::Selectable("Very Low", m_abPitch[0]);

	// Checks if selectable was pressed and is currently not highlighted
	if (bPitchVL && !m_abPitch[0])
	{
		// Adjusts the pitch to equal the very low float
		m_pAudioManager->AdjustPitch(VLPITCH);

		// Sets the Very Low pitch bool to be true
		m_abPitch[0] = true;

		// Sets every other pitch bool in array to be false
		for (int i = 0; i < 5; ++i)
		{
			if (i != 0)
			{
				m_abPitch[i] = false;
			}
		}
	}

	// Adds a selectable for "Low" pitch and stores if it's pressed in local bool
	bool bPitchL = ImGui::Selectable("Low", m_abPitch[1]);

	// Checks if selectable was pressed and is currently not highlighted
	if (bPitchL && !m_abPitch[1])
	{
		// Adjusts the pitch to equal the low float
		m_pAudioManager->AdjustPitch(LPITCH);

		// Sets the Low pitch bool to be true
		m_abPitch[1] = true;

		// Sets every other pitch bool in array to be false
		for (int i = 0; i < 5; ++i)
		{
			if (i != 1)
			{
				m_abPitch[i] = false;
			}
		}
	}

	// Adds a selectable for "Average" pitch and stores if it's pressed in local bool
	bool bPitchA = ImGui::Selectable("Average", m_abPitch[2]);

	// Checks if selectable was pressed and is currently not highlighted
	if (bPitchA && !m_abPitch[2])
	{
		// Adjusts the pitch to equal the average float
		m_pAudioManager->AdjustPitch(APITCH);

		// Sets the Average pitch bool to be true
		m_abPitch[2] = true;

		// Sets every other pitch bool in array to be false
		for (int i = 0; i < 5; ++i)
		{
			if (i != 2)
			{
				m_abPitch[i] = false;
			}
		}
	}

	// Adds a selectable for "High" pitch and stores if it's pressed in local bool
	bool bPitchH = ImGui::Selectable("High", m_abPitch[3]);

	// Checks if selectable was pressed and is currently not highlighted
	if (bPitchH && !m_abPitch[3])
	{
		// Adjusts the pitch to equal the high float
		m_pAudioManager->AdjustPitch(HPITCH);

		// Sets the High pitch bool to be true
		m_abPitch[3] = true;

		// Sets every other pitch bool in array to be false
		for (int i = 0; i < 5; ++i)
		{
			if (i != 3)
			{
				m_abPitch[i] = false;
			}
		}
	}

	// Adds a selectable for "Very High" pitch and stores if it's pressed in local bool
	bool bPitchVH = ImGui::Selectable("Very High", m_abPitch[4]);

	// Checks if selectable was pressed and is currently not highlighted
	if (bPitchVH && !m_abPitch[4])
	{
		// Adjusts the pitch to equal the very high float
		m_pAudioManager->AdjustPitch(VHPITCH);

		// Sets the Very High pitch bool to be true
		m_abPitch[4] = true;

		// Sets every other pitch bool in array to be false
		for (int i = 0; i < 5; ++i)
		{
			if (i != 4)
			{
				m_abPitch[i] = false;
			}
		}
	}

	// Ends detecting code for the pitch list box
	ImGui::ListBoxFooter();

	// Indents line by 300 on the same line as pitch list box
	ImGui::SameLine();
	ImGui::Indent(300.0f);

	// Begins creating a List Box header for volume with no heading and a set box size
	ImGui::ListBoxHeader("  ", m_v2BoxSize);

	// Adds a selectable for "Very Low" volume and stores if it's pressed in local bool
	bool bVolVL = ImGui::Selectable("Very Low", m_abVol[0]);

	// Checks if selectable was pressed and is currently not highlighted
	if (bVolVL && !m_abVol[0])
	{
		// Adjusts the volume to equal the very low float
		m_pAudioManager->AdjustVolume(VLVOLUME);

		// Sets the Very Low volume bool to be true
		m_abVol[0] = true;

		// Sets every other volume bool in array to be false
		for (int i = 0; i < 5; ++i)
		{
			if (i != 0)
			{
				m_abVol[i] = false;
			}
		}
	}

	// Adds a selectable for "Low" volume and stores if it's pressed in local bool
	bool bVolL = ImGui::Selectable("Low", m_abVol[1]);

	// Checks if selectable was pressed and is currently not highlighted
	if (bVolL && !m_abVol[1])
	{
		// Adjusts the volume to equal the low float
		m_pAudioManager->AdjustVolume(LVOLUME);

		// Sets the Low volume bool to be true
		m_abVol[1] = true;

		// Sets every other volume bool in array to be false
		for (int i = 0; i < 5; ++i)
		{
			if (i != 1)
			{
				m_abVol[i] = false;
			}
		}
	}

	// Adds a selectable for "Average" volume and stores if it's pressed in local bool
	bool bVolA = ImGui::Selectable("Average", m_abVol[2]);

	// Checks if selectable was pressed and is currently not highlighted
	if (bVolA && !m_abVol[2])
	{
		// Adjusts the volume to equal the average float
		m_pAudioManager->AdjustVolume(AVOLUME);

		// Sets the Average volume bool to be true
		m_abVol[2] = true;

		// Sets every other volume bool in array to be false
		for (int i = 0; i < 5; ++i)
		{
			if (i != 2)
			{
				m_abVol[i] = false;
			}
		}
	}

	// Adds a selectable for "High" volume and stores if it's pressed in local bool
	bool bVolH = ImGui::Selectable("High", m_abVol[3]);

	// Checks if selectable was pressed and is currently not highlighted
	if (bVolH && !m_abVol[3])
	{
		// Adjusts the volume to equal the high float
		m_pAudioManager->AdjustVolume(HVOLUME);

		// Sets the High volume bool to be true
		m_abVol[3] = true;

		// Sets every other volume bool in array to be false
		for (int i = 0; i < 5; ++i)
		{
			if (i != 3)
			{
				m_abVol[i] = false;
			}
		}
	}

	// Adds a selectable for "Very High" volume and stores if it's pressed in local bool
	bool bVolVH = ImGui::Selectable("Very High", m_abVol[4]);

	// Checks if selectable was pressed and is currently not highlighted
	if (bVolVH && !m_abVol[4])
	{
		// Adjusts the volume to equal the very high float
		m_pAudioManager->AdjustVolume(VHVOLUME);

		// Sets the Very High volume bool to be true
		m_abVol[4] = true;

		// Sets every other volume bool in array to be false
		for (int i = 0; i < 5; ++i)
		{
			if (i != 4)
			{
				m_abVol[i] = false;
			}
		}
	}

	// Ends detecting code for the volume list box
	ImGui::ListBoxFooter();
}
