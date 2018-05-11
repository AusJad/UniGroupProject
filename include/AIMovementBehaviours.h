#pragma once

#include "vec3.h"
#include "Maths.h"
#include <iostream>
#include "Maths.h"

#define M_PI 3.14159265358979323846

/**
* @class AIMovementBehavious
* @brief Provides an interface for AI scripting.
*
* @author Morgan Smolder
* @version 01
* @date 08/05/2018
*/
class AIMovementBehaviours
{
public:
	/**
	* @brief The seek method for the AI.
	*
	* @param self - The position of the agent.
	* @param target - The position of the target.
	* @param speed - The speed of the agent.
	*
	* @return vec3 - The next position for the agent to move to.
	*/
	static vec3 Seek(const vec3 & self, const vec3 & target, float speed);

	/**
	* @brief The flee method for the AI.
	*
	* @param self - The position of the agent.
	* @param target - The position of the target.
	* @param speed - The speed of the agent.
	*
	* @return vec3 - The next position for the agent to move to.
	*/
	static vec3 Flee(const vec3 & self, const vec3 & target, float speed);

	/**
	* @brief When the agent does apon arrival at the target position.
	* 
	* @param self - The position of the agent.
	* @param target - The position of the target.
	* @param velocity - How fast the agent is traveling.
	* @param maxspeed - The max speed of the agent.
	* @param slowspeed - The min speed of the agent.
	* @param mindistance - The min distance the agent can be from the target before the goal is acheived.
	*
	* @return vec3 - The next position for the agent to move to.
	*/
	static vec3 Arrive(const vec3 & self, const vec3 & target, const vec3 & velocity, float maxspeed, float slowspeed, float mindistance);

	/**
	* @brief A method to get the AI to chase a target.
	*
	* @param self - The position of the agent.
	* @param target - The position of the target.
	* @param selfvelocity - The velocity of the agent.
	* @param targetvelocity - The velocity of the target.
	* @param selfheading - The direction the agent is heading in.
	* @param selfspeed - The speed of the agent.
	* @param targetspeed - The speed of the agent.
	*
	* @return vec3 - The next position for the agent to move to.
	*/
	static vec3 Chase(const vec3 & self, const vec3 & target, const vec3 & selfvelocity, const vec3 & targetvelocity, const vec3 & selfheading, float selfspeed, float targetspeed);

	/**
	* @brief A method to get the distance between two points.
	*
	* @param self - The first point.
	* @param target - The second point.
	*
	* @return float - The distance.
	*/
	static float getDistance(const vec3 & self, const vec3 & target);

	/**
	* @brief A method to get the angle the object must turn at to 'face' the target.
	*
	* @param self - The object that will move to 'face' the target.
	* @param target - The target to look at.
	*
	* @return float - The angle to rotate.
	*/
	static float faceTarget(const vec3 & self, const vec3 & target);

	/**
	* @brief A method to cap the velocity of a agent based on the max speed value.
	*
	* @param velocity - The current velocity of the agent.
	* @param maxspeed - The max speed the agent can go.
	*
	* @return vec3 - The new velocity vector.
	*/
	static vec3 capSpeed(const vec3 & velocity, float maxspeed);
};

