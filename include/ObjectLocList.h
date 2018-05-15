#pragma once

#include <map>
#include <vector>
#include <string>
#include "Singleton.h"
#include "vec3.h"

/**
* @class ObjectLocList
* @brief Class for storing static object locations where a key lookup is required for pathfinding, associated with level
*
* @author Mat Devene
* @version 01
* @date 11/05/2018
*/

#define OBJLOCS Singleton<ObjectLocList>::getInstance()

class ObjectLocList
{
public:
	ObjectLocList();
	
	ObjectLocList(std::string level, vec3 pos );

	bool at(std::string level, int x, int z);

	bool addObjectLoc(std::string level, vec3 pos);

	int size(std::string level);

	bool setTerrainDimensions(std::string level, std::string minx, std::string maxx, std::string minz, std::string maxz);

	float getTerrainMinX(std::string level);

	float getTerrainMaxX(std::string level);

	float getTerrainMinZ(std::string level);

	float getTerrainMaxZ(std::string level);

private:
	/// The objects map.
	std::map<std::string, std::vector<std::vector<int>>> objectLocations;
	/// Map of terrain min and max values for x and z
	std::map<std::string, std::map<std::string, float>> terrainMinMax;
};

