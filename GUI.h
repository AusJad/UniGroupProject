#pragma once
#include "Singleton.h"
#include "EditorContext.h"

#define GI Singleton<GUI>::getInstance()

class GUI
{
public:
	GUI();
	~GUI();
	bool initalise();
	void update(float time);
	void render();
	bool testClick(int x, int y);
	void disableEditor();
	void enableEditor();

private:
	EditorContext editor;
	LabelComponent instructions;

	bool pasteditorcontext;
};

