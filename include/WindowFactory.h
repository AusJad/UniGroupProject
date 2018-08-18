#pragma once

#include "Window.h"

#define WINDOW_SMALL_SQUARE		0
#define WINDOW_MEDIUM_SQUARE	1
#define WINDOW_MEDIUM_WIDE		2
#define WINDOW_SMALL_WIDE		3
#define WINDOW_MEDIUM_TALL		4

class WindowFactory
{
public:
	static Window* getWindow(int size, std::string type, vec2 stpos, std::string title = "Window");
};

