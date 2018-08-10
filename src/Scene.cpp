#include "Scene.h"


Scene::Scene()
{
	objects.setWorldDimensions(-100, 100, 100, -100);
	state = -1;
	loaded = false;

	/*
	components.push_back(new SelectionComponent(480, 64, vec2(tlscreen.x() + 10, tlscreen.y() + 64)));
	components.push_back(new TextInputComponent(480, FNT_SIZE_MEDIUM_O + 6, vec2(tlscreen.x() + 10, tlscreen.y() + 140)));
	LabelComponent * l = new LabelComponent(480, FNT_SIZE_MEDIUM_O + 6, vec2(tlscreen.x() + 10, tlscreen.y() + 240));
	l->setLabel("this is a test label");
	components.push_back(l);*/

	LabelComponent *l = new LabelComponent();

	tstwnd = WindowFactory::getWindow(WINDOW_SMALL, "GENERIC");
	tstwnd->addComponent(new TextInputComponent(), 50, 10);
	l->setLabel("This is a label");
	tstwnd->addComponent(l, 50, 10);

	tstwnd->addComponent(new TextInputComponent(), 50, 10);
	l = new LabelComponent();
	l->setLabel("Label 2");
	tstwnd->addComponent(l, 50, 10);

	tstwnd->addComponent(new ButtonComponent(64, 64, vec2()));
	tstwnd->addComponent(new SelectionComponent(), 100, 20);

	
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
	tstwnd->render();
	if (resources.hasResource("renderfunc")) {
		RNDR->RenderFacingCamera();
		LSM->callFunction<Scene, MessagingBus>(resources.getResource("renderfunc"), *this, *(Singleton<MessagingBus>::getInstance()));
		RNDR->StopRenderFacingCamera();
	}
}

void Scene::interpretClick(int x, int y) {
	tstwnd->testClick(x, y);
}

bool Scene::attachTerrain(Identifiers & id, vec3 pos, ResourceList & list) {
	return objects.addTerrain(id, pos, list);
}

bool Scene::addObject(Identifiers & id, vec3 pos, ResourceList & list){
	return objects.addObject(id, pos, list);
}

void Scene::update(float time) {
	if (resources.hasResource("updatefunc")) {
		LSM->callFunction<Scene, MessagingBus>(resources.getResource("updatefunc"), *this, *(MSGBS));
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