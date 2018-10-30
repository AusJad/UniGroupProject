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
	instructions.setPadding(3);
	instructions.setWidth(250);
	instructions.setHeight(25);
	instructions.setTex(WND_HEADER_BG);
	npcemos1.setLabel("NPC1 emotions:");
	npcemos1.setPadding(3);
	npcemos1.setWidth(200);
	npcemos1.setHeight(200);
	npcemos1.setTex(WND_HEADER_BG);
	npcemos2.setLabel("NPC2 emotions:");
	npcemos2.setPadding(3);
	npcemos2.setWidth(200);
	npcemos2.setHeight(200);
	npcemos2.setTex(WND_HEADER_BG);
	npcemos3.setLabel("NPC3 emotions:");
	npcemos3.setPadding(3);
	npcemos3.setWidth(200);
	npcemos3.setHeight(200);
	npcemos3.setTex(WND_HEADER_BG);
	
	npcemos1x.setPadding(3);
	npcemos1x.setWidth(190);
	npcemos1x.setHeight(45);
	
	npcemos1y.setPadding(3);
	npcemos1y.setWidth(190);
	npcemos1y.setHeight(45);
	
	npcemos1z.setPadding(3);
	npcemos1z.setWidth(190);
	npcemos1z.setHeight(45);
	
	npcemos1w.setPadding(3);
	npcemos1w.setWidth(190);
	npcemos1w.setHeight(45);

	npcemos3.setTex(WND_HEADER_BG);

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
			AE->unpauseChannels();
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
			AE->pauseActiveChannels();
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
		case inactive: {
				renderInstructions();
				renderNpcEmo();
			}
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
	if (canEdit()) {
		RNDR->RenderModeOrtho();
		instructions.render();
		RNDR->RenderModePerspective();
	}
}

void GUI::renderNpcEmo() {
	if (canEdit()) {
		vec4 npcemo1 = vec4(0, 1, 2, 3);
		std::string npcemo1x_char = std::to_string(npcemo1.x());
		std::string npcemo1y_char = std::to_string(npcemo1.y());
		std::string npcemo1z_char = std::to_string(npcemo1.z());
		std::string npcemo1w_char = std::to_string(npcemo1.w());


		npcemos1x.setLabel("x: " + std::to_string(npcemo1.x()));
		npcemos1y.setLabel("y: " + npcemo1y_char);
		npcemos1z.setLabel("z: " + npcemo1z_char);
		npcemos1w.setLabel("w: " + npcemo1w_char);

		RNDR->RenderModeOrtho();
		npcemos1.setPos(vec2(0, 25));
		npcemos1.render();
		npcemos2.setPos(vec2(0, 225));
		npcemos2.render();
		npcemos3.setPos(vec2(0, 425));
		npcemos3.render();
		npcemos1x.setPos(vec2(5, 60));
		npcemos1x.render();
		npcemos1y.setPos(vec2(5, 90));
		npcemos1y.render();
		npcemos1z.setPos(vec2(0, 120));
		npcemos1z.render();
		npcemos1w.setPos(vec2(0, 150));
		npcemos1w.render();


		RNDR->RenderModePerspective();
	}
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