#include "AudioEditorApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Imgui.h"

AudioEditorApp::AudioEditorApp() {

}

AudioEditorApp::~AudioEditorApp() {

}

bool AudioEditorApp::startup() 
{
	setBackgroundColour(0.1f, 0.1f, 0.1f, 1.0f);

	firstWindow = new Window();

	return true;
}

void AudioEditorApp::shutdown() 
{
	delete firstWindow;
}

void AudioEditorApp::update(float deltaTime) 
{
	// input example
	aie::Input* input = aie::Input::getInstance();

	// Opens up the ImGui window
	firstWindow->UpdateWindow("New Project", true);

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
	{
		quit();
	}
}

void AudioEditorApp::draw() 
{
	// wipe the screen to the background colour
	clearScreen();
}
