#include "EditorCameraTool.h"

ButtonComponent * EditorCameraTool::colltoggle = NULL;

EditorCameraTool::EditorCameraTool(){
	cameratool = NULL;
}


EditorCameraTool::~EditorCameraTool()
{
	if (cameratool != NULL) delete cameratool;
}

void EditorCameraTool::toggle() {
	cameratool->tglVis();
	if (cameratool->isVis()) cameratool->centerInDisplay();
}

void EditorCameraTool::show() {
	cameratool->show();
}

void EditorCameraTool::hide() {
	cameratool->hide();
}

void EditorCameraTool::update(float time) {
	if (cameratool->isVis()) cameratool->update(time);
}

bool EditorCameraTool::initalise() {
	cameratool = WindowFactory::getWindow(WINDOW_MEDIUM_WIDE, "GENERIC", vec2(0,0), "Camera Tool");
	if (cameratool == NULL) return false;


	colltoggle = new ButtonComponent();
	if (colltoggle == NULL) return false;

	colltoggle->setTitle("Free Cam Is: Off");
	colltoggle->setCallback(cameracollisioncallback);
	cameratool->addComponent(colltoggle, 100, 10);

	ButtonComponent * b = NULL;
	b = new ButtonComponent();
	if (b == NULL) return false;

	b->setTitle("Set Level Start From Cam");
	b->setCallback(updateStartPosCall);
	cameratool->addComponent(b, 100, 10);

	cameratool->FitToContent();

	return true;
}

bool EditorCameraTool::testClick(int x, int y) {
	if (cameratool->isVis()) return cameratool->testClick(x, y);
	else return false;
}

void EditorCameraTool::render() {
	if (cameratool->isVis()) cameratool->render();
}

void EditorCameraTool::cameracollisioncallback(int code) {
	CAM->toggleFreeCam();

	if(colltoggle->getTitle() == "Free Cam Is: Off") colltoggle->setTitle("Free Cam Is: On");
	else colltoggle->setTitle("Free Cam Is: Off");
}

void EditorCameraTool::updateStartPosCall(int code) {
	LVL->setStartPos(vec3(CAM->getActiveCam()->getPos()));
	LVL->setStartOreientation(vec2(CAM->getActiveCam()->getHorizontalAngle(), CAM->getActiveCam()->getVerticalAngle()));
	ALERT->doNotify("Level Start Position Updated!", NULL);
}