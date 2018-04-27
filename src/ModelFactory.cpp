#include "ModelFactory.h"

unsigned ModelFactory::nextid = 0;

ModelFactory::ModelFactory() {
	
}

Model* ModelFactory::create(std::string path, std::string type) {
	Model* tmp;

	if (type == "RAWTRN") {
		tmp = new RAWTerrain;
		if (tmp == NULL) {
			return tmp;
		}
		if (tmp->loadModel(path)) {
			tmp->setId(nextid++);
			return tmp;
		}
		else {
			delete tmp;
			return NULL;
		}
	}
	if (type == "IM") {
		tmp = new ImportModel;
		if (tmp == NULL) {
			return tmp;
		}
		if (tmp->loadModel(path))
		{
			tmp->setId(nextid++);
			return tmp;
		}
		else
		{
			delete tmp;
			return NULL;
		}
	}
	if (type == "TX") {
		tmp = new TexturedSquare;
		if (tmp == NULL) {
			return tmp;
		}
		if (tmp->loadModel(path))
		{
			tmp->setId(nextid++);
			return tmp;
		}
		else
		{
			delete tmp;
			return NULL;
		}
	}
	if (type == "MD2") {
		tmp = new MD2Model;
		if (tmp == NULL) {
			return tmp;
		}
		if (tmp->loadModel(path))
		{
			tmp->setId(nextid++);
			return tmp;
		}
		else
		{
			delete tmp;
			return NULL;
		}
	}

	return NULL;
}
