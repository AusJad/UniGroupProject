#pragma once

#include "UITextures.h"
#include "vec2.h"

typedef void(*onClick)(int action);

#define BUTTON_CLICK 0
#define TEXT_INPUT 1
#define LABEL_CLICK 2

class WndComponent
{
public:
	WndComponent();
	WndComponent(int width, int height, vec2 pos);
	virtual void render() = 0;
	virtual bool testClick(int x, int y) = 0;
	void setCallback(onClick toset);
	virtual void setWidth(int toset);
	virtual void setHeight(int toset);
	virtual void setPos(vec2 toset);
	virtual void move(float x, float y);
	virtual void update(float time) {}

	int getWidth() { return width; }
	int getHeight() { return height; }
	vec2 & getPos() { return pos; }
protected:
	int width;
	int height;
	vec2 pos;
	onClick callback;
};

