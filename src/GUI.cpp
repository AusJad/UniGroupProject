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
	
	initializeNPCWindow();

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
		RNDR->RenderModeOrtho();
		if (npc1 != NULL) {
			if (npc1->getModel() == NULL) { //std::cout << "model is NULL" << std::endl; }
			if (npc1->getModel() != NULL) {
				npcemos1x.setLabel("E/G: " + std::to_string(npc1->getemotion().x()));
				npcemos1y.setLabel("A/L: " + std::to_string(npc1->getemotion().y()));
				npcemos1z.setLabel("V/A: " + std::to_string(npc1->getemotion().z()));
				npcemos1w.setLabel("R/T: " + std::to_string(npc1->getemotion().w()));
				npcemos1.setPos(vec2(0, 25));
				npcemos1.render();
				npcemos1x.setPos(vec2(5, 60));
				npcemos1x.render();
				npcemos1y.setPos(vec2(5, 90));
				npcemos1y.render();
				npcemos1z.setPos(vec2(0, 120));
				npcemos1z.render();
				npcemos1w.setPos(vec2(0, 150));
				npcemos1w.render();
			}
		}
		if (npc2 != NULL) {
			if (npc2->getModel() != NULL) {
			npcemos2x.setLabel("E/G: " + std::to_string(npc2->getemotion().x()));
			npcemos2y.setLabel("A/L: " + std::to_string(npc2->getemotion().y()));
			npcemos2z.setLabel("V/A: " + std::to_string(npc2->getemotion().z()));
			npcemos2w.setLabel("R/T: " + std::to_string(npc2->getemotion().w()));
			npcemos2.setPos(vec2(0, 225));
			npcemos2.render();
			npcemos2x.setPos(vec2(5, 260));
			npcemos2x.render();
			npcemos2y.setPos(vec2(5, 290));
			npcemos2y.render();
			npcemos2z.setPos(vec2(0, 320));
			npcemos2z.render();
			npcemos2w.setPos(vec2(0, 350));
			npcemos2w.render();
			}
		}
		if (npc3 != NULL) {
			if (npc3->getModel() != NULL) {
				npcemos3x.setLabel("E/G: " + std::to_string(npc3->getemotion().x()));
				npcemos3y.setLabel("A/L: " + std::to_string(npc3->getemotion().y()));
				npcemos3z.setLabel("V/A: " + std::to_string(npc3->getemotion().z()));
				npcemos3w.setLabel("R/T: " + std::to_string(npc3->getemotion().w()));
				npcemos3.setPos(vec2(0, 425));
				npcemos3.render();
				npcemos3x.setPos(vec2(5, 460));
				npcemos3x.render();
				npcemos3y.setPos(vec2(5, 490));
				npcemos3y.render();
				npcemos3z.setPos(vec2(0, 520));
				npcemos3z.render();
				npcemos3w.setPos(vec2(0, 550));
				npcemos3w.render();
			}
		}
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

void GUI::setNpc(NPC *npcin) {
	if (npc1 == NULL) {
		npc1 = npcin;
		std::cout << "NPC1 Has entered the building" << std::endl;
		npcCount++;
	}
	else if (npc2 == NULL){
		npc2 = npcin;
		std::cout << "NPC2 Has entered the building" << std::endl;
		npcCount++;
	}
	else if (npc3 == NULL) {
		npc3 = npcin;
		std::cout << "NPC3 Has entered the building" << std::endl;
		npcCount++;
	}
	std::cout << "NPC Count is: " << npcCount << std::endl;
}

void GUI::initializeNPCWindow() {
	npcemos1.setLabel("NPC1 emotions:");
	npcemos1.setPadding(3);
	npcemos1.setWidth(200);
	npcemos1.setHeight(200);
	npcemos1.setTex(WND_HEADER_BG);
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
	npcemos2.setLabel("NPC2 emotions:");
	npcemos2.setPadding(3);
	npcemos2.setWidth(200);
	npcemos2.setHeight(200);
	npcemos2.setTex(WND_HEADER_BG);
	npcemos2x.setPadding(3);
	npcemos2x.setWidth(190);
	npcemos2x.setHeight(45);
	npcemos2y.setPadding(3);
	npcemos2y.setWidth(190);
	npcemos2y.setHeight(45);
	npcemos2z.setPadding(3);
	npcemos2z.setWidth(190);
	npcemos2z.setHeight(45);
	npcemos2w.setPadding(3);
	npcemos2w.setWidth(190);
	npcemos2w.setHeight(45);
	npcemos3.setLabel("NPC3 emotions:");
	npcemos3.setPadding(3);
	npcemos3.setWidth(200);
	npcemos3.setHeight(200);
	npcemos3.setTex(WND_HEADER_BG);
	npcemos3x.setPadding(3);
	npcemos3x.setWidth(190);
	npcemos3x.setHeight(45);
	npcemos3y.setPadding(3);
	npcemos3y.setWidth(190);
	npcemos3y.setHeight(45);
	npcemos3z.setPadding(3);
	npcemos3z.setWidth(190);
	npcemos3z.setHeight(45);
	npcemos3w.setPadding(3);
	npcemos3w.setWidth(190);
	npcemos3w.setHeight(45);
}

void GUI::deRegisterNPC(NPC *npcin) {
	std::cout << "reached de-registration" << std::endl;
	if (npcin == npc1) { 
		npc1 = NULL; 
		if (npc1 == NULL) {
			std::cout << "npc1 de-registered from GUI" << std::endl;
			npcCount--;
		}
	}
	else if (npcin == npc2) { 
		npc2 = NULL;
		if (npc2 == NULL) {
			std::cout << "npc2 de-registered from GUI" << std::endl;
			npcCount--;
		}
	}
	else if (npcin == npc3) { 
		npc3 = NULL; 
		if (npc3 == NULL) { 
			std::cout << "npc3 de-registered from GUI" << std::endl; 
			npcCount--;
		}
	}
}
