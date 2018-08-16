#include "FPSControlsContext.h"

double FPSControlsContext::prevx = -1;
double FPSControlsContext::prevy = -1;
engineCallback FPSControlsContext::callback = NULL;

void FPSControlsContext::keys(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		if ((char)key == 'A') {
			CAM->getActiveCam()->mvLeft();
		}
		else
		if ((char)key == 'W') {
			CAM->getActiveCam()->moveFoward();
		}
		else
		if ((char)key == 'S') {
			CAM->getActiveCam()->moveBackward();
		}
		else
		if ((char)key == 'D') {
			CAM->getActiveCam()->mvRight();
		}
		else
		if ((char)key == 'Q') {
			CAM->getActiveCam()->moveUp();
		}
		else
		if ((char)key == 'E') {
			CAM->getActiveCam()->moveDown();
		}
		else
		if ((char)key == 'M') {
			if(callback != NULL) callback();
		}
	}
	else
	if (action == GLFW_RELEASE) {
		if ((char)key == 'A') {
			CAM->getActiveCam()->stpMvLeft();
		}
		else
		if ((char)key == 'W') {
			CAM->getActiveCam()->stpMvFoward();
		}
		else
		if ((char)key == 'S') {
			CAM->getActiveCam()->stpMvBackward();
		}
		else
		if ((char)key == 'D') {
			CAM->getActiveCam()->stpMvRight();
		}
		else
		if ((char)key == 'Q') {
			CAM->getActiveCam()->stpMvUp();
		}
		else
		if ((char)key == 'E') {
			CAM->getActiveCam()->stpMvDown();
		}
	}
}

void FPSControlsContext::moveMouse(GLFWwindow* window, double x, double y) {
	std::string sx = std::to_string(x);
	std::string sy = std::to_string(y);

	LUAScriptManager* tmpl = Singleton<LUAScriptManager>::getInstance();
	MessagingBus* tmpmb = Singleton<MessagingBus>::getInstance();

	if (prevx == -1) prevx = x;
	if (prevy == -1) prevy = y;

	CAM->getActiveCam()->look(-x + prevx, -y + prevy);

	int w; int h;
	glfwGetWindowSize(window, &w, &h);

	prevx = (float)w / 2;
	prevy = (float)h / 2;

	glfwSetCursorPos(window, (double)w / 2, (double)h / 2);

}