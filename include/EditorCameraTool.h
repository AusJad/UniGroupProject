#pragma once
#include "WindowFactory.h"
#include "CameraManager.h"
#include "Level.h"
#include "Alert.h"

/**
* @class EditorCameraTool
*
* @author Morgan Smolder
*/
class EditorCameraTool
{
public:
	EditorCameraTool();
	~EditorCameraTool();

	void toggle();
	void show();
	void hide();
	bool testClick(int x, int y);
	void render();
	bool initalise();
	void update(float time);

private:
	Window * cameratool;
	static ButtonComponent * colltoggle;

	static void cameracollisioncallback(int code);
	static void updateStartPosCall(int code);
};

