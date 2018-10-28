#pragma once
#include <map>
#include "vec2.h"
#include <iostream>

/**
* @class pathFinderGrid
* @brief Class for Storing object position data
*
* @author Mat De Vene
* @version 01
* @date 24/05/2018
*/

class pathFinderGrid
{
public:
	/**
	* @brief Constructor.
	*
	*/
	pathFinderGrid();
	/**
	* @brief Sets scaling of the grid.
	*
	* @param xmin, low boundary of x
	* @param xmax, high boundary of x
	* @param zmin, low boundary of z
	* @param zmax, high boundary of z
	*/
	bool setGridScale(int xmin, int xmax, int zmin, int zmax);
	/**
	* @brief Get the multiplier value for x, point to cell ratio
	*
	* @return float - The ratio for x
	*/
	float getGridMultiX() { return nodeMutliX; };
	/**
	* @brief Get the multiplier value for z, point to cell ratio
	*
	* @return float - The ratio for z
	*/
	float getGridMultiZ() { return nodeMultiZ; };
	/**
	* @brief flag a position as containing an object.
	*
	* @param id - The postion in the x, z plane to be flagged as containing an object.
	*/
	void greyOut(vec2 pos);
	/**
	* @brief check if a position has been flagged as containing an object.
	*
	* @return bool - The postion in the x, z plane to be flagged as containing an object.
	*/
	bool isGrey(vec2 pos);
	/**
	* @brief confirm that the cell to point scale has been set
	*
	* @return bool - Scale has or hasn't been set
	*/
	bool scaleSet() { return scaleisSet; };
private:
	///a map of maps to represent the grid
	std::map<int, std::map<int, int>> grid;
	/// smallest x on plane
	int xmin;
	/// smallest z on plane
	int zmin;
	/// biggest x on plane
	int xmax;
	/// biggest z on plane
	int zmax;
	/// scale has been set
	bool scaleisSet;
	/// cell to point multiplier - x
	float nodeMutliX;
	/// cell to point multiplier - z
	float nodeMultiZ;
};