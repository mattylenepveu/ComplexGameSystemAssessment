// Include(s)
#include "AudioEditorApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Imgui.h"

//--------------------------------------------------------------------------------
// Default Constructor (Not being used but required from base class).
//--------------------------------------------------------------------------------
AudioEditorApp::AudioEditorApp() {}

//--------------------------------------------------------------------------------
// Acts as the AudioEditorApp's constructor by initialising values.
//
// Return:
//		Returns a bool indicating if everything has been created properly.
//--------------------------------------------------------------------------------
bool AudioEditorApp::startup()
{
	// Sets the background colour of the application to be a very dark grey
	setBackgroundColour(0.1f, 0.1f, 0.1f, 1.0f);

	// Creates a "new" Window for the Application class to use
	m_pWindow = new Window();

	// Returns true once the application has started up
	return true;
}

//--------------------------------------------------------------------------------
// Acts as the AudioEditorApp's Destructor by deleting value's from the heap.
//--------------------------------------------------------------------------------
void AudioEditorApp::shutdown()
{
	// Deletes the Window pointer from the classes' heap
	delete m_pWindow;
}

//--------------------------------------------------------------------------------
// Updates the application every frame it runs for.
//
// Param (Not being used but required from base class):
//		fDeltaTime: A float representing real time for use in physics equations.
//--------------------------------------------------------------------------------
void AudioEditorApp::update(float fDeltaTime)
{
	// Opens up the ImGui window with the title "Audio Editor"
	m_pWindow->UpdateWindow("New Project");
}

//--------------------------------------------------------------------------------
// Draws the application every frame the class runs for.
//--------------------------------------------------------------------------------
void AudioEditorApp::draw()
{
	// Wipes the screen to the background colour
	clearScreen();
}
