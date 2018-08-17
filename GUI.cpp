#include "GUI.h"

GUI::GUI()
{
	pasteditorcontext = false;
}


GUI::~GUI()
{
}

bool GUI::initalise() {
	instructions.setLabel("Editor: Press M");
	instructions.setPadding(5);
	instructions.setWidth(250);
	instructions.setHeight(25);
	instructions.setTex(WND_HEADER_BG);

	if (!ALERT->init()) return false;

	return editor.initalise();
}

void GUI::disableEditor() {
	editor.disable();
	pasteditorcontext = false;
	CONT->switchContextPlay();
}

void GUI::enableEditor() {
	editor.enable();
	pasteditorcontext = true;
}

void GUI::update(float time) {
	if (pasteditorcontext == true && !editor.isActive()) {
		pasteditorcontext = false;
		CONT->switchContextPlay();
	}

	if (GUIInteractContext::hasClick()) {
		vec2 click = GUIInteractContext::getClick().clicklocation;
		testClick((int) click.x(), (int) click.y());
	}

	if (editor.isActive()) editor.update(time);

	if (ALERT->isVis()) ALERT->update(time);
}

void GUI::render() {
	if (editor.isActive()) editor.render();
	else {
		RNDR->RenderModeOrtho();
		instructions.render();
		RNDR->RenderModePerspective();
	}	

	if (ALERT->isVis()) ALERT->render();
}

bool GUI::testClick(int x, int y) {
	if (ALERT->isVis()) return ALERT->testClick(x, y);
	if (editor.isActive()) return editor.testClick(x, y);

	return false;
}