#pragma once
#include "Application.h"
#include "Renderer2D.h"
#include "Imgui.h"

class AudioEditorApp : public aie::Application 
{
public:
	AudioEditorApp();
	virtual ~AudioEditorApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	void ConsoleWindow(char* filename, bool open);

protected:
	aie::Renderer2D* m_2dRenderer;
	ImVec2 boxSize;
};