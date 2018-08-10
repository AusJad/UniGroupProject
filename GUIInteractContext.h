#pragma once

#include "ControlContext.h"

struct clickData {
	bool hasClick;
	vec2 clicklocation;
	clickData() { hasClick = false; }
};

class GUIInteractContext : public ControlContext
{
public:
	static bool hasClick();
	static clickData & getClick();

	void setActive() { glfwSetInputMode(RNDR->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL); }
	void setInActive() { glfwSetInputMode(RNDR->getWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN); }

	keyCallback getKeyCallback() { return NULL; };
	mouseMoveCallback getMouseMoveCallback() { return menuMoveMouse; }
	mouseButtonCallback getMouseButtonCallback() { return mouseClickCallback; }

private:
	static clickData clicks;
	static vec2 mousePos;

	static void menuMoveMouse(GLFWwindow* window, double x, double y);
	static void mouseClickCallback(GLFWwindow* window, int button, int action, int mods);
};

//to do - reset click on deactivation