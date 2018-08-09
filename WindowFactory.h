#pragma once

#include "Window.h"

#define WINDOW_SMALL 0
#define WINDOW_MEDIUM 1

class WindowFactory
{
public:
	static Window* getWindow(int size, std::string type);
};

