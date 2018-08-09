#pragma once

#include "vec2.h"

typedef void(*onClick)(int action);

#define BUTTON_CLICK 0

class WndComponent
{
public:
	WndComponent(int width, int height, vec2 pos);
	virtual void render() = 0;
	virtual bool testClick(int x, int y) = 0;
	void setCallback(onClick toset);

protected:
	int width;
	int height;
	vec2 pos;
	onClick callback;
};

