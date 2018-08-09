#pragma once

#include "WndComponent.h"
#include "RenderModuleStubb.h"
#include <string>

class TextInputComponent : public WndComponent
{
public:
	TextInputComponent(int width, int height, vec2 pos);
	void render();
	bool testClick(int x, int y);
private:
	std::string value;
	int id;
};

