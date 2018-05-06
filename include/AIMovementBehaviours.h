#pragma once

#include "vec3.h"
#include <iostream>
#include "Maths.h"

#define M_PI 3.14159265358979323846

class AIMovementBehaviours
{
public:
	static vec3 Seek(const vec3 & self, const vec3 & target, float speed);
	static vec3 Flee(const vec3 & self, const vec3 & target, float speed);
	static vec3 Arrive(const vec3 & self, const vec3 & target, const vec3 & velocity, float maxspeed, float slowspeed, float mindistance);
	static vec3 Chase(const vec3 & self, const vec3 & target, const vec3 & selfvelocity, const vec3 & targetvelocity, const vec3 & selfheading, float selfspeed, float targetspeed);
	static float getDistance(const vec3 & self, const vec3 & target);
	static float faceTarget(const vec3 & self, const vec3 & target);
	static vec3 capSpeed(const vec3 & velocity, float maxspeed);
};

