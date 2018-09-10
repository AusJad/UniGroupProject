#pragma once

#include "ControlContext.h"
#include "ResourceList.h"
#include "LUAScriptManager.h"
#include "SimpleString.h"

/**
* @class LuaControlContext
*
* @author Morgan Smolder
*/
class LuaControlContext : public ControlContext
{
public:
	keyCallback getKeyCallback();
	mouseMoveCallback getMouseMoveCallback();
	mouseButtonCallback getMouseButtonCallback();
	void setActive();
	void setInActive();

	static ResourceList & getActiveContext();

	void bindControls(ResourceList & tobind) { boundcontrols = tobind; }

private:

	static double prevx;
	/// Previous y variable.
	static double prevy;
	
	static ResourceList activecontext;

	ResourceList boundcontrols;

	/**
	* @brief Keyboard key callback function
	*
	* @param window - The window being rendered.
	* @param key - The key being called.
	* @param scanecode - The scan code of the key.
	* @param action - ID for the action to be taken.
	* @param mods - ID for any special actions.
	*/
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

	/**
	* @brief Mouse cursor callback funtion.
	*
	* @param window - The window being rendered.
	* @param x - The x coord.
	* @param y - The y coord.
	*/
	static void mouseCallback(GLFWwindow* window, double x, double y);

	/**
	* @brief The mouse button callback function.
	*
	* @param window - The window being rendered.
	* @param button - The button being pressed.
	* @param action - ID for the action to be taken.
	* @param mods - ID for any special action to be taken.
	*/
	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
};

