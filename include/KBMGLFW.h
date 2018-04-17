#pragma once

#include "GLFW\glfw3.h"

/**
* @class kbmInput
* @brief Facade class for GLFW keyboard and mouse input.
*
* @author Matthew MacLennan
* @version 1.3
* @date 10 / 04 / 2018
*/
class kbmInput
{
	/**
	* @brief Gets keyboard input from user for specified window.
	*
	* @param window(GLFWwindow*) - Pointer to the window that is being used.
	* @param key(int) - Key being pressed.
	*
	* @return int - Key being pressed.
	*/
	int getKey(GLFWwindow *window, int key);

	/**
	* @brief Gets mouse button input from used for specified window.
	*
	* @param window(GLFWwindow*) - Pointer to the window that is being used.
	* @param button(int) - The mouse button being pressed.
	*
	* @return int - Mouse button being pressed.
	*/
	int getMouseButton(GLFWwindow *window, int button);

	/**
	* @brief Gets cursor position.
	*
	* @param window(GLFWwindow*) - Pointer to the window that is being used.
	* @param xpos(double*) - Pointer to the x position.
	* @param ypos(double*) - Pointer to the y position.
	*
	* @return NONE.
	*/
	void getCursorPos(GLFWwindow *window, double *xpos, double *ypos);

	/**
	* @brief Set keyboard callback function.
	*
	* @param window(GLFWwindow*) - Pointer to the window that is being used.
	* @param keycallback(GLFWcharfun) - Function name of key callback function to be assigned.
	*
	* @param GLFWkeyfun - Function that has been assigned for key callback.
	*/
	GLFWkeyfun setCharCallback(GLFWwindow *window, GLFWcharfun keycallback);

	/**
	* @brief Set mouse callback function.
	*
	* @param window(GLFWwindow*) - Pointer tot he window that is being used.
	* @param mousebutton(GLFWmousebuttonfun) - Function name of mouse callback function to be assigned.
	*
	* @return GLFWmousebuttonfun - Function that has been assigned for mouse callback.
	*/
	GLFWmousebuttonfun setMouseButtonCallback(GLFWwindow *window, GLFWmousebuttonfun mousebutton);

};