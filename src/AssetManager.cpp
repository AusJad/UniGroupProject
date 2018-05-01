#include "AssetManager.h"



AssetManager::AssetManager()
{
	TexMan = Singleton<TextureManager>::getInstance();
	MM = Singleton<ModelManger>::getInstance();
}


AssetManager::~AssetManager()
{
	delete TexMan;
	TexMan = NULL;
	delete MM;
	MM = NULL;
}

bool AssetManager::addResource(std::string path, std::string type, std::string name) {
	if (TexMan->loadNewTexture(path, type, name, Singleton<RenderModuleStubb>::getInstance())) {
		return true;
	}
	else
	if (MM->loadModel(path, type, name)) {
		return true;
	}
	else
	if(AE->loadSound(path, type, name, true)){

		return true;
	}
	else
	if (type == "FNT") {
		if (FNT_ENG->loadFont(path, name)) return true;
	}

	return false;
}

bool AssetManager::addModel(std::string path, std::string type, std::string name, vec3 & scale) {
	if (MM->loadModel(path, type, name, scale)) {
		return true;
	}
	return false;
}

bool AssetManager::useResource(std::string name) {
	if (TexMan->useTexture(name, Singleton<RenderModuleStubb>::getInstance())) {
		return true;
	}
	else
	if (AE->playSound(name)) {
		return true;
	}
	else 
	if (FNT_ENG->setActiveFont(name)) {
		return true;
	}

	return false;
}

bool AssetManager::addSound(std::string path, std::string type, std::string name, bool loop) {
	return AE->loadSound(path, type, name, loop);
}