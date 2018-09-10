#pragma once

#include "ControlContext.h"
#include "WndComponent.h"

/**
* @class TextInputContext
*
* @author Morgan Smolder
*/
class TextInputContext : public ControlContext
{
public:
	void setActive(std::string* text, onClick oncomplete, bool * active);
	void setActive() {};
	void setInActive();
	bool shouldRevert() { return done; }

	keyCallback getKeyCallback() { return keyInputCallback; };
	mouseMoveCallback getMouseMoveCallback() { return NULL; }
	mouseButtonCallback getMouseButtonCallback() { return buttonCallback; }

private:
	static std::string* textin;
	static onClick textincomplete;
	static bool* inputactive;
	static bool done;

	static void keyInputCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void buttonCallback(GLFWwindow* window, int button, int action, int mods);
};

