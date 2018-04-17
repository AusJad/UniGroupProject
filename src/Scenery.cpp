#include "Scenery.h"



Scenery::Scenery(Identifiers & id, vec3 pos, ResourceList & list) : GameObject(id, pos, list)
{

}

Scenery::Scenery() : GameObject() {

}


void Scenery::render() {

	if (resources.hasResource("model") && model != NULL) GameObject::model->render(this->pos);
	else {
		RenderModuleStubb* tmp = Singleton<RenderModuleStubb>::getInstance();

		tmp->DrawQuad(point(pos.x(), pos.y() + 1), point(pos.x() + 1, pos.y()), pos.z());
	}
}

void Scenery::update(float time) {
	msgrcvr();
}

vec3 Scenery::getCenterOffset() {
	if (resources.hasResource("model") && model != NULL) {
		return vec3(0, abs(model->getMaxY()), 0);
	}

	return vec3(0, 0, 0);
}


bool Scenery::isCollidable() {
	return false;
}