#pragma once

#include "movementInfo.h"
#include "ControlContext.h"

class WindowMoveContext : public ControlContext
{
public:
	void setActive(movementInfo * totrack);
	void setActive() {};
	void setInActive();
	bool shouldRevert();

	keyCallback getKeyCallback() { return NULL; };
	mouseMoveCallback getMouseMoveCallback() { return menuMoveMouse; }
	mouseButtonCallback getMouseButtonCallback() { return menuMoveMouseRelease; }

private:
	static void menuMoveMouse(GLFWwindow* window, double x, double y);
	static void menuMoveMouseRelease(GLFWwindow* window, int button, int action, int mods);

	static movementInfo * moveData;
};

