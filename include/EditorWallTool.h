#pragma once
#include "WindowFactory.h"
#include "Wall.h"
#include "CameraManager.h"
#include "SceneManager.h"
#include "CollisionEngine.h"
#include "Alert.h"

#define LABEL_PADDING 10

#define ORIGIN "Origin"
#define CAMERA "Camera"
#define PLACE "Place With Look"
#define PREV_WALL "Last Wall"

#define X_AXIS 0
#define Y_AXIS 1
#define Z_AXIS 2

#define ITEM_NEAR 30.0f
#define ITEM_FAR 300.0f
#define SCROLL_OFFSET_MODIFIER 6.0f

class EditorWallTool
{
public:
	void toggle();
	void show();
	void hide();
	bool init();
	void render();
	void update(float time);
	bool testClick(int x, int y);
private:
	Window * walltool;

	static int camnearoffset;

	static vec3 wallposref;
	static bool inplacemode;
	static bool inselectmode;

	static Wall * wall;
	static Wall * prevwall;

	static SelectionComponent * texturein;

	static TextInputComponent * widthin;
	static TextInputComponent * heightin;
	static TextInputComponent * depthin;

	static std::string relativeselection;
	static SelectionComponent * positionrin;

	static TextInputComponent * posxin;
	static TextInputComponent * posyin;
	static TextInputComponent * poszin;

	static TextInputComponent * rotxin;
	static TextInputComponent * rotyin;
	static TextInputComponent * rotzin;

	static void setHeightCallback(int code);
	static void setWidthCallback(int code);
	static void setDepthCallback(int code);
	
	static void setPosXCallBack(int code);
	static void setPosYCallBack(int code);
	static void setPosZCallBack(int code);

	static void setRotXCallBack(int code);
	static void setRotYCallBack(int code);
	static void setRotZCallBack(int code);

	static void updateTextureCallback(int code);
	static void updateRelativeSelection(int code);

	static void onWallPlace();

	static void placeWall(int code);

	static void resetWallPos(int code);

	static vec3 calcOffset(int off, int axis);

	static void addToGameCallBack(int code);

	static void mouseScroll(float offset);

	static void selectItemStart(int code);

	static void onWallSelect();

	static void selectItem(int code);

	static void setInputsFromWall();

	static std::string selectionwalltex;
	static Wall* selectionWall;

	static void confirmSelectItem(int code);
};

