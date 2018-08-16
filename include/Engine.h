#pragma once

#include "SceneManager.h"
#include "LUAScriptManager.h"
#include "Singleton.h"
#include "CtoLUABinder.h"
#include "RenderModuleStubb.h"
#include "AssetManager.h"
#include "AudioEngine.h"
#include "windows.h"
#include "Controls.h"
#include "../GUI.h"

/**
* @class Engine
* @brief Class for handling all other engines and creating their objects
*
* @author Morgan Smolder
* @version 01
* @date 02/04/2018
*/
class Engine
{
public:

	/**
	* @brief Initalise the engine.
	*
	* @param initscript - The script to being called to initalise the engine.
	*
	* @return bool - If the engine was initilised.
	*/
	bool Initalise(std::string initscript);

	/**
	* @brief The run funtion.
	*/
	void Run();

private:

	/**
	* @brief Initalise the scripting interface.
	*
	* @return bool - If it was initalised.
	*/
	bool initaliseScriptingInterface();

	/**
	* @brief Initalise the renderer.
	*
	* @return bool - If it was initalised.
	*/
	bool initaliseRenderer();

	/**
	* @brief Initalise the audio engine.
	*
	* @return bool - If it was initalised.
	*/
	bool initaliseAudioEngine();

	void renderLoad();

	static void SwitchInterfaceContext();
	static void SwitchPlayContext();
};

