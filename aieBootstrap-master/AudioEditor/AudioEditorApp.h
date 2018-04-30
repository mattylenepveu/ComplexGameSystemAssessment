#pragma once
#include "Application.h"
#include "Renderer2D.h"
#include "Window.h"
//#include "AudioManager.h"

class AudioEditorApp : public aie::Application 
{
public:
	AudioEditorApp();
	virtual ~AudioEditorApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:
	aie::Renderer2D* m_2dRenderer;

	Window* window;
};