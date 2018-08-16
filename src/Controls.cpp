#include "Controls.h"

Controls::Controls() {
	activecontext = NULL;
	prevcontext = NULL;
	lastLUAContext = NULL;
}

Controls::~Controls() {

}

void Controls::addInitalisedControlGroup(unsigned controlgroup, ResourceList & data) {
	LuaControlContext * tmp = new LuaControlContext;
	tmp->bindControls(data);
	controls[controlgroup] = tmp;
}

void Controls::switchContextConsole(bool active, RenderModuleStubb* render, Controls* tochange) {
	if (active) {
		unbindControls(CONT->activecontext);
		CONT->prevcontext = CONT->activecontext;
		glfwSetKeyCallback(render->getWindow(), ConsoleCallback);
	}
	else {
		glfwSetKeyCallback(render->getWindow(), NULL);
		bindControls(CONT->prevcontext);
		CONT->activecontext = CONT->prevcontext;
	}
}

void Controls::restorePreviousControlContext() {
	if (CONT->prevcontext != NULL) {
		unbindControls(CONT->activecontext);
		CONT->activecontext->setInActive();

		bindControls(CONT->prevcontext);
		CONT->prevcontext->setActive();

		ControlContext * tmp = CONT->activecontext;

		CONT->activecontext = CONT->prevcontext;
		CONT->prevcontext = tmp;
	}
}

bool Controls::bindControls(unsigned group, ResourceList & toset) {
	LuaControlContext * tmp = new LuaControlContext;
	tmp->bindControls(toset);
	controls[group] = tmp;

	return true;
}

void Controls::update() {
	if (activecontext != NULL) {
		if (activecontext->shouldRevert()) restorePreviousControlContext();
	}
}

bool Controls::changeControlGroup(unsigned groupno, RenderModuleStubb* render, Controls* tochange) {
	if (tochange->controls.count(groupno) == 0) return false;
	
	if (CONT->activecontext != NULL) {
		unbindControls(CONT->activecontext);
		tochange->controls.at(groupno)->setInActive();
		CONT->prevcontext = CONT->activecontext;
	}

	CONT->activecontext = CONT->controls.at(groupno);
	bindControls(CONT->activecontext);
	CONT->activecontext->setActive();

	return true;
}

void Controls::bindControls(ControlContext* tobind) {
	if (tobind->getKeyCallback() != NULL) glfwSetKeyCallback(RNDR->getWindow(), tobind->getKeyCallback());
	if (tobind->getMouseButtonCallback() != NULL) glfwSetMouseButtonCallback(RNDR->getWindow(), tobind->getMouseButtonCallback());
	if (tobind->getMouseMoveCallback() != NULL) glfwSetCursorPosCallback(RNDR->getWindow(), tobind->getMouseMoveCallback());
	if (tobind->getScrollCallback() != NULL) glfwSetScrollCallback(RNDR->getWindow(), tobind->getScrollCallback());
}

void Controls::unbindControls(ControlContext* tobind) {
	if (tobind->getKeyCallback() != NULL) glfwSetKeyCallback(RNDR->getWindow(), NULL);
	if (tobind->getMouseButtonCallback() != NULL) glfwSetMouseButtonCallback(RNDR->getWindow(), NULL);
	if (tobind->getMouseMoveCallback() != NULL) glfwSetCursorPosCallback(RNDR->getWindow(), NULL);
	if (tobind->getScrollCallback() != NULL) glfwSetScrollCallback(RNDR->getWindow(), NULL);
}

void Controls::switchContextMenuMove(movementInfo * tomove) {
	if (CONT->activecontext != NULL) {
		unbindControls(CONT->activecontext);
		CONT->prevcontext = CONT->activecontext;
	}

	bindControls(&CONT->WMC);
	CONT->WMC.setActive(tomove);
	CONT->activecontext = &CONT->WMC;
}

void Controls::switchContextTextInput(std::string * toedit, onClick whenComplete, bool * active) {
	if (CONT->activecontext != NULL) {
		unbindControls(CONT->activecontext);
		CONT->prevcontext = CONT->activecontext;
	}

	bindControls(&CONT->TIC);
	CONT->TIC.setActive(toedit, whenComplete, active);
	CONT->activecontext = &CONT->TIC;
}

void Controls::switchContextGUIInteract() {
	if (CONT->activecontext != NULL) {
		unbindControls(CONT->activecontext);
		CONT->prevcontext = CONT->activecontext;
		//todo - revise after lua removed from engine
		CONT->lastLUAContext = CONT->activecontext;
	}

	bindControls(&CONT->GIC);
	CONT->GIC.setActive();
	CONT->activecontext = &CONT->GIC;
}

void Controls::switchContextPlay() {
	if (CONT->activecontext != NULL) {
		unbindControls(CONT->activecontext);
		CONT->prevcontext = CONT->activecontext;
	}

	bindControls(&CONT->FPS);
	CONT->FPS.setActive();
	CONT->activecontext = &CONT->FPS;
}

void Controls::switchContextItemPlace(placementCompleteCallback oncomplete, itemScroll scrollcb) {
	if (CONT->activecontext != NULL) {
		unbindControls(CONT->activecontext);
		CONT->prevcontext = CONT->activecontext;
	}

	bindControls(&CONT->IPC);
	CONT->IPC.setActive();
	CONT->IPC.setPlacementCallback(oncomplete);
	CONT->IPC.setScrollCB(scrollcb);
	CONT->activecontext = &CONT->IPC;
}

void Controls::ConsoleCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	int flags;
	std::string keys;
	keys = (char)key;

	if (key == 32) keys = "space";
	if (key == 257) keys = "enter";
	if (key == 259) keys = "backspace";
	if (key == 265) keys = "up";
	if (key == 264) keys = "down";
	if (key == 340) keys = "shift";
	if (key == 263) keys = "left";
	if (key == 262) keys = "right";

	if (action == GLFW_REPEAT) {
		flags = REPEAT;
	}
	else if (action == GLFW_PRESS) {
		flags = PRESS;
	}
	else {
		flags = RELEASE;
	}

	Message tmp(C_INPUT);

	tmp.setsData(keys);
	tmp.setIData(flags);

	MSGBS->postIMessage(tmp, CONSOLE_ID);
}

void Controls::registerCallbacks(engineCallback toset) {
	FPS.setEngCallBack(toset);
}

void Controls::registerGUICallback(engineCallback toset) {
	GIC.setCallback(toset);
}