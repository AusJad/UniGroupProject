#include "Scene.h"


Scene::Scene()
{
	objects.setWorldDimensions(-100, 100, 100, -100);
}


Scene::~Scene()
{
}

void Scene::addResources(ResourceList & toadd) {
	resources = toadd;
}

void Scene::render() {
	objects.render();
	if (resources.hasResource("renderfunc")) {
		RNDR->RenderFacingCamera();
		LSM->callFunction<Scene, MessagingBus>(resources.getResource("renderfunc"), *this, *(Singleton<MessagingBus>::getInstance()));
		RNDR->StopRenderFacingCamera();
	}
}

bool Scene::attachTerrain(Identifiers & id, vec3 pos, ResourceList & list) {
	return objects.addTerrain(id, pos, list);
}

bool Scene::addObject(Identifiers & id, vec3 pos, ResourceList & list){
	return objects.addObject(id, pos, list);
}

void Scene::update(float time) {
	if (resources.hasResource("updatefunc")) {
		LSM->callFunction<Scene, MessagingBus>(resources.getResource("updatefunc"), *this, *(Singleton<MessagingBus>::getInstance()));
	}

	objects.refreshTree();

	for (unsigned i = 0; i < objects.getNumObjects(); i++) {
		if(objects.getObject(i) != NULL) collision.update(objects.getObject(i), objects.findSpatiallyGroupedGameObjects(objects.getObject(i)), time);
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

//mm
std::vector<std::string> Scene::saveGame()
{
	std::vector<std::string> s;

	for (unsigned i = 0; i < objects.getNumObjects(); i++)
	{
		if (!objects.getObject(i)->getIdentifiers().getName().empty()) // Only want named objects
		{
			s.push_back(objects.getObject(i)->toString());
		}
	}

	return s;
}

void Scene::loadGame(save sf)
{
	for (unsigned i = 0; i < objects.getNumObjects(); i++)
	{
		for (unsigned j = 0; j < sf.getData().size(); j++)
		{
			if (objects.getObject(i)->getIdentifiers().getName() == sf.getData()[j].substr(0, sf.getData()[j].find(','))) // First attribute is name
			{
				sf.getData()[j].erase(0, sf.getData()[j].find(',') + 1); // Erase the object name
				objects.getObject(i)->fromstring(sf.getData()[j]); // Pass in only data
			}
		}
	}
}