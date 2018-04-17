#include "CollisionEngine.h"

CollisionEngine::CollisionEngine()
{
	hasHMap = false;
}

CollisionEngine::~CollisionEngine()
{
}

void CollisionEngine::setHeightMap(std::vector<vec3> & toset) {
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

	hasHMap = true;
}


//CollGO - vector of object pointers it is possible for the current entity to collide with
//Taken from the quad tree
void CollisionEngine::update(GameObject* & toupdate, std::vector<GameObject*> collGO, float time) {
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

	for (unsigned i = 0; i < collGO.size(); i++) {
		if (collGO.at(i)->getID() != toupdate->getID() && collGO.at(i)->isCollidable()) {
			compb = genAABB(collGO.at(i));
			if (updateb.xmax >= compb.xmin && updateb.xmin <= compb.xmax
				&& updateb.zmax >= compb.zmin && updateb.zmin <= compb.zmax) {
				toupdate->setPos(tmpos);
				toupdate->stop();
			}
		}
	}

	if (hasHMap) {
		float x = toupdate->getPos().x();
		float z = toupdate->getPos().z();

		if ((x < maxx && x > minx && z > minz && z < maxz) == false) {
			toupdate->setPos(tmpos);
			toupdate->stop();
		}

		if (x < maxx && x > minx && z > minz && z < maxz && hasHMap) {
			HMPos hmloc = findHMLocation(toupdate->getPos());

			float y = interpolateY(toupdate->getPos(), hmloc);

			toupdate->setPos(vec3(toupdate->getPos().x(), y + toupdate->getCenterOffset().y(), toupdate->getPos().z()));
			toupdate->setTarget(vec3(toupdate->getTarget().x(), 0, toupdate->getTarget().z()));
		}
	}
}

AABB CollisionEngine::genAABB(GameObject* toupdate) {
	if (toupdate->getModel() == NULL) 
		return AABB(toupdate->getPos().x() + 7.0f, toupdate->getPos().x() - 7.0f,
			toupdate->getPos().y() + 7.0f, toupdate->getPos().y() - 7.0f,
			toupdate->getPos().z() + 7.0f, toupdate->getPos().z() - 7.0f);
	else 
		return AABB(toupdate->getModel()->getMaxX(), toupdate->getModel()->getMinX(),
		toupdate->getModel()->getMaxY(), toupdate->getModel()->getMinY(),
		toupdate->getModel()->getMaxZ(), toupdate->getModel()->getMinZ());
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
