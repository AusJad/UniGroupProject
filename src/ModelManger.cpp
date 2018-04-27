#include "ModelManger.h"



ModelManger::ModelManger()
{
}


ModelManger::~ModelManger()
{
	for (std::map<std::string, Model*>::iterator mapit = models.begin(); mapit != models.end(); ++mapit) {
		delete mapit->second;
		mapit->second = NULL;
	}
}

bool ModelManger::loadModel(std::string path, std::string type, std::string name) {
	if (models.count(name) == 1) return false;

	Model* tmp = modelfactory.create(path, type);

	if (tmp == NULL) return false;

	tmp->centerOnPoint(vec3(0, 0, 0));

	models[name] = tmp;

	return true;
}

bool ModelManger::loadModel(std::string path, std::string type, std::string name, vec3 & scale) {
	if (models.count(name) == 1) return false;
	if (type != "IM" && type != "MD2") return false;

	Model* tmp = modelfactory.create(path, type);

	if (tmp == NULL) return false;

	tmp->setScale(scale);
	tmp->centerOnPoint(vec3(0, 0, 0));

	models[name] = tmp;

	return true;
}

Model* ModelManger::useModel(std::string name, std::string instancename) {
	if (models.count(name) == 0) {
		return NULL;
	}
	else {
		Model* tmp = NULL;
		tmp = models[name]->create();
		
		if (tmp != NULL) tmp->setName(instancename);

		return tmp;
	}
}

Model* ModelManger::getModelRefrence(std::string name) {
	if (models.count(name) == 0) {
		return NULL;
	}
	else return models[name];
}