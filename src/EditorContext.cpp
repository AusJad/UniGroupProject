#include "EditorContext.h"

bool EditorContext::active = false;

EditorCameraTool EditorContext::cameratool;
EditorWallTool EditorContext::walltool;
EditorAgentTool EditorContext::agenttool;
SaveTool EditorContext::savetool;
EditorObjectTool EditorContext::objecttool;
Window * EditorContext::toolbar = NULL;

EditorContext::EditorContext()
{
}


EditorContext::~EditorContext()
{
	delete toolbar;
}

bool EditorContext::initalise() {
	toolbar = WindowFactory::getWindow(WINDOW_SMALL_WIDE, "GENERIC", vec2(768, 592), "Editor Toolbar - Close to Exit Editor");
	if (toolbar == NULL) return false;

	if(!walltool.init()) return false;
	walltool.hide();

	if (!cameratool.initalise()) return false;
	cameratool.hide();

	if (!agenttool.init()) return false;
	agenttool.hide();

	if (!savetool.initalise()) return false;
	savetool.hide();

	if (!objecttool.init()) return false;
	objecttool.hide();
	
	if (!initToolBar()) return false;

	RNDR->addResizeCallBack(windowResizeCallback);
	windowResizeCallback(RNDR->getWinWidth(), RNDR->getWinHeight());

	return true;
}

void EditorContext::toolbarClose(int code){
	active = false;
}

void EditorContext::render() {
	walltool.render();
	savetool.render();
	objecttool.render();
	agenttool.render();
	cameratool.render();
	toolbar->render();
}

void EditorContext::update(float time) {
	walltool.update(time);
	objecttool.update(time);
	agenttool.update(time);
	toolbar->update(time);
	cameratool.update(time);
	savetool.update(time);
}

bool EditorContext::initToolBar() {
	toolbar->setPadding(0);

	ButtonComponent * b = NULL;
	b = new ButtonComponent();
	if (b == NULL) return false;
	b->setWidth(96);
	b->setHeight(96);
	b->setTex(WALL_TOOL_ICON);
	b->setCallback(walltoolclick);
	toolbar->addComponent(b);

	b = NULL;
	b = new ButtonComponent();
	if (b == NULL) return false;
	b->setWidth(96);
	b->setHeight(96);
	b->setTex(OBJECT_TOOL_ICON);
	b->setCallback(objecttoolclick);
	toolbar->addComponent(b);

	b = NULL;
	b = new ButtonComponent();
	if (b == NULL) return false;
	b->setWidth(96);
	b->setHeight(96);
	b->setTex(AGENT_TOOL_ICON);
	b->setCallback(agenttoolclick);
	toolbar->addComponent(b);

	b = NULL;
	b = new ButtonComponent();
	if (b == NULL) return false;
	b->setWidth(96);
	b->setHeight(96);
	b->setTex(CAM_TOOL_ICON);
	b->setCallback(cameratoolclock);
	toolbar->addComponent(b);

	b = NULL;
	b = new ButtonComponent();
	if (b == NULL) return false;
	b->setWidth(96);
	b->setHeight(96);
	b->setTex(SAVE_TOOL_ICON);
	b->setCallback(savetoolclick);
	toolbar->addComponent(b);

	b = NULL;
	b = new ButtonComponent();
	if (b == NULL) return false;
	b->setWidth(32);
	b->setHeight(96);
	b->setTex(TOOLBAR_END_ICON);
	toolbar->addComponent(b);

	toolbar->setCloseButtonCallBack(toolbarClose);

	return true;
}

bool EditorContext::testClick(int x, int y) {
	if (toolbar->isVis()) if (toolbar->testClick(x, y)) return true;
	if (cameratool.testClick(x, y)) return true;
	if (objecttool.isVis()) if(objecttool.testClick(x, y)) return true;
	if (agenttool.isVis()) if (agenttool.testClick(x, y)) return true;
	if (savetool.testClick(x, y)) return true;
	if (walltool.testClick(x, y)) return true;

	return false;
}

void EditorContext::walltoolclick(int code) {
	walltool.toggle();
	if (walltool.isVis()) {
		objecttool.hide();
		agenttool.hide();
	}
}

void EditorContext::objecttoolclick(int code) {
	objecttool.toggle();
	if (objecttool.isVis()) {
		walltool.hide();
		agenttool.hide();
	}
}

void EditorContext::agenttoolclick(int code) {
		agenttool.toggle();
		if (agenttool.isVis()) {
			walltool.hide();
			objecttool.hide();
		}
	}

void EditorContext::cameratoolclock(int code) {
	cameratool.toggle();
}

void EditorContext::savetoolclick(int code) {
	savetool.toggle();
}

void EditorContext::windowResizeCallback(int nwidth, int nheight){
	toolbar->placeAt(nwidth - 512.0f, nheight - 128.0f);
}