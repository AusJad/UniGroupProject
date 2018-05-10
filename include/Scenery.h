#pragma once

#include "GameObject.h"

class Scenery : public GameObject
{
public:
	Scenery(Identifiers & id, vec3 pos, ResourceList & list);
	Scenery();

	/**
	* @brief The update function.
	*
	* @param time - The system time.
	*/
	void update(float time);

	/**
	* @brief The render function.
	*/
	void render();

	/**
	* @brief Get the center offset.
	*
	* @return vec3 - The offset.
	*/
	vec3 getCenterOffset();
	
	/**
	* @brief A method to find if the object is collidable.
	*
	* @return bool - If the object was collidable.
	*/
	bool isCollidable();
};

