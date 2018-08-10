#include "LuaControlContext.h"

ResourceList LuaControlContext::activecontext;
double LuaControlContext::prevx = -1;
double LuaControlContext::prevy = -1;

ResourceList & LuaControlContext::getActiveContext() {
	return activecontext;
}

void LuaControlContext::setActive() {
	glfwSetInputMode(RNDR->getWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	LuaControlContext::activecontext = boundcontrols;
}

void LuaControlContext::setInActive() {
	LuaControlContext::activecontext = ResourceList();
}

keyCallback LuaControlContext::getKeyCallback() {
	if (boundcontrols.hasResource("keyCallback")) return keyCallback;

	return NULL;
};

mouseMoveCallback LuaControlContext::getMouseMoveCallback() {
	if (boundcontrols.hasResource("mouseCallback")) return mouseCallback;

	return NULL;
}

mouseButtonCallback LuaControlContext::getMouseButtonCallback() {
	if (boundcontrols.hasResource("mouseButtonCallback")) return mouseButtonCallback;

	return NULL;
}

void LuaControlContext::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	LUAScriptManager* tmpl = Singleton<LUAScriptManager>::getInstance();
	MessagingBus* tmpmb = Singleton<MessagingBus>::getInstance();

	std::string actions;
	std::string keys;
	keys = (char)key;

	if (key == 32) keys = "space";
	if (key == 257) keys = "enter";
	if (key == 259) keys = "backspace";
	if (key == 265) keys = "up";
	if (key == 264) keys = "down";
	if (key == 263) keys = "left";
	if (key == 262) keys = "right";
	if (key == GLFW_KEY_ESCAPE) keys = "esc";

	if (action == GLFW_REPEAT) {
		actions = "repeat";
	}
	else if (action == GLFW_PRESS) {
		actions = "press";
	}
	else {
		actions = "release";
	}

	tmpl->callFunction<SimpleString, SimpleString, MessagingBus>(LuaControlContext::getActiveContext().getResource("keyCallback"), SimpleString(keys), SimpleString(actions), *tmpmb);
}


void LuaControlContext::mouseCallback(GLFWwindow* window, double x, double y) {
	std::string sx = std::to_string(x);
	std::string sy = std::to_string(y);

	LUAScriptManager* tmpl = Singleton<LUAScriptManager>::getInstance();
	MessagingBus* tmpmb = Singleton<MessagingBus>::getInstance();

	if (prevx == -1) prevx = x;
	if (prevy == -1) prevy = y;

	tmpl->setGlobal<double>(prevx, "prevx");
	tmpl->setGlobal<double>(prevy, "prevy");

	tmpl->callFunction<SimpleString, SimpleString, MessagingBus>(LuaControlContext::getActiveContext().getResource("mouseCallback"), SimpleString(sx), SimpleString(sy), *tmpmb);

	int w; int h;
	glfwGetWindowSize(window, &w, &h);

	prevx = (float)w / 2;
	prevy = (float)h / 2;

	glfwSetCursorPos(window, (double)w / 2, (double)h / 2);
}

void LuaControlContext::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	std::string sbutton;
	std::string saction;

	if (button == GLFW_MOUSE_BUTTON_RIGHT) {
		sbutton = "right";
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT) {
		sbutton = "left";
	}

	if (action == GLFW_PRESS) {
		saction = "press";
	}
	else {
		saction = "release";
	}

	LUAScriptManager* tmpl = Singleton<LUAScriptManager>::getInstance();
	MessagingBus* tmpmb = Singleton<MessagingBus>::getInstance();

	tmpl->callFunction<SimpleString, SimpleString, MessagingBus>(LuaControlContext::getActiveContext().getResource("mouseButtonCallback"), SimpleString(sbutton), SimpleString(saction), *tmpmb);
}