#include "AudioEditorApp.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

int main() {
	
	// allocation
	auto app = new AudioEditorApp();

	// initialise and loop
	app->run("Audio Editor", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}