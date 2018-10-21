#pragma once

#include <fstream>
#include "SceneManager.h"
#include "Wall.h"
#include "GenericObject.h"
#include "Level.h"
#include "Geometry3D.h"

/**
* @class EngineStateWriter
*
* @author Morgan Smolder
*/
class EngineStateWriter
{
public:
	static bool writeState(std::string filename);
	static bool readState(std::string filename);
private:
	static void addGenericObj(std::ifstream & toparse);
	static void addWall(std::ifstream & toparse);
	static void addTerrain(std::ifstream & toparse);
	static void updateLevelInfo(std::ifstream & toparse);
};

