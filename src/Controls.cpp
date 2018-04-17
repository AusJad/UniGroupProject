#include "Controls.h"

double Controls::prevx = -1;
double Controls::prevy = -1;

Controls::Controls() {
	curgroup = 0;
}

Controls::~Controls() {

}

void Controls::addControlGroup(unsigned controlgroup) {
	controls[controlgroup] = ResourceList();
}

void Controls::addInitalisedControlGroup(unsigned controlgroup, ResourceList & data) {
	controls[controlgroup] = data;
}

bool Controls::bindControls(unsigned group, ResourceList & toset) {
	if (controls.count(group) == 0) return false;

	controls.at(group) = toset;

	return true;
}

bool Controls::changeControlGroup(unsigned groupno, RenderModuleStubb* render, Controls* tochange) {
	if (tochange->controls.count(groupno) == 0) return false;
	unbindControls(tochange->curgroup, render, tochange);
	tochange->curgroup = groupno;
	bindControls(tochange->curgroup, render, tochange);
	return true;
}

void Controls::bindControls(unsigned groupno, RenderModuleStubb* render, Controls* tochange) {
	if (tochange->controls.at(groupno).hasResource("keyCallback")) glfwSetKeyCallback(render->getWindow(), keyCallback);
	if (tochange->controls.at(groupno).hasResource("mouseButtonCallback")) glfwSetMouseButtonCallback(render->getWindow(), mouseButtonCallback);
	if (tochange->controls.at(groupno).hasResource("mouseCallback")) glfwSetCursorPosCallback(render->getWindow(), mouseCallback);
}

void Controls::unbindControls(unsigned groupno, RenderModuleStubb* render, Controls* tochange) {
	if (tochange->controls.at(groupno).hasResource("keyCallback")) glfwSetKeyCallback(render->getWindow(), NULL);
	if (tochange->controls.at(groupno).hasResource("mouseButtonCallback")) glfwSetMouseButtonCallback(render->getWindow(), NULL);
	if (tochange->controls.at(groupno).hasResource("mouseCallback")) glfwSetCursorPosCallback(render->getWindow(), NULL);
}

void Controls::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	Controls* tmpc = Singleton<Controls>::getInstance();
	LUAScriptManager* tmpl = Singleton<LUAScriptManager>::getInstance();
	MessagingBus* tmpmb = Singleton<MessagingBus>::getInstance();

	std::string actions;
	std::string keys;
	keys = (char) key;

	if (key == 32) keys = "space";
	if (key == 257) keys = "enter";

	if (action == GLFW_REPEAT) {
		actions = "repeat";
	}
	else if (action == GLFW_PRESS) {
		actions = "press";
	}
	else {
		actions = "release";
	}

	tmpl->callFunction<SimpleString, SimpleString, MessagingBus>(tmpc->controls.at(tmpc->curgroup).getResource("keyCallback"), SimpleString(keys), SimpleString(actions), *tmpmb);	
}

void Controls::mouseCallback(GLFWwindow* window, double x, double y) {
	std::string sx = std::to_string(x);
	std::string sy = std::to_string(y);

	Controls* tmpc = Singleton<Controls>::getInstance();
	LUAScriptManager* tmpl = Singleton<LUAScriptManager>::getInstance();
	MessagingBus* tmpmb = Singleton<MessagingBus>::getInstance();

	if (prevx == -1) prevx = x;
	if (prevy == -1) prevy = y;

	tmpl->setGlobal<double>(prevx, "prevx");
	tmpl->setGlobal<double>(prevy, "prevy");

	tmpl->callFunction<SimpleString, SimpleString, MessagingBus>(tmpc->controls.at(tmpc->curgroup).getResource("mouseCallback"), SimpleString(sx), SimpleString(sy), *tmpmb);

	int w; int h;
	glfwGetWindowSize(window, &w, &h);

	prevx = (float)w / 2;
	prevy = (float)h / 2;

	glfwSetCursorPos(window, (double)w / 2, (double)h / 2);

	/*
	if (x > w * .55 || x < w * .45) {
		glfwSetCursorPos(window, (double) w/2, y);
		prevx = (double)w / 2;
	}
	if (y > h *.55 || y < h * .45) {
		glfwSetCursorPos(window, x, (double)h / 2);
		prevy = (double)h / 2;
	}*/
		
}

void Controls::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
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

	Controls* tmpc = Singleton<Controls>::getInstance();
	LUAScriptManager* tmpl = Singleton<LUAScriptManager>::getInstance();
	MessagingBus* tmpmb = Singleton<MessagingBus>::getInstance();

	tmpl->callFunction<SimpleString, SimpleString, MessagingBus>(tmpc->controls.at(tmpc->curgroup).getResource("mouseButtonCallback"), SimpleString(sbutton), SimpleString(saction), *tmpmb);
}