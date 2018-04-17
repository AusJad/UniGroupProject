#include "LUAScriptManager.h"

LUAScriptManager::LUAScriptManager(){
	lstate = NULL;
}


LUAScriptManager::~LUAScriptManager(){
	if (lstate != NULL){
		lua_close(lstate);
		lstate = NULL;
	}
}

std::string LUAScriptManager::getErrorMSG(LUAERROR){
	return lua_tostring(e.state(), -1);
}

lua_State* LUAScriptManager::getState() {
	return lstate;
}

bool LUAScriptManager::loadScript(std::string file, std::string name){
	if (scripts.count(name) == 1) return false;
	
	std::ifstream infile(file.c_str());
	if (!infile) return false;

	std::string tmp;
	std::string out;

	while (infile.peek() != EOF){
		std::getline(infile, tmp);
		out += tmp + "\n";
	}

	if (!out.empty()){
		scripts[name] = out;
		return true;
	}

	return false;
}

bool LUAScriptManager::initLuaState(){

	if (lstate != NULL) return true;

	lstate = luaL_newstate();

	if (!lstate) return false;

	luaL_openlibs(lstate);
	luabind::open(lstate);

	return true;
}


void LUAScriptManager::closeState(){
	lua_close(lstate);
	lstate = NULL;
}

bool LUAScriptManager::doScript(std::string name){
	if (scripts.count(name) == 0) return false;
	if (lstate == NULL) return false;

	luaL_dostring(lstate, scripts.at(name).c_str());

	return true;
}

bool LUAScriptManager::doScriptFromFile(std::string name){
	if (lstate == NULL) return false;

	if (luaL_dofile(lstate, name.c_str()) == 0) return true;

	return false;
}
