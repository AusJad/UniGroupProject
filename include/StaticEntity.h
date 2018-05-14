#pragma once

#include "GameObject.h"

/**
* @class StaticEntity
* @brief Class for creating a static entity and updating, rendering and getting the offset vector for it
*
* @author Morgan Smolder
* @version 01
* @date 02/04/2018
*/
class StaticEntity : public GameObject
{
public:
	StaticEntity(Identifiers & id, vec3 pos, ResourceList & list);
	StaticEntity();
	~StaticEntity();
	StaticEntity(const StaticEntity & tocpy);

	GameObject* create();

	/**
	* @brief The update function.
	*
	* @param time - The system clock.
	*/
	void update(float time);

	/**
	* @brief The render function.
	*/
	void render();

	/**
	* @brief Get the center offset vector.
	*
	* @return vec3 - The offset vector.
	*/
	vec3 getCenterOffset();
};

