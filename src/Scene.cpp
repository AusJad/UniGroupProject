#include "Scene.h"


Scene::Scene()
{
	objects.setWorldDimensions(-100, 100, 100, -100);
}


Scene::~Scene()
{
}

void Scene::render() {
	objects.render();
}

bool Scene::attachTerrain(Identifiers & id, vec3 pos, ResourceList & list) {
	return objects.addTerrain(id, pos, list);
}

bool Scene::addObject(Identifiers & id, vec3 pos, ResourceList & list){
	return objects.addObject(id, pos, list);
}

void Scene::update(float time) {
	objects.refreshTree();

	for (unsigned i = 0; i < objects.getNumObjects(); i++) {
		collision.update(objects.getObject(i), objects.findSpatiallyGroupedGameObjects(objects.getObject(i)), time);
	}

	objects.update(time);
}

int Scene::GetGameObjectID(std::string name) {
	return objects.GetGameObjectID(name);
}

GameObject* Scene::GetGameObject(std::string name) {
	return objects.GetGameObject(name);
}

bool Scene::setHeightMap(GameObject* hmObj) {
	if (hmObj == NULL) return false;
	if (hmObj->getModel() == NULL) return false;

	collision.setHeightMap(hmObj->getModel()->getVerticies());
	objects.setWorldDimensions(hmObj->getModel()->getMinX(), hmObj->getModel()->getMaxZ(), hmObj->getModel()->getMaxX(), hmObj->getModel()->getMinZ());
	return true;
}