#pragma once
#include "GameObject.h"

/**
* @class BMPLoader
* @brief Class for loading and saving BMP data.
*
* @author Morgan Smolder
* @version 01
* @date 14/04/2018
*/
class Bullet : public GameObject
{
public:
	Bullet();
	~Bullet() {};
	Bullet(Identifiers & id, vec3 pos, ResourceList & list);

	/**
	* @brief Update function for the bullet.
	*
	* @param time - System clock.
	*/
	void update(float time);

	/**
	* @brief Render function for the bullet.
	*/
	void render();

	/**
	* @brief Check function to see if the bullet should be visible.
	*
	* @return bool - If the bullet is visible or not.
	*/
	bool isVisible();

	/**
	* @brief Set the target position vector of the bullet.
	*
	* @param target - The new target position vector of the bullet.
	*/
	void setTarget(const vec3 target);

	void onCollide(vec3 & prevloc, const Identifiers & colgoid);

	bool hasGravity();

private:
	/// Flag for if the bullet is in use.
	bool inUse;
	/// Lifespan of the bullet.
	float lifespan;
	/// Time the bullet has been alive for.
	float timealive;
	/// Velocity of the bullet.
	float speed;
};

