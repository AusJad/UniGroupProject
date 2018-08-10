#pragma once

#include "WndComponent.h"
#include "RenderModuleStubb.h"
#include "FontEngine.h"
#include "Controls.h"
#include <string>

class TextInputComponent : public WndComponent
{
public:
	TextInputComponent() : WndComponent() {};
	TextInputComponent(int width, int height, vec2 pos);
	void render();
	bool testClick(int x, int y);
	void onInputComplete();
private:
	std::string value;
	int id;
};

