#include "EditorContext.h"

bool EditorContext::active = false;

EditorCameraTool EditorContext::cameratool;
EditorWallTool EditorContext::walltool;
SaveTool EditorContext::savetool;
Window * EditorContext::objecttool = NULL;

EditorContext::EditorContext()
{
	toolbar = NULL;
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

	if (!savetool.initalise()) return false;
	savetool.hide();

	objecttool = WindowFactory::getWindow(WINDOW_MEDIUM_TALL, "GENERIC", vec2(), "Object Tool");
	objecttool->hide();
	
	initToolBar();
	initObjectTool();

	return true;
}

void EditorContext::toolbarClose(int code){
	active = false;
}

void EditorContext::render() {
	walltool.render();
	savetool.render();
	objecttool->render();
	cameratool.render();
	toolbar->render();
}

void EditorContext::update(float time) {
	walltool.update(time);
	objecttool->update(time);
	toolbar->update(time);
	cameratool.update(time);
	savetool.update(time);
}

void EditorContext::initObjectTool() {

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

	toolbar->setCloseButtonCallBack(toolbarClose);
}

bool EditorContext::testClick(int x, int y) {
	if (toolbar->isVis()) if (toolbar->testClick(x, y)) return true;
	if (cameratool.testClick(x, y)) return true;
	if (objecttool->isVis()) if(objecttool->testClick(x, y)) return true;
	if (savetool.testClick(x, y)) return true;
	if (walltool.testClick(x, y)) return true;

	return false;
}

void EditorContext::walltoolclick(int code) {
	walltool.toggle();
}

void EditorContext::objecttoolclick(int code) {
	objecttool->tglVis();
}

void EditorContext::cameratoolclock(int code) {
	cameratool.toggle();
}

void EditorContext::savetoolclick(int code) {
	savetool.toggle();
}