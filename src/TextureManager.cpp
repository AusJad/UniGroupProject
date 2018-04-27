#include "TextureManager.h"

TextureManager::TextureManager() {
	nextid = 0;
}

bool TextureManager::loadNewTexture(std::string path, std::string type, std::string name, RenderModuleStubb* renderer) {
	if (images.count(name) == 1) return false;

	bool success = ImgCH.CreateImage(path, type);

	if (!success) return false;

	int id = nextid;

	nextid++;

	ImgCH.bindImage(id, renderer);

	images[name] = id;

	return true;
}

bool TextureManager::useTexture(std::string name, RenderModuleStubb* renderer) {
	if (images.count(name) == 0) return false;
	renderer->bindTexture(images.at(name));

	return true;
}

bool TextureManager::useTexture(std::string name, std::string name2, RenderModuleStubb* renderer) {
	if (images.count(name) == 0 || images.count(name2) == 0) return false;
	renderer->bindMultiTexture(images.at(name), images.at(name2));
	return true;
}

bool TextureManager::deleteTexture(std::string name, RenderModuleStubb* renderer) {
	if (images.count(name) == 0) return false;
	renderer->deleteTexture(images.at(name));
	images.erase(name);
	return true;
}

void TextureManager::disableTexture(RenderModuleStubb* renderer) {
	renderer->bindTexture(NULL);
}

bool TextureManager::genMultiTexture(std::vector<vec3> heightmap, std::vector<std::string> textures, std::string name) {
	if (images.count(name) == 1) return false;

	int id = nextid;

	nextid++;

	bool success = ImgCH.CreateMultiTexture(heightmap, textures, name, id);

	if (success) {
		images[name] = id;
		return true;
	}

	nextid--;

	return false;
}

bool TextureManager::storeTextureFromData(std::string name, unsigned char* data, unsigned bits, unsigned width, unsigned height) {
	int id = nextid;
	nextid++;
	Singleton<RenderModuleStubb>::getInstance()->storeTexture(id, bits, width, height, data);

	images[name] = id;

	return true;
}

void TextureManager::DisableMultiTex(RenderModuleStubb* renderer) {
	renderer->disableMultiTexture();
}


bool TextureManager::loadTempTex(std::string path, std::string type) {
	bool success = ImgCH.CreateImage(path, type);

	if (!success) return false;

	return true;
}

bool TextureManager::createSubTexFromTemp(std::string name, unsigned subwidth, unsigned subheight, unsigned x, unsigned y) {

	int id = nextid;

	nextid++;

	if (!ImgCH.bindSubImage(id, subwidth, subheight, x, y)) return false;

	images[name] = id;

	return true;
}