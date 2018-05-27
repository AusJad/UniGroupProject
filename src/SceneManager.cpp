#include "SceneManager.h"


SceneManager::SceneManager()
{
	currscene = 0;
	id.setName("SM");
}


SceneManager::~SceneManager()
{
}

void SceneManager::attachConsoleBehaviour(std::string entrypoint) {
	console.attachBehaviour(entrypoint);
}

void SceneManager::attachConsoleTex(std::string tex) {
	console.addTex(tex);
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
	if(console.isActive()) console.update(time);

	msgrcvr();

	Singleton<LUAScriptManager>::getInstance()->setGlobal<float>(time, "time");
	if (!console.isActive()) {
		scenes.at(currscene).update(time);
	}
}

void SceneManager::render() {
	if (console.isActive()) console.render();

	scenes.at(currscene).render();
}

void SceneManager::setCurrScene(unsigned sceneno) {
	if (sceneno < scenes.size()) {
		closeScene(currscene);
		Singleton<LUAScriptManager>::getInstance()->setGlobal<double>(currscene, "prevscene");
		currscene = sceneno;
		initScene(sceneno);
		scenes.at(currscene).update(0);
		Singleton<LUAScriptManager>::getInstance()->setGlobal<double>(currscene, "curscene");
	}
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
			//Strictly Temporary - due to bug in playing cutscene with console active
			if(console.isActive()) console.toggle();
			CONT->switchContextConsole(console.isActive(), RNDR, CONT);
		}
		else
		if (tmpmsg.getInstruction() == "CSR") {
			setCurrScene(currscene + tmpmsg.getData().idata);
		}
		else
		if (tmpmsg.getInstruction() == TGL_CONSOLE) {
			console.toggle();
			CONT->switchContextConsole(console.isActive(), RNDR, CONT);
		}
		else
		if (tmpmsg.getInstruction() == PUSH_CHANGES) {
			scenes.at(currscene).update(0);
		}
		else 
		if (tmpmsg.getInstruction() == SAVE_GAME) {
			if (scenes.size() > tmpmsg.getiData()) {
				unsigned tmpc = currscene;
				currscene = tmpmsg.getiData();
				saveGame(tmpmsg.getData().sdata);
				currscene = tmpc;
			}
		}
		if (tmpmsg.getInstruction() == LOAD_GAME) {
			loadGame(tmpmsg.getData().sdata);
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
	else
	if (scenes.at(sceneno).setHeightMap(hmObj)) {
		Singleton<LUAScriptManager>::getInstance()->setGlobal<float>(hmObj->getModel()->getMinX(), "worldminx" + std::to_string(sceneno));
		Singleton<LUAScriptManager>::getInstance()->setGlobal<float>(hmObj->getModel()->getMaxX(), "worldmaxx" + std::to_string(sceneno));
		Singleton<LUAScriptManager>::getInstance()->setGlobal<float>(hmObj->getModel()->getMaxZ(), "worldmaxz" + std::to_string(sceneno));
		Singleton<LUAScriptManager>::getInstance()->setGlobal<float>(hmObj->getModel()->getMinZ(), "worldminz" + std::to_string(sceneno));
		return true;
	}

	return false;
}

bool SceneManager::saveGame(std::string savename) {
	std::string savef = std::to_string(currscene) + "\n";

	//mm
	save sf(savename); // Assuming it is just a file name (no path or extention)
	
	std::vector<std::string> tmp = scenes[currscene].saveGame();
	if (tmp.size() > 0) {
		tmp.at(0) = savef + tmp.at(0);
	}

	sf.saveGame(tmp);

	return true;
}

bool SceneManager::loadGame(std::string filetoload) {
	try {
		//mm
		save sf(filetoload); // Create save object with filename.
		if (sf.loadFile()) // Checks that file exists and that it is loaded in.
		{
			std::string tmp = sf.getData().at(0);

			int tmpi = atoi(tmp.c_str());
			
			int cs = currscene;

			setCurrScene(tmpi);

			scenes[currscene].loadGame(sf);
		}

		return true;
	}
	catch (...) {
		return false;
	}
}

bool SceneManager::setSceneResources(ResourceList & toset, unsigned sceneno) {
	if (sceneno > scenes.size()) return false;
	scenes.at(sceneno).addResources(toset);
	return true;
}

//return stack, not void
void SceneManager::findPath(const vec3 & pos, const vec3 & target) {
	std::cout << "in path finder" << std::endl;

	//Your pathfinding function - calls findpath for current scene with arguments to thei function.
	//Have to use SM singleton here, as function is static
	//return SM->findPath();
}