#include "StaticEntity.h"

StaticEntity::StaticEntity() : GameObject() {

}

StaticEntity::StaticEntity(Identifiers & id, vec3 pos, ResourceList & list) : GameObject(id, pos, list)
{
}


StaticEntity::~StaticEntity()
{
}

StaticEntity::StaticEntity(const StaticEntity & tocpy) : GameObject(tocpy) {};

GameObject* StaticEntity::create() {
	return new StaticEntity(*this);
}

void StaticEntity::update(float time) {
	msgrcvr();
}

void StaticEntity::render() {
	if (resources.hasResource("model") && model != NULL) GameObject::model->render(pos);
	else {
		RenderModuleStubb* tmp = Singleton<RenderModuleStubb>::getInstance();

		tmp->DrawQuad(point(pos.x(), pos.y() + 1), point(pos.x() + 1, pos.y()), pos.z());
	}
}

vec3 StaticEntity::getCenterOffset() {
	if (resources.hasResource("model") && model != NULL) {
		return vec3(0, abs(model->getMaxY()), 0);
	}

	return vec3(0, 0, 0);
}