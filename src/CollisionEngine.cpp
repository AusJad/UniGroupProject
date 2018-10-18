#include "CollisionEngine.h"

CollisionEngine::CollisionEngine()
{
	hasHMap = false;
}

CollisionEngine::~CollisionEngine()
{
}

void CollisionEngine::setHeightMap(std::vector<vec3> & toset) {
	
	heightmap.clear();
	if (toset.empty()) { hasHMap = false; return; }

	std::map<float, float> tmp;

	maxx = toset.at(0).x();
	minx = toset.at(0).x();
	maxz = toset.at(0).z();
	minz = toset.at(0).z();

	for (unsigned i = 0; i < toset.size(); i++) {
		if (heightmap.count(toset.at(i).x()) == 0) heightmap[ toset.at(i).x()] = tmp;
		heightmap[toset.at(i).x()][toset.at(i).z()] = toset.at(i).y();
		if(toset.at(i).x() > maxx){
			maxx = toset.at(i).x();
		}
		if (toset.at(i).z() > maxz) {
			maxz = toset.at(i).z();
		}
		if (toset.at(i).x() < minx) {
			minx = toset.at(i).x();
		}
		if (toset.at(i).z() < minz) {
			minz = toset.at(i).z();
		}
	}

	//minx += 1000;
	//maxx -= 1000;
	//minz += 1000;
	//maxz -= 1000;

	hasHMap = true;
}

void CollisionEngine::update(GameObject* toupdate, std::vector<GameObject*> collGO, float time) {
	if (toupdate->isCollidable() == false) {
		vec3 tmpos = toupdate->getPos();
		
		toupdate->update(time);

		float x = toupdate->getPos().x();
		float z = toupdate->getPos().z();

		if ((x < maxx && x > minx && z > minz && z < maxz) == false) {
			//toupdate->setPos(tmpos);
			//toupdate->stop();
		}

		return;
	}

	vec3 tmpos = toupdate->getPos();

	toupdate->update(time);

	AABB updateb = genAABB(toupdate);

	AABB compb;

	for (unsigned i = 0; i < collGO.size(); i++) {
		if (collGO.at(i)->getID() != toupdate->getID() && collGO.at(i)->isCollidable()) {
			if (toupdate->hasMultiObb() && collGO.at(i)->hasOBB()) {
				//std::cout << "Multi vs Single\n" << std::endl;
				for (int i = 0; i < toupdate->getNumOBBs(); i++) {
					if (OBBOBB(toupdate->getOBB(i), collGO.at(i)->getOBB())) {
						CollisionManifold coll = FindCollisionFeatures(toupdate->getOBB(i), collGO.at(i)->getOBB());
						if (coll.colliding) {
							toupdate->onCollide(collGO.at(i), coll);
							//toupdate->onCollide2(tmpos, collGO.at(i)->getPos()); // onCollide2() is from NPC and no longer used
						}
					}
				}
			}
			else if (toupdate->hasMultiObb() && collGO.at(i)->hasMultiObb()) {
				//std::cout << "Multi vs Multi\n" << std::endl;
				for (int i = 0; i < toupdate->getNumOBBs(); i++) {
					for (int k = 0; k < collGO.at(i)->getNumOBBs(); k++) {
						if (OBBOBB(toupdate->getOBB(i), collGO.at(i)->getOBB(k))) {
							CollisionManifold coll = FindCollisionFeatures(toupdate->getOBB(i), collGO.at(i)->getOBB(k));
							if (coll.colliding) {
								toupdate->onCollide(collGO.at(i), coll);
								//toupdate->onCollide2(tmpos, collGO.at(i)->getPos());
							}
						}
					}
				}
			}
			else if (toupdate->hasOBB() && collGO.at(i)->hasMultiObb()) {
				//std::cout << "Single vs Multi\n" << std::endl;
					for (int k = 0; k < collGO.at(i)->getNumOBBs(); k++) {
						if (OBBOBB(toupdate->getOBB(), collGO.at(i)->getOBB(k))) {
							CollisionManifold coll = FindCollisionFeatures(toupdate->getOBB(), collGO.at(i)->getOBB(k));
							if (coll.colliding) {
								toupdate->onCollide(collGO.at(i), coll);
								//toupdate->onCollide2(tmpos, collGO.at(i)->getPos());
							}
						}
					}
			}
			else if (toupdate->hasOBB() && collGO.at(i)->hasOBB()) {
				//std::cout << "Single vs Single\n" << std::endl;
				if (OBBOBB(toupdate->getOBB(), collGO.at(i)->getOBB())) {
					CollisionManifold coll = FindCollisionFeatures(toupdate->getOBB(), collGO.at(i)->getOBB());
					if (coll.colliding) {
						toupdate->onCollide(collGO.at(i), coll);
						//toupdate->onCollide(tmpos, collGO.at(i)->getIdentifiers());
						//toupdate->onCollide2(tmpos, collGO.at(i)->getPos());
					}
				}
			}
			else {
				compb = genAABB(collGO.at(i));
				if (updateb.xmax >= compb.xmin && updateb.xmin <= compb.xmax
					&& updateb.zmax >= compb.zmin && updateb.zmin <= compb.zmax
					&& updateb.ymax >= compb.ymin && updateb.ymin <= compb.ymax) {
					toupdate->onCollidehm(tmpos, collGO.at(i)->getIdentifiers());
					//toupdate->onCollide2(tmpos, collGO.at(i)->getPos());
				}
			}
		}
	}

	if (hasHMap) {
		float x = toupdate->getPos().x();
		float z = toupdate->getPos().z();

		if ((x < maxx && x > minx && z > minz && z < maxz) == false) {
			//toupdate->setPos(tmpos);
			//toupdate->stop();
			if (toupdate->getIdentifiers().getType() == "BLT") toupdate->onCollidehm(tmpos, Identifiers("NAN"));
		}

		if (x < maxx && x > minx && z > minz && z < maxz && hasHMap && toupdate->hasGravity()) {
			HMPos hmloc = findHMLocation(toupdate->getPos());

			float y = interpolateY(toupdate->getPos(), hmloc);

			toupdate->setPos(vec3(toupdate->getPos().x(), y + toupdate->getCenterOffset().y(), toupdate->getPos().z()));
			toupdate->setTarget(vec3(toupdate->getTarget().x(), 0, toupdate->getTarget().z()));
		}
		else {
			if (x < maxx && x > minx && z > minz && z < maxz && hasHMap) {
				HMPos hmloc = findHMLocation(toupdate->getPos());

				float y = interpolateY(toupdate->getPos(), hmloc);

				if(toupdate->getPos().y() < y)  toupdate->onCollidehm(tmpos, Identifiers("NAN"));
			}
		}
	}
}

void CollisionEngine::update(GameObject* toupdate, GameObject* collGO, float time) {
	if (toupdate->isCollidable() == false) {
		vec3 tmpos = toupdate->getPos();
		toupdate->update(time);

		float x = toupdate->getPos().x();
		float z = toupdate->getPos().z();

		if ((x < maxx && x > minx && z > minz && z < maxz) == false) {
			toupdate->setPos(tmpos);
			toupdate->stop();
		}

		return;
	}

	vec3 tmpos = toupdate->getPos();

	toupdate->update(time);

	AABB updateb = genAABB(toupdate);

	AABB compb;

	if (collGO->getID() != toupdate->getID() && collGO->isCollidable()) {
		compb = genAABB(collGO);
		if (updateb.xmax >= compb.xmin && updateb.xmin <= compb.xmax
			&& updateb.zmax >= compb.zmin && updateb.zmin <= compb.zmax
			&& updateb.ymax >= compb.ymin && updateb.ymin <= compb.ymax) {
			toupdate->onCollidehm(tmpos, collGO->getIdentifiers());
			//toupdate->onCollide2(tmpos, collGO->getPos());
		}
	}

	if (hasHMap) {
		float x = toupdate->getPos().x();
		float z = toupdate->getPos().z();

		if ((x < maxx && x > minx && z > minz && z < maxz) == false) {
			toupdate->setPos(tmpos);
			toupdate->stop();
			if (toupdate->getIdentifiers().getType() == "BLT") toupdate->onCollidehm(tmpos, Identifiers("NAN"));
		}

		if (x < maxx && x > minx && z > minz && z < maxz && hasHMap && toupdate->hasGravity()) {
			HMPos hmloc = findHMLocation(toupdate->getPos());

			float y = interpolateY(toupdate->getPos(), hmloc);

			toupdate->setPos(vec3(toupdate->getPos().x(), y + toupdate->getCenterOffset().y(), toupdate->getPos().z()));
			toupdate->setTarget(vec3(toupdate->getTarget().x(), 0, toupdate->getTarget().z()));
		}
		else {
			if (x < maxx && x > minx && z > minz && z < maxz && hasHMap) {
				HMPos hmloc = findHMLocation(toupdate->getPos());

				float y = interpolateY(toupdate->getPos(), hmloc);

				if (toupdate->getPos().y() < y)  toupdate->onCollidehm(tmpos, Identifiers("NAN"));
			}
		}
	}
}

AABB CollisionEngine::genAABB(GameObject* toupdate) {
	if (toupdate->getModel() == NULL) 
		return AABB(toupdate->getPos().x() + 7.0f, toupdate->getPos().x() - 7.0f,
			toupdate->getPos().y() + 7.0f, toupdate->getPos().y() - 30.0f,
			toupdate->getPos().z() + 7.0f, toupdate->getPos().z() - 7.0f);
	else 
		return AABB(toupdate->getModel()->getMaxTX(), toupdate->getModel()->getMinTX(),
		toupdate->getModel()->getMaxTY(), toupdate->getModel()->getMinTY(),
		toupdate->getModel()->getMaxTZ(), toupdate->getModel()->getMinTZ());
}

HMPos CollisionEngine::findHMLocation(const vec3 & pos) {
	std::map<float, std::map<float, float> >::iterator mapit1 = heightmap.lower_bound(pos.x());
	float tmpky1upr = mapit1->first;
	mapit1--;
	float tmpk1lwr = mapit1->first;

	std::map<float, float>::iterator mapit2 = heightmap.at(tmpky1upr).lower_bound(pos.z());
	float tmpky2upr = mapit2->first;
	mapit2--;
	float tmpk2lwr = mapit2->first;

	HMPos tmp;
	tmp.tl = vec2(tmpky1upr, tmpk2lwr);
	tmp.br = vec2(tmpk1lwr, tmpky2upr);

	return tmp;
}

float CollisionEngine::interpolateY(const vec3 & ppos, HMPos & pos) {
	float y00 = heightmap.at(pos.br.x()).at(pos.tl.y());
	float y01 = heightmap.at(pos.tl.x()).at(pos.tl.y());;
	float y10 = heightmap.at(pos.br.x()).at(pos.br.y());;
	float y11 = heightmap.at(pos.tl.x()).at(pos.br.y());;

	float y1 = ((pos.tl.x() - ppos.x())/(pos.tl.x() - pos.br.x()))*y00 + ((ppos.x() - pos.br.x())/(pos.tl.x() - pos.br.x()))*y01;
	float y2 = ((pos.tl.x() - ppos.x()) / (pos.tl.x() - pos.br.x()))*y10 + ((ppos.x() - pos.br.x()) / (pos.tl.x() - pos.br.x()))*y11;

	float fy = ((pos.br.y() - ppos.z()) / (pos.br.y() - pos.tl.y()))* y1 + ((ppos.z() - pos.tl.y()) / (pos.br.y() - pos.tl.y()))* y2;

	return fy;
}

/*
	Adapted from algorithm found at this url:
	https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-box-intersection
*/
bool CollisionEngine::rayAABBTest(Ray & r, GameObject* collGO, vec3 & collpoint) {
	float tmp;

	AABB bounds = genAABB(collGO);

	float tmin = (bounds.xmin - r.origin.x()) / r.direction.x();
	float tmax = (bounds.xmax - r.origin.x()) / r.direction.x();

	if (tmin > tmax) {
		tmp = tmin;
		tmin = tmax;
		tmax = tmp;
	}

	float tymin = (bounds.ymin - r.origin.y()) / r.direction.y();
	float tymax = (bounds.ymax - r.origin.y()) / r.direction.y();

	if (tymin > tymax) {
		tmp = tymax;
		tymax = tymin;
		tymin = tmp;
	}

	if ((tmin > tymax) || (tymin > tmax))
		return false;

	if (tymin > tmin)
		tmin = tymin;

	if (tymax < tmax)
		tmax = tymax;

	float tzmin = (bounds.zmin - r.origin.z()) / r.direction.z();
	float tzmax = (bounds.zmax - r.origin.z()) / r.direction.z();

	if (tzmin > tzmax) {
		tmp = tzmin;
		tzmin = tzmax;
		tzmax = tmp;
	}

	if ((tmin > tzmax) || (tzmin > tmax))
		return false;

	if (tzmin > tmin)
		tmin = tzmin;

	if (tzmax < tmax)
		tmax = tzmax;
	
	collpoint = r.direction * tmin;
	
	return true;

}