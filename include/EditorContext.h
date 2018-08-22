#pragma once

#include "EditorWallTool.h"
#include "EditorCameraTool.h"
#include "CameraManager.h"
#include "EngineStateWriter.h"
#include "SaveTool.h"
#include "EditorObjectTool.h"

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
	void enable() { active = true; toolbar->show(); windowResizeCallback(RNDR->getWinWidth(), RNDR->getWinHeight()); }

	bool testClick(int x, int y);

private:
	static Window * toolbar;
	static EditorCameraTool cameratool;
	static EditorWallTool walltool;
	static SaveTool savetool;
	static EditorObjectTool objecttool;

	static bool active;

	bool initToolBar();

	static void toolbarClose(int code);
	static void walltoolclick(int code);
	static void objecttoolclick(int code);
	static void cameratoolclock(int code);
	static void savetoolclick(int code);

	static void windowResizeCallback(int nwidth, int nheight);
};

