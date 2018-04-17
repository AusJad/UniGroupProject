#pragma once
#include <map>
#include <fstream>	
#include <string> 
#include <iostream>

extern "C" {
	#include "lua/lua.h"
	#include "lua/lualib.h"
	#include "lua/lauxlib.h"
}

#include <luabind/luabind.hpp>

#define LUAERROR luabind::error& e
#define LUAERRORMSG e

#define DEBUGMODE false

/**
* @class LUAScriptManager
* @brief Class for handling lua scripts
*
* @author Morgan Smolder
* @version 01
* @date 02/04/2018
*/
class LUAScriptManager
{
public:
	LUAScriptManager();
	~LUAScriptManager();

	/**
	* @brief Load the script.
	*
	* @param file - The file name.
	* @param name - The script name.
	*
	* @return bool - If the script loaded.
	*/
	bool loadScript(std::string file, std::string name);

	/**
	* @brief Execute the script.
	*
	* @param name - The script name.
	*
	* @return bool - If the script executed.
	*/
	bool doScript(std::string name);

	/**
	* @brief Execute a script from a file.
	*
	* @param name - The file name.
	*
	* @return bool - If the script executed.
	*/
	bool doScriptFromFile(std::string name);

	/**
	* @brief Initalise the lua state.
	*
	* @return bool - If it initalised.
	*/
	bool initLuaState();

	/**
	* @brief Close the lua state.
	*/
	void closeState();

	/**
	* @brief Get the error message.
	*
	* @param LUAERROR - The error message type.
	*
	* @return string - The Error message.
	*/
	std::string getErrorMSG(LUAERROR);

	/**
	* @brief Get the lua state.
	*
	* @return lua_state* - A pointer to the lua state.
	*/
	lua_State* getState();

	/**
	* @brief Set the global state.
	*
	* @param ng - The new global.
	* @param name - The name of the global.
	*/
	template <class T>
	void setGlobal(const T & ng, std::string name) {
		luabind::globals(lstate)[name] = ng;
	}

	/**
	* @brief Call the function for the script.
	*
	* @param func - The function
	*/
	inline void callFunction(std::string func) {
		luabind::call_function<void>(lstate, func.c_str());
	};

	/**
	* @brief Call the function
	*
	* @param func - The function.
	* @param arg - The first arguement.
	*/
	template <class T>
	inline void callFunction(std::string func, T & arg) {
		try {
			luabind::call_function<void>(lstate, func.c_str(), boost::ref<T>(arg));
		}
		catch (LUAERROR)
		{
			std::string error = getErrorMSG(LUAERRORMSG);
			if(DEBUGMODE) std::cerr << error << std::endl;
		}
	};

	/**
	* @brief Call the function
	*
	* @param func - The function.
	* @param arg - The first arguement.
	* @param arg2 - The second arguement.
	*/
	template <class T, class U>
	inline void callFunction(std::string func, T & arg, U & arg2) {
		try {
			luabind::call_function<void>(lstate, func.c_str(), boost::ref<T>(arg), boost::ref<U>(arg2));
		}
		catch (LUAERROR)
		{
			std::string error = getErrorMSG(LUAERRORMSG);
			if (DEBUGMODE) std::cerr << error << std::endl;
		}
	};

	/**
	* @brief Call the function
	*
	* @param func - The function.
	* @param arg - The first arguement.
	* @param arg2 - The second arguement.
	* @param arg3 - The third arguement.
	*/
	template <class T, class U, class V>
	inline void callFunction(std::string func, T & arg, U & arg2, V & arg3) {
		try {
			luabind::call_function<void>(lstate, func.c_str(), boost::ref<T>(arg), boost::ref<U>(arg2), boost::ref<V>(arg3));
		}
		catch (LUAERROR)
		{
			std::string error = getErrorMSG(LUAERRORMSG);
			if (DEBUGMODE) std::cerr << error << std::endl;
		}
	};

	/**
	* @brief Call the function
	*
	* @param func - The function.
	* @param arg - The first arguement.
	* @param arg2 - The second arguement.
	* @param arg3 - The third arguement.
	* @param arg4 - The fourth arguement.
	*/
	template <class T, class U, class V, class W>
	inline void callFunction(std::string func, T & arg, U & arg2, V & arg3, W & arg4) {
		try {
			luabind::call_function<void>(lstate, func.c_str(), boost::ref<T>(arg), boost::ref<U>(arg2), boost::ref<V>(arg3), boost::ref<W>(arg4));
		}
		catch (LUAERROR)
		{
			std::string error = getErrorMSG(LUAERRORMSG);
			if (DEBUGMODE) std::cerr << error << std::endl;
		}
	};

private:
	/// The lua state.
	lua_State* lstate;
	/// A map for scripts.
	std::map< std::string, std::string> scripts;
};

