#include "GameObjectHandler.h"

std::vector<GameObject*> GameObjectHandler::searchres;

GameObjectHandler::GameObjectHandler()
{
	terrain = NULL;
	id.setName("GOH");
}

GameObjectHandler::~GameObjectHandler(){
	if (terrain != NULL) delete terrain;
	terrain = NULL;

	for (unsigned i = 0; i < gameobjects.size(); i++) {
		delete gameobjects.at(i);
		gameobjects.at(i) = NULL;
	}

	for (unsigned i = 0; i < tmpobjects.size(); i++) {
		delete tmpobjects.at(i);
		tmpobjects.at(i) = NULL;
	}
}

GameObjectHandler::GameObjectHandler(const GameObjectHandler & tocpy) {
	if (tocpy.terrain != NULL) terrain = tocpy.terrain->create();
	else terrain = NULL;

	for (unsigned i = 0; i < tocpy.gameobjects.size(); i++) {
		gameobjects.push_back(tocpy.gameobjects.at(i)->create());
	}

	for (unsigned i = 0; i < tocpy.tmpobjects.size(); i++) {
		tmpobjects.push_back(tocpy.tmpobjects.at(i)->create());
	}

	id = tocpy.id;
}

const GameObjectHandler & GameObjectHandler::operator = (const GameObjectHandler & rhs) {
	if (terrain != NULL) delete terrain;
	terrain = NULL;

	for (unsigned i = 0; i < gameobjects.size(); i++) {
		delete gameobjects.at(i);
		gameobjects.at(i) = NULL;
	}

	for (unsigned i = 0; i < tmpobjects.size(); i++) {
		delete tmpobjects.at(i);
		tmpobjects.at(i) = NULL;
	}

	if (rhs.terrain != NULL) terrain = rhs.terrain->create();
	else terrain = NULL;
	
	for (unsigned i = 0; i < rhs.gameobjects.size(); i++) {
		gameobjects.push_back(rhs.gameobjects.at(i)->create());
	}
	
	for (unsigned i = 0; i < rhs.tmpobjects.size(); i++) {
		tmpobjects.push_back(rhs.tmpobjects.at(i)->create());
	}
	
	id = rhs.id;

	return *this;
}

bool GameObjectHandler::addTerrain(Identifiers id, vec3 pos, ResourceList & list) {
	if (id.getType() != "TO") return false;
	
	GameObject* tmp = GOF->create(id, pos, list);

	if (tmp == NULL) return false;

	if (this->terrain != NULL) {
		delete this->terrain;
	}

	this->terrain = tmp;

	return true;
}

bool GameObjectHandler::addObject(Identifiers id, vec3 pos, ResourceList & list){
	GameObject* tmp = GOF->create(id, pos, list);

	if (tmp == NULL) return false;
	else {
		gameobjects.push_back(tmp);
	}
	return true;
}

void GameObjectHandler::addGameObject(GameObject* toadd) {
	gameobjects.push_back(toadd);
}

void GameObjectHandler::msgrcvr() {
	Message tmpmsg;
	
	while (MSGBS->hasMessage(id)) {
		tmpmsg = MSGBS->getMessage(id);
		if (tmpmsg.getInstruction() == ADD_TMP_OBJ) {
			addTmpObj(Identifiers("BLT", tmpmsg.getFrom().getType()), tmpmsg.getData().mvdata.at(0), tmpmsg.getData().mvdata.at(1), ResourceList("model", tmpmsg.getData().sdata));
		}
		if (tmpmsg.getInstruction() == GET_OBJECT_LIST) {
			tmpmsg.setInstruction(OBJECT_LIST_RESPONSE);
			
			tmpmsg.getData().sdata = "";

			for (unsigned i = 0; i < gameobjects.size(); i++) {
				if (!gameobjects.at(i)->getIdentifiers().getName().empty()) {
					tmpmsg.getData().sdata += gameobjects.at(i)->getIdentifiers().getName();
					tmpmsg.getData().sdata += ",";
				}
			}
			
			MSGBS->postIMessage(tmpmsg, CONSOLE_ID);
		}
	}
}

void GameObjectHandler::update(float time) {
	msgrcvr();
	for (unsigned i = 0; i < tmpobjects.size(); i++) {
		tmpobjects.at(i)->update(time);
	}
}

unsigned GameObjectHandler::getNumObjects() {
	return gameobjects.size() + tmpobjects.size();
}

GameObject* GameObjectHandler::getObject(unsigned index) {
	if (index >= gameobjects.size()) {
		int ind = index - gameobjects.size();
		
		if(tmpobjects.at(ind)->isVisible()) return tmpobjects.at(ind);
		else return NULL;
	}
	return gameobjects.at(index);
}

void GameObjectHandler::removeGameObject(GameObject * toremove) {
	bool found = false;
	
	for (unsigned i = 0; i < tmpobjects.size() && !found; i++) {
		if (toremove->getID() == tmpobjects.at(i)->getID()) {
			tmpobjects.erase(tmpobjects.begin() + i);
			found = true;
		}
	}

	if (found) return;

	for (unsigned i = 0; i < gameobjects.size() && !found; i++) {
		if (toremove->getID() == gameobjects.at(i)->getID()) {
			gameobjects.erase(gameobjects.begin() + i);
			found = true;
		}
	}
}

int GameObjectHandler::GetGameObjectID(std::string name) {
	int tmpid = -1;
	
	for (unsigned i = 0; i < gameobjects.size() && tmpid == -1; i++) {
		if (gameobjects.at(i)->getIdentifiers().getName() == name) {
			tmpid = (int) gameobjects.at(i)->getID();
		}
	}

	return tmpid;
	
	if (tmpid = -1 && terrain != NULL) {
		if (terrain->getIdentifiers().getName() == name) tmpid = (int) terrain->getID();
	}

	return tmpid;
}

GameObject* GameObjectHandler::GetGameObject(std::string name) {
	GameObject* tmp = NULL;

	for (unsigned i = 0; i < gameobjects.size() && tmp == NULL; i++) {
		if (gameobjects.at(i)->getIdentifiers().getName() == name) {
			tmp = gameobjects.at(i);
		}
	}

	if (tmp == NULL && terrain != NULL) {
		if (terrain->getIdentifiers().getName() == name) tmp = terrain;
	}

	return tmp;
}

void GameObjectHandler::render() {
	if (terrain != NULL) terrain->render();

	for (unsigned i = 0; i < tmpobjects.size(); i++) {
		tmpobjects.at(i)->render();
	}
	for (unsigned i = 0; i < gameobjects.size(); i++) {
		gameobjects.at(i)->render();
	}
}

bool GameObjectHandler::addTmpObj(Identifiers id, vec3 pos, vec3 target, ResourceList model) {
	bool found = false;
	if (model.hasResource("model") == false) return false;
	for (unsigned i = 0; i < tmpobjects.size() && !found; i++) {
		if (tmpobjects.at(i)->isVisible() == false ) {
			found = true;
			tmpobjects.at(i)->setIdentifiers(id);
			tmpobjects.at(i)->setPos(pos);
			tmpobjects.at(i)->setTarget(target);
			if(Singleton<ModelManger>::getInstance()->getModelRefrence(model.getResource("model")) != NULL)
			if(Singleton<ModelManger>::getInstance()->getModelRefrence(model.getResource("model"))->getId() != tmpobjects.at(i)->getModel()->getId())
				tmpobjects.at(i)->setModel(Singleton<ModelManger>::getInstance()->useModel(model.getResource("model"), "NAN"));
		}
	}

	if(found) return true;	

	GameObject * tmp = GOF->create(id, pos, model);

	if (tmp == NULL) return false;

	tmp->setPos(pos);

	tmp->setTarget(target);

	tmpobjects.push_back(tmp);

	return true;
}

void GameObjectHandler::setWorldDimensions(float tlx, float tlz, float brx, float brz) {

}

void  GameObjectHandler::refreshTree() {

}

std::vector<GameObject*> GameObjectHandler::findSpatiallyGroupedGameObjects(GameObject* tofind) {
	return gameobjects;
}

pair GameObjectHandler::getposfunc(const GameObjectWrapper & element) {
	pair temp;

	temp.x = element.pointer->getPos().x();
	temp.z = element.pointer->getPos().z();

	return temp;
}

void  GameObjectHandler::travfunc(const std::vector< std::list<GameObjectWrapper> > & elements, pair topleft, pair bottomright) {
	for (unsigned i = 0; i < elements.size(); i++) {
		for (std::list<GameObjectWrapper>::const_iterator listit = elements.at(i).begin(); listit != elements.at(i).end(); ++listit) {
			searchres.push_back(listit->pointer);
		}
	}
}

bool  GameObjectHandler::comparisonfunc(const GameObjectWrapper & element, const GameObjectWrapper & comparator) {
	if (element.pointer->getID() == comparator.pointer->getID()) {
		return true;
	}

	return false;
}

void  GameObjectHandler::onFind(const std::vector<std::list<GameObjectWrapper> > & elements, pair topleft, pair bottomright) {
	for (unsigned i = 0; i < elements.size(); i++) {
		for (std::list<GameObjectWrapper>::const_iterator listit = elements.at(i).begin(); listit != elements.at(i).end(); ++listit) {
			searchres.push_back(listit->pointer);
		}
	}
}

void GameObjectHandler::clear() {
	for (unsigned i = 0; i < gameobjects.size(); i++) {
		delete gameobjects.at(i);
		gameobjects.at(i) = NULL;
	}
	
	gameobjects.clear();

	for (unsigned i = 0; i < tmpobjects.size(); i++) {
		delete tmpobjects.at(i);
		tmpobjects.at(i) = NULL;
	}

	tmpobjects.clear();
}