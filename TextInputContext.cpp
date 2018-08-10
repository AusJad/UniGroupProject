#include "TextInputContext.h"

std::string* TextInputContext::textin = NULL;
onClick TextInputContext::textincomplete = NULL;
bool TextInputContext::done = false;

void TextInputContext::setActive(std::string* text, onClick oncomplete) {
	TextInputContext::textin = text;
	textincomplete = oncomplete;
	done = false;
}

void TextInputContext::setInActive() {
	TextInputContext::textin = NULL;
	TextInputContext::textincomplete = NULL;
	done = false;
}

void TextInputContext::keyInputCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ENTER) {
		//call callback if registered
		if (textincomplete != NULL) textincomplete(TEXT_INPUT); 

		// set finished flag
		done = true;
	}
	else {
		if (textin != NULL) {
			if (action == GLFW_PRESS) {
				if (key == GLFW_KEY_BACKSPACE) {
					if (!textin->empty()) textin->pop_back();
				}
				else textin->push_back((char)key);
			}
		}
	}
}