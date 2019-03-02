// Include(s)
#include "AudioEditorApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Imgui.h"

//--------------------------------------------------------------------------------
// Default Constructor (Not Being Used).
//--------------------------------------------------------------------------------
AudioEditorApp::AudioEditorApp() {}

//--------------------------------------------------------------------------------
// Default Constructor (Not Being Used).
//--------------------------------------------------------------------------------
AudioEditorApp::~AudioEditorApp() {}

//--------------------------------------------------------------------------------
// Acts as the AudioEditorApp's constructor by initialising values.
//
// Return:
//		Returns a bool indicating if everything has been created properly.
//--------------------------------------------------------------------------------
bool AudioEditorApp::startup()
{
	setBackgroundColour(0.1f, 0.1f, 0.1f, 1.0f);

	m_pWindow = new Window();

	return true;
}

//--------------------------------------------------------------------------------
// Acts as the AudioEditorApp's Destructor by deleting value's from the heap.
//--------------------------------------------------------------------------------
void AudioEditorApp::shutdown()
{
	delete m_pWindow;
}

//--------------------------------------------------------------------------------
// Updates the application every frame it runs for.
//
// Param:
//		Returns a bool indicating if everything has been created properly.
//--------------------------------------------------------------------------------
void AudioEditorApp::update(float fDeltaTime)
{
	// input example
	aie::Input* input = aie::Input::getInstance();

	// Opens up the ImGui window
	m_pWindow->UpdateWindow("New Project", true);

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
	{
		quit();
	}
}

//--------------------------------------------------------------------------------
// Draws the application every frame the class runs for.
//--------------------------------------------------------------------------------
void AudioEditorApp::draw()
{
	// wipe the screen to the background colour
	clearScreen();
}
