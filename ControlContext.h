#pragma once

#include "RenderModuleStubb.h"

typedef void(*engineCallback)();
typedef void(*keyCallback)(GLFWwindow* window, int key, int scancode, int action, int mods);
typedef void(*mouseMoveCallback)(GLFWwindow* window, double x, double y);
typedef void(*mouseButtonCallback)(GLFWwindow* window, int button, int action, int mods);

class ControlContext
{
public:
	virtual void setActive() = 0;
	virtual void setInActive() = 0;
	virtual keyCallback getKeyCallback() = 0;
	virtual mouseMoveCallback getMouseMoveCallback() = 0;
	virtual mouseButtonCallback getMouseButtonCallback() = 0;
	virtual bool shouldRevert() { return false; }
};

