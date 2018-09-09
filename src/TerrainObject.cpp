#include "TerrainObject.h"

TerrainObject::TerrainObject() : GameObject() {

}

TerrainObject::TerrainObject(Identifiers & id, vec3 pos, ResourceList & list) : GameObject(id, pos, list)
{
}


TerrainObject::~TerrainObject()
{
}

void TerrainObject::update(float time) {
	msgrcvr();
}


std::string TerrainObject::toString() {
	std::string ret;

	ret += "TERRAIN_START\n";
	ret += "NAME," + model->getName() + "\n";
	ret += "TERRAIN_END\n";

	return ret;
}

void TerrainObject::render() {
	if (model != NULL) {
		GameObject::model->render(pos);
	}
	else {
		RenderModuleStubb* tmp = Singleton<RenderModuleStubb>::getInstance();

		tmp->DrawQuad(point(pos.x(), pos.y() + 1), point(pos.x() + 1, pos.y()), pos.z());
	}
}

void TerrainObject::setModel(Model* M) {
	model = M;
	model->centerOnPoint(vec3(pos.x(), 0, pos.y()));
}

vec3 TerrainObject::getCenterOffset() {
	return vec3(0, 0, 0);
}

TerrainObject::TerrainObject(const TerrainObject & tocpy) : GameObject(tocpy) {

}

GameObject* TerrainObject::create() {
	return new TerrainObject(*this);
}