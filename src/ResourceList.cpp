#include "ResourceList.h"

ResourceList::ResourceList() {
	resources.clear();
}

ResourceList::ResourceList(std::string k1, std::string v1) {
	resources[k1] = v1;
}

ResourceList::ResourceList(std::string k1, std::string v1, std::string k2, std::string v2) {
	resources[k1] = v1;
	resources[k2] = v2;
}

ResourceList::ResourceList(std::string k1, std::string v1, std::string k2, std::string v2, std::string k3, std::string v3){
	resources[k1] = v1;
	resources[k2] = v2;
	resources[k3] = v3;
}

bool ResourceList::hasResource(std::string key) {
	return resources.count(key) == 1;
}

std::string ResourceList::getResource(std::string key) {
	return resources[key];
}

bool ResourceList::addResource(std::string k1, std::string v1) {
	if (resources.count(k1) == 1) return false;
	resources[k1] = v1;
	return true;
}
