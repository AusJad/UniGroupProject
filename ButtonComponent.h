#pragma once
#include "WndComponent.h"
#include "RenderModuleStubb.h"
#include "TextureManager.h"
#include "FontEngine.h"
#include <string>
#include <iostream>

class ButtonComponent : public WndComponent
{
public:
	ButtonComponent() : WndComponent() {};
	ButtonComponent(int width, int height, vec2 pos);
	void render();
	bool testClick(int x, int y);
	void setTex(std::string ntex);
	void setTitle(std::string toset);

	void setWidth(int toset);
	void setHeight(int toset);
	void setPos(vec2 toset);
private:
	void recalcDimensions();

	std::string buttontex;
	std::string text;
	std::string vistext;

	vec2 textpos;
};

