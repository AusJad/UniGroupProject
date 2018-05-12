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

	const vec3 & getVelocity();

	const float & getHealth();

	void setVelocity(const vec3 & velocity);

	void setHealth(float health);

	void setSpeed(float speed);

	float getSpeed();

	void stop();

	bool NPCDefaultMessageHandler(Message & message);
	
	const vec3 & getHeading();

	void setHeading(const vec3 & heading);

	void setLAngle(float nangle);

private:
	vec3 velocity;
	vec3 heading;
	float lookangle;
	float health;
	float speed;
};

