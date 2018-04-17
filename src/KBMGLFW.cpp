#include "KBMGLFW.h"

int kbmInput::getKey(GLFWwindow *window, int key)
{
	return glfwGetKey(window, key);
}

int kbmInput::getMouseButton(GLFWwindow *window, int button)
{
	return glfwGetMouseButton(window, button);
}

void kbmInput::getCursorPos(GLFWwindow *window, double *xpos, double *ypos)
{
	glfwGetCursorPos(window, xpos, ypos);
}

GLFWkeyfun kbmInput::setCharCallback(GLFWwindow *window, GLFWcharfun keycallback)
{
	glfwSetCharCallback(window, keycallback);
}

GLFWmousebuttonfun kbmInput::setMouseButtonCallback(GLFWwindow *window, GLFWmousebuttonfun mousebutton)
{
	glfwSetMouseButtonCallback(window, mousebutton);
}