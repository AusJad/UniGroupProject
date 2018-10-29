#pragma once
#include <SimpleStack.h>
#include <vector>
#include <vec2.h>
#include <GameObject.h>
#include <unordered_map>

#define SEEN 0
#define OPEN 1
#define CLOSED 2

/**
* @class pathFinder
* @brief Class for Storing object position data
*
* @author Mat De Vene
* @version 01
* @date 24/05/2018
*/

/**
* @struct indexpair
* @brief Struct for holding cell position 
*
* @author Mat De Vene
* @version 01
* @date 24/05/2018
*/
struct indexpair {
	indexpair(int nz, int nx) : x(nx), z(nz) {};
	int x;
	int z;
};

/**
* @struct pair
* @brief Struct for holding A star node attributes
*
* @author Mat De Vene
* @version 01
* @date 24/05/2018
*/
struct AsNode {
	AsNode() : f(0), g(0), h(0), x(0), z(0), parent(-1, -1), status(SEEN) {};
	AsNode(int nx, int nz) : f(0), g(0), h(0), x(nx), z(nz), parent(-1, -1), status(SEEN) {};
	int f;
	int g;
	int h;
	int x;
	int z;
	indexpair parent;
	int status;
};

class pathFinder
{
public:
	/**
	* @brief Constructor.
	*
	*/
	pathFinder();
	/**
	* @brief returnes a SimpleStack of waypoints
	*
	* @param objects, A vector of game objects
	* @param pos, requesting entities position
	* @param target, the position of the target
	*/
	//mmpf -- made static
	static SimpleStack findpath(std::vector<GameObject*> & objects, vec3 pos, vec3 target);

private:
	/**
	* @brief returnes a variation of pythagoris theorem to compare distances from a cell to the target
	*
	* @param start, The potential start cell
	* @param target, The target cell
	*/
	static int calcH(AsNode & start, AsNode & target);
};

