#include "TextInputContext.h"

std::string* TextInputContext::textin = NULL;
onClick TextInputContext::textincomplete = NULL;
bool* TextInputContext::inputactive = NULL;
bool TextInputContext::done = false;

void TextInputContext::setActive(std::string* text, onClick oncomplete, bool * active) {
	TextInputContext::textin = text;
	textincomplete = oncomplete;
	done = false;
	inputactive = active;
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
		//signal input complete
		*inputactive = false;
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

void TextInputContext::buttonCallback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		//call callback if registered
		if (textincomplete != NULL) textincomplete(TEXT_INPUT);

		// set finished flag
		done = true;
		//signal input complete
		*inputactive = false;
	}
}