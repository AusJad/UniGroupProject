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

/**
* @class GUI
*
* @author Morgan Smolder
*/
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
	bool canEdit() { return mmenu.canEdit(); }
	void setNpc(NPC *npcin);

private:
	GUIState state;
	EditorContext editor;
	LabelComponent instructions;
	LabelComponent npcemos1;
	LabelComponent npcemos1x;
	LabelComponent npcemos1y;
	LabelComponent npcemos1z;
	LabelComponent npcemos1w;
	LabelComponent npcemos2;
	LabelComponent npcemos2x;
	LabelComponent npcemos2y;
	LabelComponent npcemos2z;
	LabelComponent npcemos2w;
	LabelComponent npcemos3;
	LabelComponent npcemos3x;
	LabelComponent npcemos3y;
	LabelComponent npcemos3z;
	LabelComponent npcemos3w;
	int npcCount = 0;
	NPC* npc1 = NULL;
	NPC* npc2 = NULL;
	NPC* npc3 = NULL;

	MainMenu mmenu;

	void updateSelf();
	void renderInstructions();
	void renderNpcEmo();
	void enableState(GUIState toenable);
	void disableState(GUIState todisable);
	void initializeNPCWindow();
	static void playGameCallback(int code);
};

