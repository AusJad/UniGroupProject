#pragma once

#include <string>
#include "NPC.h"
#include "camera.h"
#include "ModelManger.h"
#include "Singleton.h"
#include "StaticEntity.h"
#include "TerrainObject.h"
#include "MenuObject.h"
#include "Bullet.h"
#include "Player.h"
#include "Scenery.h"

/**
* @class GameObjectFactory	
* @brief Class for handling the creation of game objects.
*
* @author Morgan Smolder
* @version 01
* @date 02/04/2018
*/
class GameObjectFactory
{
public:
	GameObjectFactory();

	/**
	* @brief Create a game object.
	*
	* @param id - The identifier for the object.
	* @param pos - The position for the object.
	* @param list - The resource list for the object.
	*
	* @return GameObject* - A pointer to the created game object.
	*/
	GameObject* create(Identifiers & id, vec3 pos, ResourceList & list);

	/// ID for the next object.
	unsigned nextid;
private:

	/**
	* @brief Set the model for the object.
	*
	* @param GO - A pointer to the game object.
	* @param model - The model data.
	*
	* @return bool - If the model was set.
	*/
	bool setModel(GameObject* & GO, std::string model);
};

