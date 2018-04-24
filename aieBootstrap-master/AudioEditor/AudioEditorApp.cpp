#include "AudioEditorApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Imgui.h"

static const int MAX_DROPDOWN_ITEMS = 5;

AudioEditorApp::AudioEditorApp() {

}

AudioEditorApp::~AudioEditorApp() {

}

bool AudioEditorApp::startup() 
{
	setBackgroundColour(0.1f, 0.1f, 0.1f, 1.0f);

	m_2dRenderer = new aie::Renderer2D();

	boxSize = ImVec2(90, 90);
	

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	//m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	return true;
}

void AudioEditorApp::shutdown() 
{
	//delete m_font;
	delete m_2dRenderer;
}

void AudioEditorApp::update(float deltaTime) 
{
	// input example
	aie::Input* input = aie::Input::getInstance();

	ConsoleWindow("New Project", true);

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

void AudioEditorApp::ConsoleWindow(char* filename, bool open)
{
	ImGui::SetNextWindowSize(ImVec2(900.0f, 500.0f));
	ImGui::Begin(filename, &open, ImGuiWindowFlags_NoResize);

	ImGui::BeginMenuBar();

	if (ImGui::BeginMenu("File"))
	{
		ImGui::MenuItem("New Project");		
		
		if (ImGui::MenuItem("Load Audio"))
		{
			ImGui::BeginPopup(filename);
			ImGui::End();
		}

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
	ImGui::Button("PAUSE", ImVec2(50, 20));

	ImGui::SameLine();
	ImGui::Indent(100.0f);
	ImGui::Button("PLAY", ImVec2(50, 20));

	ImGui::SameLine();
	ImGui::Indent(100.0f);
	ImGui::Button("STOP", ImVec2(50, 20));

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
