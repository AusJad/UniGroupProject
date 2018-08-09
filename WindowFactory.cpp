#include "WindowFactory.h"


Window* WindowFactory::getWindow(int size, std::string type) {
	Window * ret = NULL;

	if (type == "GENERIC") {
		ret = new Window(vec2(128, 128), 512, 512, "demo window");

	}


	return ret;
}