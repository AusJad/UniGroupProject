#include "ObjectLocList.h"
#include <stdio.h>

ObjectLocList::ObjectLocList()
{
}

ObjectLocList::ObjectLocList(std::string level, vec3 pos) {
	objectLocations[level].at(pos.x()).at(pos.z()) = 1;
}

bool ObjectLocList::at(std::string level, int x, int z) {
	return (objectLocations[level].at(x).at(z) == 1);
}

bool ObjectLocList::addObjectLoc(std::string level, vec3 pos) {
	
	if (objectLocations[level].at(pos.x()).at(pos.z()) = 1)
		return true;
	else
		return false;
}

int ObjectLocList::size(std::string level) {
	return objectLocations[level].capacity();
}

bool ObjectLocList::setTerrainDimensions(std::string level, std::string minx, std::string maxx, std::string minz, std::string maxz) {
	terrainMinMax[level][minx] = stof(minx);
	terrainMinMax[level][maxx] = stof(maxx);
	terrainMinMax[level][minz] = stof(minz);
	terrainMinMax[level][maxz] = stof(maxz);
	return true;
}

float ObjectLocList::getTerrainMinX(std::string level) {
	if (terrainMinMax[level].count("minx") == 0) { return -1; }
	else { return terrainMinMax[level]["minx"]; }
}

float ObjectLocList::getTerrainMaxX(std::string level) {
	if (terrainMinMax[level].count("maxx") == 0) { return -1; }
	else { return terrainMinMax[level]["maxx"]; }
}

float ObjectLocList::getTerrainMinZ(std::string level) {
	if (terrainMinMax[level].count("minz") == 0) { return -1; }
	else { return terrainMinMax[level]["minz"]; }
}

float ObjectLocList::getTerrainMaxZ(std::string level) {
	if (terrainMinMax[level].count("maxz") == 0 ){ return -1; }
	else { return terrainMinMax[level]["maxz"]; }
}



