#pragma once

#include <fstream>
#include "SceneManager.h"
#include "Wall.h"

class EngineStateWriter
{
public:
	static bool writeState(std::string filename);
	static bool readState(std::string filename);
	static void addWall(std::ifstream & toparse);
};

