#include "AIMovementBehaviours.h"

vec3 AIMovementBehaviours::Seek(const vec3 & self, const vec3 & target, float speed) {
	vec3 steeringforce = vec3(target) - self;
	steeringforce.normailse();
	steeringforce *= speed;
	
	return steeringforce;
}

vec3 AIMovementBehaviours::Flee(const vec3 & self, const vec3 & target, float speed) {
	vec3 steeringforce = vec3(self) - target;
	steeringforce.normailse();
	steeringforce *= speed;

	return steeringforce;
}

vec3 AIMovementBehaviours::Arrive(const vec3 & self, const vec3 & target, const vec3 & velocity, float maxspeed, float slowspeed, float mindistance) {
	vec3 targetoffset = vec3(target) - self;
	
	float distance = getDistance(self, target);

	if (distance > mindistance) {
		float decelspeed = distance / slowspeed * 0.1f;

		if (decelspeed > maxspeed) decelspeed = maxspeed;
		if (decelspeed < -maxspeed) decelspeed = -maxspeed;

		vec3 steeringforce = targetoffset * decelspeed / distance;

		return steeringforce - velocity;
	}

	return vec3();
}

vec3 AIMovementBehaviours::Chase(const vec3 & self, const vec3 & target, const vec3 & selfvelocity, const vec3 & targetvelocity, const vec3 & selfheading, float selfspeed, float targetspeed) {
	vec3 targetoffset = vec3(target) - self;

	vec3 targetheading = targetvelocity;
	targetheading.normailse();

	float relativeheading = vec3(selfheading).dot(targetheading);

	if (targetoffset.dot(selfheading) > 0 && relativeheading < -0.95) {
		return Seek(self, target, selfspeed);
	}

	float lookahead = getDistance(self, target) / (selfspeed + targetspeed);

	return Seek(self, vec3(target) + vec3(targetvelocity) * lookahead, selfspeed);
}

float AIMovementBehaviours::getDistance(const vec3 & self, const vec3 & target) {
	float total = 0;
	total += abs(self.x() - target.x());
	total += abs(self.z() - target.z());

	return total;
}

vec3 AIMovementBehaviours::capSpeed(const vec3 & velocity, float maxspeed) {
	vec3 nvec = velocity;

	if (velocity.x() > maxspeed) nvec.sx(maxspeed);
	if (velocity.x() < -maxspeed) nvec.sx(-maxspeed);
	if (velocity.y() > maxspeed) nvec.sy(maxspeed);
	if (velocity.y() < -maxspeed) nvec.sy(-maxspeed);
	if (velocity.z() > maxspeed) nvec.sz(maxspeed);
	if (velocity.z() < -maxspeed) nvec.sz(-maxspeed);

	return nvec;
}

float AIMovementBehaviours::faceTarget(const vec3 & self, const vec3 & target) {
	vec3 direction = Maths::normalize(target.getVec() - self.getVec());
	float angle = (float) (180 / M_PI) * atan2f(direction.x(), direction.z()) - 90;
	if (angle < 0) { angle += 360; }
	return angle;
}
