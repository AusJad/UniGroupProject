#pragma once
#include "WndComponent.h"
#include "RenderModuleStubb.h"
#include "TextureManager.h"
#include <string>
#include <iostream>

class ButtonComponent : public WndComponent
{
public:
	ButtonComponent(int width, int height, vec2 pos);
	void render();
	bool testClick(int x, int y);
private:
	std::string buttontex;

};

