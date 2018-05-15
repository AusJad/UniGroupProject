#pragma once

#include "SceneManager.h"
//#include "vec3.h"
#include "LUAScriptManager.h"
#include "NPC.h"
#include "Identifiers.h"
#include "MessagingBus.h"
#include "ResourceList.h"
#include "AssetManager.h"
#include "AudioEngine.h"
#include "SimpleString.h"
#include "StaticEntity.h"
#include "TerrainObject.h"
#include "MenuObject.h"
#include "Player.h"
#include "Maths.h"
#include "Scenery.h"
#include "AIMovementBehaviours.h"
#include "MenuTools.h"
#include "ObjectLocList.h"

extern "C" {
	#include "lua/lua.h"
	#include "lua/lualib.h"
	#include "lua/lauxlib.h"
}

#include <luabind/luabind.hpp>
#include <luabind/operator.hpp>

/**
* @class CtoLUABinder
* @brief Class for binding lua script.
*
* @author Morgan Smolder
* @version 01
* @date 02/04/2018
*/
class CtoLUABinder
{
public:
	/**
	* @brief Bind the lua script to the classes.
	*
	* @param lstate - The state of the lua script.
	*/
	void bindClasses(lua_State* lstate);
};

