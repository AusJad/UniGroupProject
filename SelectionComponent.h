#pragma once

#include "FontEngine.h"
#include "ButtonComponent.h"

class SelectionComponent : public WndComponent
{
public:
	SelectionComponent(int width, int height, vec2 pos);

	void render();
	bool testClick(int x, int y);

private:
	ButtonComponent left;
	ButtonComponent right;
	ButtonComponent enter;

	std::vector<std::string> options;
	int curoption;

	void incOpt();
	void decOpt();
};

