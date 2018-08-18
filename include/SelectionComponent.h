#pragma once

#include "FontEngine.h"
#include "ButtonComponent.h"
#include "LabelComponent.h"

class SelectionComponent : public WndComponent
{
public:
	SelectionComponent();
	SelectionComponent(int width, int height, vec2 pos);

	void render();
	bool testClick(int x, int y);

	void setWidth(int toset);
	void setHeight(int toset);
	void setPos(vec2 toset);

	void addSelection(std::string toadd);
	std::string getActiveSelection() { if (curoption != -1) return options.at(curoption); else return ""; }

	void move(float x, float y);

private:
	ButtonComponent left;
	ButtonComponent right;
	ButtonComponent enter;
	LabelComponent selection;

	std::vector<std::string> options;
	int curoption;

	void incOpt();
	void decOpt();
	void recalcDimensions();
};

