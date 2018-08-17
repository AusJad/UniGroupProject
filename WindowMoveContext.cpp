#include "WindowMoveContext.h"

movementInfo * WindowMoveContext::moveData = NULL;

void WindowMoveContext::setActive(movementInfo * totrack) {
	moveData = totrack;
}

bool WindowMoveContext::shouldRevert() {
	if (moveData == NULL) return true;
	else return !moveData->moving;
}

void WindowMoveContext::setInActive() {
	moveData = NULL;
}

void WindowMoveContext::menuMoveMouse(GLFWwindow* window, double x, double y) {
	if (moveData != NULL) {
		moveData->offset = vec2((float)(x) - moveData->inital.x(), (float)(y) - moveData->inital.y());
		moveData->inital = moveData->inital + moveData->offset;
	}
}

void WindowMoveContext::menuMoveMouseRelease(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		moveData->moving = false;
	}
}

