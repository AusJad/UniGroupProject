#include "GUI.h"

GUI::GUI()
{
	state = inactive;
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

	if (!mmenu.init(playGameCallback)) return false;

	return editor.initalise();
}

void GUI::setState(GUIState toset) {
	disableState(state);
	state = toset;
	enableState(state);
}

void GUI::enableState(GUIState toenable) {
	switch (state)
	{
		case inactive:
			return;
			break;
		case mainmenu:
			mmenu.show();
			CONT->switchContextGUIInteract();
			break;
		case editorst:
			editor.enable();
			CONT->switchContextGUIInteract();
			break;
	}
}

void GUI::disableState(GUIState todisable) {
	switch (state)
	{
		case inactive:
			return;
			break;
		case mainmenu:
			mmenu.hide();
			CONT->switchContextPlay();
			break;
		case editorst:
			editor.disable();
			CONT->switchContextPlay();
	}
}

void GUI::update(float time) {
	updateSelf();

	switch (state)
	{
		case inactive:
			return;
			break;
		case mainmenu:
			mmenu.update(time);
			break;
		case editorst:
			if (editor.isActive()) editor.update(time);
			break;
	}

	if (ALERT->isVis()) ALERT->update(time);
}

void GUI::updateSelf() {
	//hacky piece of code which allows editor to disable itself
	//without notifying gui (avoids resursive includes)
	//consider refactoring
	if (state == editorst && !editor.isActive()) {
		state = inactive;
		CONT->switchContextPlay();
	}

	if (GUIInteractContext::hasClick()) {
		vec2 click = GUIInteractContext::getClick().clicklocation;
		testClick((int)click.x(), (int)click.y());
	}
}

void GUI::render() {
	switch (state) {
		case inactive:
			renderInstructions();
			break;
		case mainmenu:
			if (mmenu.isActive()) mmenu.render();
			break;
		case editorst:
			if (editor.isActive()) editor.render();
			break;
	}

	if (ALERT->isVis()) ALERT->render();
}

void GUI::renderInstructions() {
	RNDR->RenderModeOrtho();
	instructions.render();
	RNDR->RenderModePerspective();
}

bool GUI::testClick(int x, int y) {
	if (ALERT->isVis()) return ALERT->testClick(x, y);

	switch (state) {
		case inactive:
			return false;
			break;
		case mainmenu:
			if(mmenu.isActive()) return mmenu.testClick(x, y);
			break;
		case editorst:
			if (editor.isActive()) return editor.testClick(x, y);
			break;
	}

	return false;
}

void GUI::playGameCallback(int code) {
	GI->setState(inactive);
}