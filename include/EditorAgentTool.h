#pragma once

#include "WindowFactory.h"
#include "Alert.h"
#include "Model.h"
#include "GenericObject.h"
#include "Controls.h"
#include "AxisDefs.h"
#include "SceneManager.h"
#include "NPC.h"

/**
* @class EditorAgentTool
*
* @author Mathew Devene
*/
// based on code from EditorObjectTool, by Morgan Smolder
class EditorAgentTool
{
public:
	EditorAgentTool();
	~EditorAgentTool();
	bool isVis();
	void toggle();
	void show();
	void hide();
	bool init();
	void render();
	void update(float time);
	bool testClick(int x, int y);
private:
	static Window * agenttool;

	static NPC * agent;

	static SelectionComponent * modelin;

	static TextInputComponent * posxin;
	static TextInputComponent * posyin;
	static TextInputComponent * poszin;

	static bool inplacemode;
	static float camnearoffset;


	static void setPosXCallBack(int code);
	static void setPosYCallBack(int code);
	static void setPosZCallBack(int code);

	static vec3 calcOffset(int off, int axis);
	static void updateModel(int code);
	static void switchPlaceMode(int code);
	static void onObjectPlace();
	static void mouseScroll(float offset);
	static void addToGameCallback(int code);

	static void setInToObjVal();
};

