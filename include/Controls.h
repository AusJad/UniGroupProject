#pragma once

#include <map>
#include "ResourceList.h"
#include "RenderModuleStubb.h"
#include "LUAScriptManager.h"
#include "SimpleString.h"
#include "../WndComponent.h"

#define CONT Singleton<Controls>::getInstance()

/**
* @class Controls
* @brief Class for handling user input
*
* @author Morgan Smolder
* @version 01
* @date 02/04/2018
*/
class Controls
{
	public:
		Controls();
		~Controls();

		/**
		* @brief Add a new control group.
		*
		* @param controlgroup - The new control group.
		*/
		void addControlGroup(unsigned controlgroup);

		/**
		* @brief Add a initalised control group.
		*
		* @param controlgroup - The new control group.
		* @param data - The data for the control group.
		*/
		void addInitalisedControlGroup(unsigned controlgroup, ResourceList & data);

		/**
		* @brief Bind the controls to the resources.
		*
		* @param group - The group number.
		* @para toset - The resources being bound.
		*
		* @return bool - If resources were bound.
		*/
		bool bindControls(unsigned group, ResourceList & toset);
	
		/**
		* @brief Change the controls of one group and update the renderer.
		*
		* @param groupno - The control group number.
		* @param render - The renderer.
		* @param tochange - The new controls.
		*
		* @return bool - If the controls were changed.
		*/
		static bool changeControlGroup(unsigned groupno, RenderModuleStubb* render, Controls* tochange);

		static void switchContextConsole(bool active, RenderModuleStubb* render, Controls* tochange);

		static void switchContextTextInput(std::string * toedit, onClick whenComplete);

	private:
		/// Map of resource lists with a ID.
		std::map<int, ResourceList> controls;

		/// Current group.
		unsigned curgroup;

		/// Previous x variable.
		static double prevx;
		/// Previous y variable.
		static double prevy;

		static std::string* textin;
		static onClick textincomplete;

		/**
		* @brief Bind the controls to a control object.
		*
		* @param groupno - The object id.
		* @param render - The renderer.
		* @param tochange - The controls being changed.
		*/
		static void bindControls(unsigned groupno, RenderModuleStubb* render, Controls* tochange);

		/**
		* @brief Unbind the controls of a controller.
		*
		* @param groupno - The id of the controller being unbound.
		* @param render - The renderer.
		* @param tochange - The controller being changed.
		*/
		static void unbindControls(unsigned groupno, RenderModuleStubb* render, Controls* tochange);

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

		static void keyInputCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

		/**
		* @brief Mouse cursor callback funtion.
		*
		* @param window - The window being rendered.
		* @param x - The x coord.
		* @param y - The y coord.
		*/
		static void mouseCallback(GLFWwindow* window, double x, double y);

		static void mouseCallbackMenu(GLFWwindow* window, double x, double y);

		/**
		* @brief The mouse button callback function.
		*
		* @param window - The window being rendered.
		* @param button - The button being pressed.
		* @param action - ID for the action to be taken.
		* @param mods - ID for any special action to be taken.
		*/
		static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

		//Coded in C++ for enhanced speed
		static void Controls::ConsoleCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};