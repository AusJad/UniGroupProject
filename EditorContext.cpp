#include "EditorContext.h"

bool EditorContext::active = false;

EditorContext::EditorContext()
{

}


EditorContext::~EditorContext()
{
}

bool EditorContext::initalise() {
	toolbar = WindowFactory::getWindow(WINDOW_SMALL_WIDE, "GENERIC", vec2(500, 500), "Editor Toolbar - Close to Exit Editor");
	walltool = WindowFactory::getWindow(WINDOW_MEDIUM_TALL, "GENERIC", vec2(800, 0), "Wall Tool");
	objecttool = WindowFactory::getWindow(WINDOW_MEDIUM_TALL, "GENERIC", vec2(), "Object Tool");

	initToolBar();
	initWallTool();
	initObjectTool();

	return true;
}

void EditorContext::toolbarClose(int code){
	active = false;
}

void EditorContext::render() {
	walltool->render();
	objecttool->render();
	toolbar->render();
}

void EditorContext::update(float time) {
	walltool->update(time);
	objecttool->update(time);
	toolbar->update(time);
}

void EditorContext::initWallTool() {
	LabelComponent * l = new LabelComponent();
	l->setLabel("Select Texture:");
	walltool->addComponent(l, 100, 10);
	walltool->addComponent(new SelectionComponent(), 100, 15);
	l = new LabelComponent();
	l->setLabel("Set Width:");
	walltool->addComponent(l, 60, 10);
	walltool->addComponent(new TextInputComponent(), 40, 10);
	l = new LabelComponent();
	l->setLabel("Set Height:");
	walltool->addComponent(l, 60, 10);
	walltool->addComponent(new TextInputComponent(), 40, 10);
}

void EditorContext::initObjectTool() {

}

void EditorContext::initToolBar() {
	toolbar->setPadding(0);
	toolbar->addComponent(new ButtonComponent(), 25, 100);
	toolbar->addComponent(new ButtonComponent(), 25, 100);
	toolbar->addComponent(new ButtonComponent(), 25, 100);
	toolbar->setCloseButtonCallBack(toolbarClose);
}

bool EditorContext::testClick(int x, int y) {
	if (walltool->testClick(x, y)) return true;
	else if (objecttool->testClick(x, y)) return true;
	else if (toolbar->testClick(x, y)) return true;

	return false;
}