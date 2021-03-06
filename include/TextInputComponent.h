#pragma once

#include "WndComponent.h"
#include "RenderModuleStubb.h"
#include "FontEngine.h"
#include "Controls.h"
#include "UITextures.h"
#include <string>

/**
* @class TextInputComponent
*
* @author Morgan Smolder
*/
class TextInputComponent : public WndComponent
{
public:
	TextInputComponent() : WndComponent() { inputactive = false; };
	TextInputComponent(int width, int height, vec2 pos);
	void render();
	bool testClick(int x, int y);
	std::string getValue() { return value; }
	void setValue(std::string toset) { value = toset; }

private:
	void calcVis();
	std::string value;
	
	std::string editvis;
	std::string staticvis;

	int id;
	bool inputactive;
};

