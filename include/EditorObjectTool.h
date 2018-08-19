#pragma once

#include "WindowFactory.h"
#include "Alert.h"
#include "Model.h"
#include "GenericObject.h"
#include "Controls.h"
#include "AxisDefs.h"
#include "SceneManager.h"

class EditorObjectTool
{
public:
	EditorObjectTool();
	~EditorObjectTool();
	bool isVis();
	void toggle();
	void show();
	void hide();
	bool init();
	void render();
	void update(float time);
	bool testClick(int x, int y);
private:
	Window * objecttool;

	static GenericObject * object;

	static SelectionComponent * modelin;

	static TextInputComponent * scalexin;
	static TextInputComponent * scaleyin;
	static TextInputComponent * scalezin;

	static TextInputComponent * posxin;
	static TextInputComponent * posyin;
	static TextInputComponent * poszin;

	static TextInputComponent * rotxin;
	static TextInputComponent * rotyin;
	static TextInputComponent * rotzin;

	static bool inplacemode;
	static float camnearoffset;

	static void setScaleXCallback(int code);
	static void setScaleYCallback(int code);
	static void setScaleZCallback(int code);

	static void setPosXCallBack(int code);
	static void setPosYCallBack(int code);
	static void setPosZCallBack(int code);

	static void setRotXCallBack(int code);
	static void setRotYCallBack(int code);
	static void setRotZCallBack(int code);

	static vec3 calcOffset(int off, int axis);
	static void updateModel(int code);
	static void switchPlaceMode(int code);
	static void onObjectPlace();
	static void mouseScroll(float offset);
	static void addToGameCallback(int code);

	static void setInToObjVal();
};

