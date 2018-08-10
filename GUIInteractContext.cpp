#include "GUIInteractContext.h"

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
	mousePos = vec2(x, y);
}

void GUIInteractContext::mouseClickCallback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		clicks.hasClick = true;
		clicks.clicklocation = mousePos;
	}
}