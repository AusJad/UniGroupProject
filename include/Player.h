#pragma once

#include "GameObject.h"
#include "LUAScriptManager.h"

/**
* @class NPC
* @brief Class for creating NPCs
*
* @author Morgan Smolder
* @version 01
* @date 15/04/2018
*/
class Player : public GameObject
{
public:
	Player(Identifiers & id, vec3 pos, ResourceList & list);
	Player();
	Player(const Player & tocpy);

	GameObject* create();

	/**
	* @brief Update the player object.
	* 
	* @param time - The system time.
	*/
	void update(float time);

	/**
	* @brief Render the player object.
	*/
	void render();

	/**
	* @brief Get the center offset vector of the player.
	*
	* @return vec3 - The center offset vector of the player.
	*/
	vec3 getCenterOffset();

	/**
	* @brief Find out if the player is collidable.
	* 
	* @return bool - If the player is collidable or not.
	*/
	bool isCollidable();

	/**
	* @brief Draw the player model.
	*
	* @param trans - The translation matrix.
	* @param rot - The rotation value.
	*/
	void drawModel(vec3 & trans, float rot);

	/**
	* @brief Get the front.
	*
	* @return vec3 - The front postion.
	*/
	const vec3 & getFront();

	/**
	* @brief The default message handler.
	*
	* @param tocheck - The message.
	*
	* @return bool - If the message was handled.
	*/
	bool playerDefaultMessageHandler(Message & tocheck);
	
	// mm
	/**
	* @brief A method to output player data as a string.
	*
	* @return string - Player data.
	*/
	std::string toString();

	/**
	* @brief A method to parse a string and set player data.
	*
	* @param toread - The string to be parsed.
	*
	* @return bool - If the string was parsed.
	*/
	bool fromstring(std::string toread);

	void setHealth(float nh);
	void setAmmo(int na);
	float getHealth();
	int getAmmo();

private:
	/// The direction the player should be facing.
	vec3 front;

	float health;

	int ammo;
};

