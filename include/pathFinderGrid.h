#pragma once
#include <map>
#include "vec2.h"
#include <iostream>

class pathFinderGrid
{
public:
	pathFinderGrid();
	bool setGridScale(int xmin, int xmax, int zmin, int zmax);
	float getGridMultiX() { return nodeMutliX; };
	float getGridMultiZ() { return nodeMultiZ; };
	void greyOut(vec2 pos);
	bool isGrey(vec2 pos);
	bool scaleSet() { return scaleisSet; };
private:
	std::map<int, std::map<int, bool>> grid;
	int xmin;
	int zmin;
	int xmax;
	int zmax;
	bool scaleisSet;
	float nodeMutliX;
	float nodeMultiZ;
};