#include "Scene.h"


Scene::Scene()
{
	objects.setWorldDimensions(-100, 100, 100, -100);
	state = -1;
	loaded = false;
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
	CAM->getActiveCam()->render();

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

void Scene::addObject(GameObject * toadd) {
	objects.addGameObject(toadd);
}

void Scene::update(float time) {
	if (resources.hasResource("updatefunc")) {
		LSM->callFunction<Scene, MessagingBus>(resources.getResource("updatefunc"), *this, *(MSGBS));
	}

	for (unsigned i = 0; i < objects.getNumObjects(); i++) {
		if(objects.getObject(i) != NULL)
			if(!objects.getObject(i)->isStatic()) collision.update(objects.getObject(i), objects.findSpatiallyGroupedGameObjects(objects.getObject(i)), time);
	}

	//Cam collision
	//todo - fix this retarded system
	if (objects.getNumObjects() > 0)
		collision.update(CAM->getActiveCam(), objects.findSpatiallyGroupedGameObjects(objects.getObject(0)), time);
	else
		CAM->getActiveCam()->update(time);
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

void Scene::clearHMap() {
	collision.setHeightMap(std::vector<vec3>());
}

//mm
std::vector<std::string> Scene::saveGame()
{
	std::vector<std::string> s;

	s.push_back("STATE," + std::to_string(state) + "\n");

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

	loaded = true;

	state = atoi(sf.getData().at(1).substr(sf.getData().at(1).find(',') + 1).c_str());

	for (unsigned j = 2; j < sf.getData().size(); j++){
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

bool Scene::getLoaded() {
	if (loaded == true) {
		loaded = false;
		return true;
	}

	return loaded;
}

SimpleStack Scene::getPath(vec3 pos, vec3 target) {
	return objects.getPath(pos, target);
}

bool Scene::setGridScale(int xmin, int xmax, int zmin, int zmax) {
	pGrid.setGridScale(xmin, xmax, zmin, zmax);
	return true;
}

void Scene::gridGreyOut(vec2 pos) {
	pGrid.greyOut(pos);
}

bool Scene::gridIsGrey(vec2 pos) {
	return pGrid.isGrey(pos);
};

float Scene::getGridMultiX() {
	return pGrid.getGridMultiX();
};

float Scene::getGridMultiZ() {
	return pGrid.getGridMultiZ();
};
