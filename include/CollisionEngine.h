#pragma once

#include <map>
#include <vector>
//#include "vec3.h"
//#include "vec2.h"
#include "Maths.h"
#include "GameObject.h"
/**
* @struct HMPos
* @brief Struct for containing heightmap position data
*
* @author Morgan Smolder
* @version 01
* @date 02/04/2018
*/
struct HMPos {
	vec2 tl;
	vec2 br;
};

/**
* @struct AABB
* @brief Struct for containing AABB collider data
*
* @author Morgan Smolder
* @version 01
* @date 02/04/2018
*/
struct AABB {
	float xmin, ymin, zmin, xmax, ymax, zmax;
	AABB(float xmx, float xmn, float ymx, float ymn, float zmx, float zmn) : xmax(xmx), xmin(xmn), ymax(ymx), ymin(ymn), zmax(zmx), zmin(zmn) {};
	AABB() {};
};

/**
* @struct Ray
*
* @author Morgan Smolder
*/
struct Ray {
	vec3 origin;
	vec3 direction;
	Ray(vec3 o, vec3 d) : origin(o), direction(d) {};
	Ray() {};
};

/**
* @class CollisionEngine
* @brief Class for handling collision
*
* @author Morgan Smolder
* @version 01
* @date 02/04/2018
*/
class CollisionEngine
{
public:
	CollisionEngine();
	~CollisionEngine();

	/**
	* @brief Set the height map.
	*
	* @param toset - The new height map.
	*/
	void setHeightMap(std::vector<vec3> & toset);

	/**
	* @brief Update the collision.
	*
	* @param toupdate - The game object to be updated.
	* @param collGO - A vector of game objects for colliders
	* @param time - System time.
	*/
	void update(GameObject* toupdate, std::vector<GameObject*> collGO, float time);

	void update(GameObject* toupdate, GameObject* collGO, float time);

	static bool rayAABBTest(Ray & r, GameObject* collGO, vec3 & collpoint);

	physvec3 collisionResolver(physvec3 obj1LinearVelocity, physvec3 obj2LinearVelocity, physvec3 obj1AngularVelocity, physvec3 obj2AngularVelocity, float obj1Mass, float obj2Mass, physvec3 obj1R, physvec3 obj2R, physmat4 obj1InertiaTensor, physmat4 obj2InertiaTensor, physvec3 collisionVector);
	void updateAngularVelocity(GameObject* r1, GameObject* r2, physvec3 help, physvec3 collPt);
	void updateLinearVelocity(GameObject* r1, GameObject* r2, physvec3 help);


private:
	/// The height map data.
	std::map<float, std::map<float, float>> heightmap;

	/**
	* @brief Returns the height map location.
	*
	* @param pos - The position
	*
	* @return HMPos - The position of the height map.
	*/
	HMPos findHMLocation(const vec3 & pos);

	/**
	* @brief Generate a AABB collider.
	*
	* @param toupdate - The game object having the collider generated for.
	*
	* @return AABB - The collider.
	*/
	static AABB genAABB(GameObject* toupdate);

	/**
	* @brief Interpolate the y axis
	*
	* @param ppos - The first position vector.
	* @param pos - The second position vector.
	*
	* @return float - The interpolation.
	*/
	float interpolateY(const vec3 & ppos, HMPos & pos);

	/// Max and min values for the x and z axis.
	float maxx, minx, maxz, minz;

	/// If the object has a height map.
	bool hasHMap;
};

