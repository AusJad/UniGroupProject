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

int AIMovementBehaviours::calcH(AsNode & current, AsNode & target) {
	int h;
	int distancez = 0;
	int distancex = 0;

	if (current.x > target.x) {
		for (int i = target.x; i <= current.x; i++) {
			distancex++;
		}
	}
	else {
		for (int i = current.x; i <= target.x; i++) {
			distancex++;
		}
	}

	if (current.z > target.z) {
		for (int i = target.z; i <= current.z; i++) {
			distancez++;
		}
	}
	else {
		for (int i = current.z; i <= target.z; i++) {
			distancez++;
		}
	}

	h = distancex + distancez;
	h = h * current.g;
	return h;
}

std::stack<AsNode> AIMovementBehaviours::findPath(vec3 & current, vec3 & target, ObjectLocList & list, std::string level) {

	// SEEN 0
	// OPEN 1
	// CLOSED 2

	int minx = OBJLOCS->getTerrainMinX(level);
	int maxx = OBJLOCS->getTerrainMaxZ(level);
	int minz = OBJLOCS->getTerrainMinZ(level);
	int maxz = OBJLOCS->getTerrainMaxZ(level);

	AsNode cSquare;
	AsNode dSquare;
	std::stack<AsNode> path;

	//initialise and clamp to map size
	dSquare.x = (int)(target.x());
	if (dSquare.x > maxx)
		dSquare.x = maxx - 1;
	if (dSquare.x < minx)
		dSquare.x = minx + 1;
	dSquare.z = (int)(target.z());
	if (dSquare.z > maxz)
		dSquare.z = maxz - 1;
	if (dSquare.z < minz)
		dSquare.z = minz + 1;

	cSquare.parent = { -1,-1 };
	cSquare.g = 0;
	cSquare.h = calcH(cSquare, dSquare);
	cSquare.f = cSquare.g + cSquare.h;
	cSquare.x = (int)current.x();
	cSquare.z = (int)current.z();

	// SEEN 0
	// OPEN 1
	// CLOSED 2

	AsNode temp;
	std::unordered_map<int, std::unordered_map<int, AsNode> > seennodes;
	std::vector<indexpair> openlist;
	std::stack<AsNode> adjacentsquares;

	openlist.push_back({ cSquare.z, cSquare.x });
	seennodes[cSquare.z][cSquare.x] = cSquare;

	bool pathfound = false;

	unsigned currind;
	do {
		cSquare = seennodes.at(openlist.at(0).z).at(openlist.at(0).x);
		currind = 0;

		for (unsigned i = 1; i < openlist.size(); i++) {
			if (seennodes.at(openlist.at(i).z).at(openlist.at(i).x).f < cSquare.f)
			{
				currind = i;
				cSquare = seennodes.at(openlist.at(i).z).at(openlist.at(i).x);
			}
		}

		seennodes[cSquare.z][cSquare.x].status = CLOSED;

		openlist.erase(openlist.begin() + currind);

		if (list.size(level) > cSquare.x > (minx + 1)) {
			if (list.at(level, cSquare.x + 1, cSquare.z) == 1) {
				temp.x = cSquare.x + 1;
				temp.z = cSquare.z;
				temp.g = cSquare.g + 10;
				temp.h = calcH(temp, dSquare);
				temp.f = temp.g + temp.h;
				temp.parent = { cSquare.z, cSquare.x };
				adjacentsquares.push(temp);
			}
		}

		if (0 < cSquare.x) {
			if (list.at(level, cSquare.x - 1, cSquare.z) == 1) {
				temp.x = cSquare.x - 1;
				temp.z = cSquare.z;
				temp.g = cSquare.g + 10;
				temp.h = calcH(temp, dSquare);
				temp.f = temp.g + temp.h;
				temp.parent = { cSquare.z, cSquare.x };
				adjacentsquares.push(temp);
			}
		}

		if (list.size(level) - 1 > cSquare.z) {
			if (list.at(level, cSquare.x, cSquare.z + 1) == 1) {
				temp.x = cSquare.x;
				temp.z = cSquare.z + 1;
				temp.g = cSquare.g + 10;
				temp.h = calcH(temp, dSquare);
				temp.f = temp.g + temp.h;
				temp.parent = { cSquare.z, cSquare.x };
				adjacentsquares.push(temp);
			}
		}

		if (0 < cSquare.z) {
			if (list.at(level, cSquare.x, cSquare.z - 1) == 1) {
				temp.x = cSquare.x;
				temp.z = cSquare.z - 1;
				temp.g = cSquare.g + 10;
				temp.h = calcH(temp, dSquare);
				temp.f = temp.g + temp.h;
				temp.status = SEEN;
				temp.parent = { cSquare.z, cSquare.x };
				adjacentsquares.push(temp);
			}
		}

		if (0 < cSquare.z && list.size(level) - 1 > cSquare.x) {
			if (list.at(level, cSquare.x + 1, cSquare.z - 1) == 1) {
				temp.x = cSquare.x + 1;
				temp.z = cSquare.z - 1;
				temp.g = cSquare.g + 14;
				temp.h = calcH(temp, dSquare);
				temp.f = temp.g + temp.h;
				temp.parent = { cSquare.z, cSquare.x };
				adjacentsquares.push(temp);
			}
		}

		if (0 < cSquare.z && 0 < cSquare.x) {
			if (list.at(level, cSquare.x - 1, cSquare.z - 1) == 1) {
				temp.x = cSquare.x - 1;
				temp.z = cSquare.z - 1;
				temp.g = cSquare.g + 14;
				temp.h = calcH(temp, dSquare);
				temp.f = temp.g + temp.h;
				temp.parent = { cSquare.z, cSquare.x };
				adjacentsquares.push(temp);
			}
		}

		if (list.size(level) - 1 > cSquare.z && list.size(level) - 1 > cSquare.x) {
			if (list.at(level, cSquare.x + 1, cSquare.z + 1) == 1) {
				temp.x = cSquare.x + 1;
				temp.z = cSquare.z + 1;
				temp.g = cSquare.g + 14;
				temp.h = calcH(temp, dSquare);
				temp.f = temp.g + temp.h;
				temp.parent = { cSquare.z, cSquare.x };
				adjacentsquares.push(temp);
			}
		}

		if (list.size(level) - 1 > cSquare.z && 0 < cSquare.x) {
			if (list.at(level, cSquare.x - 1, cSquare.z + 1) == 1) {
				temp.x = cSquare.x - 1;
				temp.z = cSquare.z + 1;
				temp.g = cSquare.g + 14;
				temp.h = calcH(temp, dSquare);
				temp.f = temp.g + temp.h;
				temp.parent = { cSquare.z, cSquare.x };
				adjacentsquares.push(temp);
			}
		}

		while (!adjacentsquares.empty()) {
			if (seennodes.find(adjacentsquares.top().z) != seennodes.end()) {
				if (seennodes.at(adjacentsquares.top().z).find(adjacentsquares.top().x) != seennodes.at(adjacentsquares.top().z).end()) {
					if (seennodes.at(adjacentsquares.top().z).at(adjacentsquares.top().x).status == OPEN && seennodes.at(adjacentsquares.top().z).at(adjacentsquares.top().x).g > adjacentsquares.top().g) {
						seennodes.at(adjacentsquares.top().z).at(adjacentsquares.top().x).parent = adjacentsquares.top().parent;
						seennodes.at(adjacentsquares.top().z).at(adjacentsquares.top().x).g = cSquare.g + 10;
						seennodes.at(adjacentsquares.top().z).at(adjacentsquares.top().x).h = calcH(seennodes.at(adjacentsquares.top().z).at(adjacentsquares.top().x), dSquare);
						seennodes.at(adjacentsquares.top().z).at(adjacentsquares.top().x).f = seennodes.at(adjacentsquares.top().z).at(adjacentsquares.top().x).g + seennodes.at(adjacentsquares.top().z).at(adjacentsquares.top().x).h;
						openlist.push_back({ adjacentsquares.top().z, adjacentsquares.top().x });
					}
				}
			}

			if (seennodes.find(adjacentsquares.top().z) == seennodes.end()) {
				seennodes[adjacentsquares.top().z][adjacentsquares.top().x] = adjacentsquares.top();
				seennodes[adjacentsquares.top().z][adjacentsquares.top().x].status = OPEN;
				openlist.push_back({ adjacentsquares.top().z, adjacentsquares.top().x });
			}
			else
				if (seennodes.at(adjacentsquares.top().z).find(adjacentsquares.top().x) == seennodes.at(adjacentsquares.top().z).end()) {
					seennodes[adjacentsquares.top().z][adjacentsquares.top().x] = adjacentsquares.top();
					seennodes[adjacentsquares.top().z][adjacentsquares.top().x].status = OPEN;
					openlist.push_back({ adjacentsquares.top().z, adjacentsquares.top().x });
				}

			adjacentsquares.pop();
		}

		if (seennodes.find(dSquare.z) != seennodes.end()) {
			if (seennodes.at(dSquare.z).find(dSquare.x) != seennodes.at(dSquare.z).end()) {
				pathfound = true;
			}
		}

	} while (!pathfound && !openlist.empty());

	if (!openlist.empty()) {
		indexpair parent = seennodes.at(dSquare.z).at(dSquare.x).parent;

		while (parent.z != -1)
		{
			path.push(seennodes.at(parent.z).at(parent.x));
			parent = path.top().parent;
		}

		if (!path.empty()) path.pop();
	}
	return path;
}

