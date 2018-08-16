#include "WindowFactory.h"


Window* WindowFactory::getWindow(int size, std::string type, vec2 stpos, std::string title) {
	Window * ret = NULL;

	if (type == "GENERIC") {
		switch (size) {
			case WINDOW_SMALL_SQUARE:
				ret = new Window(stpos, 512, 256, title);
				break;
			case WINDOW_MEDIUM_SQUARE:
				ret = new Window(stpos, 512, 512, title);
				break;
			case WINDOW_SMALL_WIDE:
				ret = new Window(stpos, 512, 128, title);
				break;
			case WINDOW_MEDIUM_TALL:
				ret = new Window(stpos, 256, 512, title);
				break;
			case WINDOW_MEDIUM_WIDE:
				ret = new Window(stpos, 512, 700, title);
				break;
		}
	}

	return ret;
}