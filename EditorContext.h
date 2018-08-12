#pragma once

#include "EditorWallTool.h"
#include "CameraManager.h"

class EditorContext
{
public:
	EditorContext();
	~EditorContext();

	bool initalise();
	void render();
	void update(float time);

	bool isActive() { return active; };
	void tggleActive() { active = !active; }
	void disable(){ active = false; }
	void enable() { active = true; toolbar->show(); }

	bool testClick(int x, int y);

private:
	Window * toolbar;
	static EditorWallTool walltool;
	static Window * objecttool;
	static bool active;

	void initToolBar();
	void initObjectTool();

	static void toolbarClose(int code);
	static void walltoolclick(int code);
	static void objecttoolclick(int code);
};

