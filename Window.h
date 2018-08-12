#pragma once
#include <vector>
#include "WndComponent.h"
#include "ButtonComponent.h"
#include "LabelComponent.h"
#include "SelectionComponent.h"
#include "RenderModuleStubb.h"
#include "vec2.h"
#include "TextureManager.h"
#include "FontEngine.h"
#include "TextInputComponent.h"
#include "UITextures.h"
#include "movementInfo.h"

#define HEAD_BAR_SIZE 32

class Window
{
public:
	Window(vec2 & stpos, float width, float height, std::string title);

	void update(float time);
	void render();
	void move(float x, float y);
	bool testClick(int x, int y);

	void tglVis();
	bool isVis();
	void show() { visible = true; }
	void hide() { visible = false; }

	void setCloseButtonCallBack(onClick callback);
	void addComponent(WndComponent * toadd, int widthprcnt, int heightprcnt);
	void addComponent(WndComponent * toadd);
	void setPadding(int toset) { padding = toset; }

	void FitToContent();

private:
	std::string bgtex;

	bool visible;
	bool hasHeader;

	movementInfo mvdata;

	void initHeader(std::string title);

	vec2 tlscreen;
	vec2 brscreen;
	int padding;
	
	LabelComponent header;
	ButtonComponent closebutton;
	std::vector<WndComponent*> components;

	void calculateSize();

	static onClick closebuttoncallback;

	vec2 calcComponentPlacement(WndComponent * toplace);
};

