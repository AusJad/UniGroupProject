#pragma once

#include "WindowFactory.h"

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
	Window * walltool;
	Window * objecttool;
	static bool active;

	void initWallTool();
	void initToolBar();
	void initObjectTool();

	static void toolbarClose(int code);
};

