#include "SceneManager.h"


SceneManager::SceneManager()
{
	currscene = 0;
	id.setName("SM");
}


SceneManager::~SceneManager()
{
}

bool SceneManager::attachTerrain(Identifiers & id, unsigned sceneno, vec3 pos, ResourceList & lists) {
	if (scenes.size() <= sceneno) return false;
	else return(scenes.at(sceneno).attachTerrain(id, pos, lists));
}

bool SceneManager::addObject(Identifiers & id, unsigned sceneno, vec3 pos, ResourceList & list) {
	if (scenes.size() <= sceneno) return false;
	else return(scenes.at(sceneno).addObject(id, pos, list));
}

void SceneManager::addScene(void ) {
	Scene tmp;
	scenes.push_back(tmp);
	Singleton<AudioEngine>::getInstance()->addChannelSubgroup(scenes.size()-1);
	Singleton<Controls>::getInstance()->addControlGroup(scenes.size() - 1);
}

bool SceneManager::attachControls(unsigned sceneno, ResourceList toset) {
	if (scenes.size() - 1 <= sceneno == false) return false;
	Singleton<Controls>::getInstance()->bindControls(sceneno, toset);
	return true;
}

void SceneManager::update(float time) {
	msgrcvr();
	scenes.at(currscene).update(time);
}

void SceneManager::render() {
	scenes.at(currscene).render();
}

void SceneManager::setCurrScene(unsigned sceneno) {
	if (sceneno < scenes.size()) {
		closeScene(currscene);
		currscene = sceneno;
		initScene(sceneno);
		scenes.at(currscene).update(0);
	}
	Singleton<LUAScriptManager>::getInstance()->setGlobal<double>(currscene, "curscene");
}

unsigned SceneManager::getNumScenes() {
	return scenes.size();
}

void SceneManager::initScene(unsigned sceneind) {
	Singleton<AudioEngine>::getInstance()->setActiveChannelSubGroup(sceneind);
	Singleton<Controls>::getInstance()->changeControlGroup(sceneind, Singleton<RenderModuleStubb>::getInstance(), Singleton<Controls>::getInstance());
}

void SceneManager::closeScene(unsigned sceneind) {

}

void SceneManager::msgrcvr() {
	MessagingBus* tmp = Singleton<MessagingBus>::getInstance();

	while (tmp->hasMessage(id)) {
		Message tmpmsg = tmp->getMessage(id);
		if (tmpmsg.getInstruction() == "CS") {
			setCurrScene(tmpmsg.getData().idata);
		}
		if (tmpmsg.getInstruction() == "CSR") {
			setCurrScene(currscene + tmpmsg.getData().idata);
		}
	}
}

int  SceneManager::GetGameObjectID(std::string name) {
	int tmpid = -1;
	for (unsigned i = 0; i < scenes.size() && tmpid == -1; i++) {
		tmpid = scenes.at(currscene).GetGameObjectID(name);
	}

	return tmpid;
}

GameObject* SceneManager::GetGameObject(std::string name) {
	GameObject* tmp = NULL;
	for (unsigned i = 0; i < scenes.size() && tmp == NULL; i++) {
		tmp = scenes.at(currscene).GetGameObject(name);
	}

	return tmp;
}

bool SceneManager::setSceneHeightMap(unsigned sceneno, GameObject* hmObj) {
	if (sceneno > scenes.size()) return false;
	else return scenes.at(sceneno).setHeightMap(hmObj);
}