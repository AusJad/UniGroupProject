#include "SaveTool.h"

ButtonComponent * SaveTool::savelvl = NULL;
TextInputComponent * SaveTool::filename = NULL;
LabelComponent * SaveTool::instructions = NULL;

SaveTool::SaveTool(){
	savetool = NULL;
}


SaveTool::~SaveTool(){
	if(savetool !=NULL) delete savetool;
}

void SaveTool::toggle() {
	savetool->tglVis();
	if (!savetool->isVis()) {
		filename->setValue("");
	}
	else{
		savetool->centerInDisplay();
	}
}

void SaveTool::show() {
	savetool->show();
	savetool->centerInDisplay();
}

void SaveTool::hide() {
	savetool->hide();
	filename->setValue("");
}

void SaveTool::update(float time) {
	if (savetool->isVis()) savetool->update(time);
}

bool SaveTool::initalise() {
	savetool = WindowFactory::getWindow(WINDOW_MEDIUM_SQUARE, "GENERIC", vec2(0, 0), "Save Tool");
	if (savetool == NULL) return false;

	savetool->setCloseButtonCallBack(onWndClose);

	instructions = new LabelComponent();

	if (instructions == NULL) return false;

	instructions->setLabel("Type Name to Save Level As:");
	savetool->addComponent(instructions, 100, 7);

	filename = new TextInputComponent();
	if (filename == NULL) return false;
	savetool->addComponent(filename, 100, 10);

	savelvl = new ButtonComponent();
	if (savelvl == NULL) return false;

	savelvl->setTitle("Save Level");
	savelvl->setCallback(save);
	savetool->addComponent(savelvl, 100, 10);

	savetool->FitToContent();

	return true;
}

bool SaveTool::testClick(int x, int y) {
	if (savetool->isVis()) return savetool->testClick(x, y);
	else return false;
}

void SaveTool::render() {
	if (savetool->isVis()) savetool->render();
}

void SaveTool::save(int code) {
	if (filename->getValue().empty()) {
		ALERT->doNotify("Cannot Save: No File Name Given!", NULL);
	}
	else {
		if (EngineStateWriter::writeState("./Resources/Levels/" + filename->getValue() + ".lvl")) {
			ALERT->doNotify("Level Saved: " + filename->getValue() + ".lvl", NULL);
		}
		else {
			ALERT->doNotify("Save Failed: Unkown Error!", NULL);
		}
	}
}

void SaveTool::onWndClose(int code) {
	filename->setValue("");
}