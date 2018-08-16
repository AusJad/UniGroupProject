#include "GUIInteractContext.h"

engineCallback GUIInteractContext::callback = NULL;
clickData GUIInteractContext::clicks;
vec2  GUIInteractContext::mousePos;

bool GUIInteractContext::hasClick() {
	return clicks.hasClick; 
}

clickData & GUIInteractContext::getClick() {
	clicks.hasClick = false; 
	return clicks; 
}

void GUIInteractContext::menuMoveMouse(GLFWwindow* window, double x, double y) {
	mousePos = vec2((float) x, (float) y);
}

void GUIInteractContext::mouseClickCallback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		clicks.hasClick = true;

		double x, y;
		glfwGetCursorPos(window, &x, &y);
		clicks.clicklocation = vec2((float)x, (float)y);
	}
}

void GUIInteractContext::keys(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS && (char)key == 'M') {
		if (callback != NULL) callback();
	}
}