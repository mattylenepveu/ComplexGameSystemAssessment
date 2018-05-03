#pragma once

// Include(s)
#include "Application.h"
#include "Renderer2D.h"
#include "Window.h"

//--------------------------------------------------------------------------------
// AudioEditorApp class runs the application for the Editor to run in.
//
// Inherit:
//		Class inherits from the Application class in the aieBootstrap.
//--------------------------------------------------------------------------------
class AudioEditorApp : public aie::Application 
{
public:
	//--------------------------------------------------------------------------------
	// Default Constructor (Not Being Used).
	//--------------------------------------------------------------------------------
	AudioEditorApp();

	//--------------------------------------------------------------------------------
	// Default Constructor (Not Being Used).
	//--------------------------------------------------------------------------------
	virtual ~AudioEditorApp();

	//--------------------------------------------------------------------------------
	// Acts as the AudioEditorApp's constructor by initialising values.
	//
	// Return:
	//		Returns a bool indicating if everything has been created properly.
	//--------------------------------------------------------------------------------
	virtual bool startup();

	//--------------------------------------------------------------------------------
	// Acts as the AudioEditorApp's Destructor by deleting value's from the heap.
	//--------------------------------------------------------------------------------
	virtual void shutdown();

	//--------------------------------------------------------------------------------
	// Updates the application every frame it runs for.
	//
	// Param:
	//		Returns a bool indicating if everything has been created properly.
	//--------------------------------------------------------------------------------
	virtual void update(float fDeltaTime);

	//--------------------------------------------------------------------------------
	// Draws the application every frame the class runs for.
	//--------------------------------------------------------------------------------
	virtual void draw();

protected:
	// Window pointer allows AudioEditorApp to access functions in the Window class
	Window* m_pWindow;
};