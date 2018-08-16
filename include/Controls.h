#pragma once

#include <map>
#include "ResourceList.h"
#include "RenderModuleStubb.h"
#include "LUAScriptManager.h"
#include "SimpleString.h"
#include "../LuaControlContext.h"
#include "../GUIInteractContext.h"
#include "../TextInputContext.h"
#include "../WindowMoveContext.h"
#include "../FPSControlsContext.h"

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

		void addInitalisedControlGroup(unsigned controlgroup, ResourceList & data);

		bool bindControls(unsigned group, ResourceList & toset);

		void update();

		static bool changeControlGroup(unsigned groupno, RenderModuleStubb* render, Controls* tochange);

		static void switchContextConsole(bool active, RenderModuleStubb* render, Controls* tochange);

		static void switchContextTextInput(std::string * toedit, onClick whenComplete);

		static void switchContextMenuMove(movementInfo * tomove);

		static void switchContextGUIInteract();

		static void switchContextPlay();

		static void restorePreviousControlContext();

		void registerCallbacks(engineCallback toset);
		void registerGUICallback(engineCallback toset);

	private:
		/// Map of resource lists with a ID.
		std::map<int, ControlContext*> controls;
		GUIInteractContext GIC;
		TextInputContext TIC;
		WindowMoveContext WMC;
		FPSControlsContext FPS;

		ControlContext * activecontext;
		ControlContext * prevcontext;
		//temporary until proper controls sorted
		ControlContext * lastLUAContext;

		/**
		* @brief Bind the controls to a control object.
		*
		* @param groupno - The object id.
		* @param render - The renderer.
		* @param tochange - The controls being changed.
		*/
		static void bindControls(ControlContext* tobind);

		/**
		* @brief Unbind the controls of a controller.
		*
		* @param groupno - The id of the controller being unbound.
		* @param render - The renderer.
		* @param tochange - The controller being changed.
		*/
		static void unbindControls(ControlContext* tobind);


		//Coded in C++ for enhanced speed
		static void Controls::ConsoleCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};