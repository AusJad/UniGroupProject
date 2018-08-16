#pragma once
#include "ControlContext.h"
#include "CameraManager.h"

typedef void(*placementCompleteCallback)();
typedef void(*itemScroll)(float offsety);

class ItemPlaceContext: public ControlContext
{
public:
	void setActive() { glfwSetInputMode(RNDR->getWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN); prevx = -1; prevy = -1; }
	void setInActive() { glfwSetInputMode(RNDR->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL); CAM->getActiveCam()->stop(); }

	keyCallback getKeyCallback() { return keys; };
	mouseMoveCallback getMouseMoveCallback() { return moveMouse; }
	mouseButtonCallback getMouseButtonCallback() { return mouseClick; }
	scrollCallback getScrollCallback() { return mouseScroll; }
	void setPlacementCallback(placementCompleteCallback toset) { ondone = toset; };
	void setScrollCB(itemScroll toset) { scrlcb = toset; };

private:
	static void keys(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void moveMouse(GLFWwindow* window, double x, double y);
	static void mouseScroll(GLFWwindow* window, double xoffset, double yoffset);
	static void mouseClick(GLFWwindow* window, int button, int action, int mods);

	static double prevx;
	static double prevy;
	static placementCompleteCallback ondone;
	static itemScroll scrlcb;
};

