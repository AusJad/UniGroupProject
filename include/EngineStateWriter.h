#pragma once

#include <fstream>
#include "SceneManager.h"
#include "Wall.h"
#include "GenericObject.h"

class EngineStateWriter
{
public:
	static bool writeState(std::string filename);
	static bool readState(std::string filename);
private:
	static void addGenericObj(std::ifstream & toparse);
	static void addWall(std::ifstream & toparse);
};

