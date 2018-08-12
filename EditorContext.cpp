#include "EditorContext.h"

bool EditorContext::active = false;

EditorWallTool EditorContext::walltool;
Window * EditorContext::objecttool = NULL;

EditorContext::EditorContext()
{

}


EditorContext::~EditorContext()
{
}

bool EditorContext::initalise() {
	toolbar = WindowFactory::getWindow(WINDOW_SMALL_WIDE, "GENERIC", vec2(768, 592), "Editor Toolbar - Close to Exit Editor");
	if (toolbar == NULL) return false;

	if(!walltool.init()) return false;
	walltool.hide();

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
	toolbar->render();
	objecttool->render();
}

void EditorContext::update(float time) {
	walltool.update(time);
	objecttool->update(time);
	toolbar->update(time);
}

void EditorContext::initObjectTool() {

}

void EditorContext::initToolBar() {
	toolbar->setPadding(0);

	ButtonComponent * b = new ButtonComponent();
	b->setWidth(96);
	b->setHeight(96);
	b->setTex(WALL_TOOL_ICON);
	b->setCallback(walltoolclick);
	toolbar->addComponent(b);

	b = new ButtonComponent();
	b->setWidth(96);
	b->setHeight(96);
	b->setTex(OBJECT_TOOL_ICON);
	b->setCallback(objecttoolclick);
	toolbar->addComponent(b);

	toolbar->setCloseButtonCallBack(toolbarClose);
}

bool EditorContext::testClick(int x, int y) {
	if (objecttool->testClick(x, y)) return true;
	else if (walltool.testClick(x, y)) return true;
	else if (toolbar->testClick(x, y)) return true;

	return false;
}

void EditorContext::walltoolclick(int code) {
	walltool.toggle();
}

void EditorContext::objecttoolclick(int code) {
	objecttool->tglVis();
}