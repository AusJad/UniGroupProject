#pragma once

#include "RenderModuleStubb.h"
#include "FontEngine.h"
#include "WndComponent.h"
#include <string>

/**
* @class LabelComponent
*
* @author Morgan Smolder
*/
class LabelComponent : public WndComponent
{
public:
	LabelComponent() : WndComponent() { padding = 0; };
	LabelComponent(int width, int height, vec2 pos) : WndComponent(width, height, pos) { padding = 3; };
	void render();
	bool testClick(int x, int y);
	void setLabel(std::string toset);
	void setWidth(int toset);
	void setHeight(int toset);
	void setPos(vec2 toset);
	void setTex(std::string toset) { texture = toset; }
	void setPadding(int toset) { padding = toset; recalcDimensions(); }

private:
	std::string texture;
	std::string label;
	std::string vislabel;
	int padding;

	void recalcDimensions();
};

