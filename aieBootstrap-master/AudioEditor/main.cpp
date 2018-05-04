#include "AudioEditorApp.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <crtdbg.h>

int main() 
{
	// allocation
	auto app = new AudioEditorApp();

	// initialise and loop
	app->run("Audio Editor", 1280, 720, false);

	// Checks for memory leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// deallocation
	delete app;

	return 0;
}