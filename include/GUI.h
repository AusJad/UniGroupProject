#pragma once
#include "Singleton.h"
#include "EditorContext.h"
#include "Alert.h"
#include "MainMenu.h"

#define GI Singleton<GUI>::getInstance()

enum GUIState {
	inactive = 0,
	mainmenu = 1,
	editorst = 2
};

class GUI
{
public:
	GUI();
	~GUI();
	bool initalise();
	void update(float time);
	void render();
	bool testClick(int x, int y);
	void setState(GUIState toset);
	GUIState getState() { return state; }

private:
	GUIState state;
	EditorContext editor;
	LabelComponent instructions;
	MainMenu mmenu;

	void updateSelf();
	void renderInstructions();
	void enableState(GUIState toenable);
	void disableState(GUIState todisable);

	static void playGameCallback(int code);
};

