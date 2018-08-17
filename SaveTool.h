#pragma once

#include "WindowFactory.h"
#include "EngineStateWriter.h"
#include "Alert.h"

class SaveTool
{
public:
	SaveTool();
	~SaveTool();

	void toggle();
	void show();
	void hide();
	bool testClick(int x, int y);
	void render();
	bool initalise();
	void update(float time);

private:
	Window * savetool;

	static LabelComponent * instructions;
	static ButtonComponent * savelvl;
	static TextInputComponent * filename;

	static void save(int code);
	static void onWndClose(int code);
};

