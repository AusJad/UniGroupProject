#include "Scene.h"


Scene::Scene()
{
	objects.setWorldDimensions(-100, 100, 100, -100);
	state = -1;
}


Scene::~Scene()
{
}


int Scene::getState() {
	return state;
}

void Scene::setState(int state) {
	this->state = state;
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
		//While game objects are never deleted, thay do go inactive
		//GameObjectHandler returns NULL if an inactive object is requested
		//So we must check for this (root of your "saving the game with dead enimies" issue)
		if (objects.getObject(i) != NULL) {
			if (!objects.getObject(i)->getIdentifiers().getName().empty()) // Only want named objects
			{
				s.push_back(objects.getObject(i)->toString());
			}
		}
	}

	return s;
}

void Scene::loadGame(save sf)
{
	bool match;

	for (unsigned j = 0; j < sf.getData().size(); j++){
		match = false;
		//Loop until match is found (saves redudant searching)
		for (unsigned i = 0; i < objects.getNumObjects() && !match; i++)
		{
			//While game objects are never deleted, thay do go inactive
			//GameObjectHandler returns NULL if an inactive object is requested
			//So we must check for this (root of your "game crashes when loading file with lots of bullets and such" issue)
			if (objects.getObject(i) != NULL) {
				if (objects.getObject(i)->getIdentifiers().getName() == sf.getData()[j].substr(0, sf.getData()[j].find(','))) // First attribute is name
				{
					match = true;
					sf.getData()[j].erase(0, sf.getData()[j].find(',') + 1); // Erase the object name
					objects.getObject(i)->fromstring(sf.getData()[j]); // Pass in only data
				}
			}
		}
	}
}