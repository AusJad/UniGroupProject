#pragma once

#include "RenderModuleStubb.h"
#include "FontEngine.h"
#include "WndComponent.h"
#include <string>


class LabelComponent : public WndComponent
{
public:
	LabelComponent() : WndComponent() {}; 
	LabelComponent(int width, int height, vec2 pos) : WndComponent(width, height, pos) {};
	void render();
	bool testClick(int x, int y);
	void setLabel(std::string toset);

private:
	std::string label;
};

