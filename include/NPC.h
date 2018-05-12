#pragma once
#include "GameObject.h"
#include <iostream>
#include "AudioEngine.h"

/**
* @class NPC
* @brief Class for creating NPCs
*
* @author Morgan Smolder
* @version 01
* @date 02/04/2018
*/
class NPC : public GameObject
{
public:
	NPC(Identifiers & id, vec3 pos, ResourceList & list);
	NPC();
	~NPC();
	NPC(const NPC & tocpy);

	GameObject* create();

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
	* @brief Get the NPCs velocity.
	* 
	* @return vec3 - The velocity.
	*/
	const vec3 & getVelocity();

	/**
	* @brief Get the NPCs health.
	*
	* @return float - The health.
	*/
	const float & getHealth();

	/**
	* @brief Set the NPCs velocity.
	*
	* @param velocity - The new velocity.
	*/
	void setVelocity(const vec3 & velocity);

	/**
	* @brief Set the health of the NPC.
	*
	* @param health - The new health of the NPC.
	*/
	void setHealth(float health);

	/**
	* @brief Set the speed of the NPC.
	*
	* @param speed - The new speed of the NPC.
	*/
	void setSpeed(float speed);

	/**
	* @brief Get the speed of the NPC.
	*
	* @return float - The speed of the NPC.
	*/
	float getSpeed();

	/**
	* @brief A method to make the NPC stop what its doing.
	*/
	void stop();

	/**
	* @brief A default message handler method.
	*
	* @param message - The message.
	*
	* @return bool - If the message was processed.
	*/
	bool NPCDefaultMessageHandler(Message & message);
	
	/**
	* @brief Get the heading position.
	*
	* @return vec3 - The heading position.
	*/
	const vec3 & getHeading();

	/**
	* @brief Set the heading position.
	*
	* @param heading - The new heading position.
	*/
	void setHeading(const vec3 & heading);

	/**
	* @brief Set the l angle.
	*
	* @param nangle - The new angle.
	*/
	void setLAngle(float nangle);

	//mm
	/**
	* @brief Set the NPC data to a string.
	*
	* @return string - The NPC data.
	*/
	std::string toString();

	/**
	* @brief Set the NPC data from a string.
	*
	* @param toread - The string being parsed.
	*
	* @return bool - If the data loaded.
	*/
	bool fromstring(std::string toread);

private:
	/// Velocity of the NPC.
	vec3 velocity;
	/// The heading of the NPC.
	vec3 heading;
	/// The look angle of the NPC.
	float lookangle;
	/// The health of the NPC.
	float health;
	/// The speed of the NPC.
	float speed;
};

