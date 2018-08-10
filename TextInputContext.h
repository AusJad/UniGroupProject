#pragma once

#include "ControlContext.h"
#include "WndComponent.h"

class TextInputContext : public ControlContext
{
public:
	void setActive(std::string* text, onClick oncomplete);
	void setActive() {};
	void setInActive();
	bool shouldRevert() { return done; }

	keyCallback getKeyCallback() { return keyInputCallback; };
	mouseMoveCallback getMouseMoveCallback() { return NULL; }
	mouseButtonCallback getMouseButtonCallback() { return NULL; }

private:
	static std::string* textin;
	static onClick textincomplete;
	static bool done;

	static void keyInputCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

