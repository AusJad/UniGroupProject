#include "EditorContext.h"

bool EditorContext::active = false;

Window * EditorContext::walltool = NULL;
Window * EditorContext::objecttool = NULL;

EditorContext::EditorContext()
{

}


EditorContext::~EditorContext()
{
}

bool EditorContext::initalise() {
	toolbar = WindowFactory::getWindow(WINDOW_SMALL_WIDE, "GENERIC", vec2(500, 500), "Editor Toolbar - Close to Exit Editor");
	
	walltool = WindowFactory::getWindow(WINDOW_MEDIUM_TALL, "GENERIC", vec2(800, 0), "Wall Tool");
	walltool->hide();

	objecttool = WindowFactory::getWindow(WINDOW_MEDIUM_TALL, "GENERIC", vec2(), "Object Tool");
	objecttool->hide();
	
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
	if (walltool->testClick(x, y)) return true;
	else if (objecttool->testClick(x, y)) return true;
	else if (toolbar->testClick(x, y)) return true;

	return false;
}

void EditorContext::walltoolclick(int code) {
	walltool->tglVis();
}

void EditorContext::objecttoolclick(int code) {
	objecttool->tglVis();
}