#pragma once

#include "ControlContext.h"
#include "CameraManager.h"

class FPSControlsContext : public ControlContext
{
public:
	void setActive() { glfwSetInputMode(RNDR->getWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN); prevx = -1; prevy = -1; }
	void setInActive() { glfwSetInputMode(RNDR->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL); CAM->getActiveCam()->stop();}

	keyCallback getKeyCallback() { return keys; };
	mouseMoveCallback getMouseMoveCallback() { return moveMouse; }
	mouseButtonCallback getMouseButtonCallback() { return NULL; }
	void setEngCallBack(engineCallback toset) { callback = toset; }
	void setMainMenuCallback(engineCallback toset) { mainmenucallback = toset; }

private:
	static void keys(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void moveMouse(GLFWwindow* window, double x, double y);

	static double prevx;
	static double prevy;
	static engineCallback callback;
	static engineCallback mainmenucallback;
};

