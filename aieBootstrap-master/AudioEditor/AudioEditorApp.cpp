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

	m_2dRenderer = new aie::Renderer2D();

	window = new Window();

	audioManager = new AudioManager();

	// Boots up the FMOD system
	audioManager->SystemStart();

	// Loads a sound from the audio manager
	audioManager->LoadSound();

	return true;
}

void AudioEditorApp::shutdown() 
{
	delete m_2dRenderer;
	delete window;
}

void AudioEditorApp::update(float deltaTime) 
{
	// input example
	aie::Input* input = aie::Input::getInstance();

	// Opens up the ImGui window
	window->ConsoleWindow("New Project", true);

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

	// begin drawing sprites
	m_2dRenderer->begin();

	// done drawing sprites
	m_2dRenderer->end();
}
