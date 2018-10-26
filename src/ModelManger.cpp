#include "ModelManger.h"



ModelManger::ModelManger()
{
	loadOBBs(std::string("./Resources/Models/specific.obbs"));
}


ModelManger::~ModelManger()
{
	for (std::map<std::string, Model*>::iterator mapit = models.begin(); mapit != models.end(); ++mapit) {
		delete mapit->second;
		mapit->second = NULL;
	}
}

std::vector<OBB> ModelManger::getMultiObb(std::string modelName) {
		return obb_map.at(modelName);		
}

bool ModelManger::hasMultiObb(std::string modelName) {
	if (obb_map.find(modelName) == obb_map.end())
		return false;
	else
		return true;
}



bool ModelManger::loadOBBs(std::string filename) {
	std::cout << "loading obbs from MM" << std::endl;
	std::ifstream infile(filename.c_str());
	if (!infile) {
		std::cout << "couldn't open obb file" << std::endl;
		return false;
	}
	std::string in;
	physvec3 tmppos;
	physvec3 tmpsize;
	physvec3 tmprotate;
	float tmpmass;
	//OBB obbtmp;
	std::string inname;
	
	try {
		while (infile.peek() != EOF) {
			getline(infile, in);
			// name, positionx,y,z,sizex,y,z
			inname = in.substr(0, in.find(',')).c_str();
			in = in.substr(in.find(',') + 1);
			tmppos.x = ((float)atof(in.substr(0, in.find(',') + 1).c_str()));
			in = in.substr(in.find(',') + 1);
			tmppos.y = ((float)atof(in.substr(0, in.find(',') + 1).c_str()));
			in = in.substr(in.find(',') + 1);
			tmppos.z = ((float)atof(in.substr(0, in.find(',') + 1).c_str()));
			in = in.substr(in.find(',') + 1);
			tmpsize.x = ((float)atof(in.substr(0, in.find(',') + 1).c_str()));
			in = in.substr(in.find(',') + 1);
			tmpsize.y = ((float)atof(in.substr(0, in.find(',') + 1).c_str()));
			in = in.substr(in.find(',') + 1);
			tmpsize.z = ((float)atof(in.substr(0, in.find(',') + 1).c_str()));
			in = in.substr(in.find(',') + 1);
			tmprotate.x = ((float)atof(in.substr(0, in.find(',') + 1).c_str()));
			in = in.substr(in.find(',') + 1);
			tmprotate.y = ((float)atof(in.substr(0, in.find(',') + 1).c_str()));
			in = in.substr(in.find(',') + 1);
			tmprotate.z = ((float)atof(in.substr(0, in.find(',') + 1).c_str()));
			in = in.substr(in.find(',') + 1);
			tmpmass = ((float)atof(in.substr(0, in.find(',') + 1).c_str()));
			in = in.substr(in.find(',') + 1);
			mat3 tmprotation = Rotation3x3((float)tmprotate.x, (float)tmprotate.z, (float)tmprotate.y);

			OBB obbtmp(tmppos, tmpsize, tmprotation, tmpmass);
			
			if (obb_map.find(inname) == obb_map.end()) {
				std::cout << "Key not found" << std::endl;
				std::vector<OBB> tmpvec;
				obb_map[inname] = tmpvec;
			}
			obb_map.at(inname).push_back(obbtmp);
		}
	}
	catch (...) {
		std::cout << "failed try" << std::endl;
		infile.close();
		return false;
	}
	infile.close();
	return true;

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

void ModelManger::loadBatch(std::string groupname, std::string path, std::string type, std::string fstype) {
	fileNameReader::getFileNames(path.c_str(), fstype);

	std::cout << path << std::endl;

	std::string activefile;

	while (fileNameReader::hasFiles()) {
		activefile = fileNameReader::getFile();
		std::cout << "Getting: " << activefile << std::endl;
		if (loadModel(path + activefile, type, activefile)) {
			if (batchfiles.count(groupname) == 0) {
				batchfiles[groupname] = std::vector<std::string>();
			}

			batchfiles.at(groupname).push_back(activefile);
			std::cout << "Loaded: " << activefile << std::endl;
		}
		else std::cout << "Failed to Load: " << activefile << std::endl;
	}
}

bool ModelManger::hasModelGroup(std::string group) {
	return batchfiles.count(group) == 1;
}

const std::vector<std::string> & ModelManger::getModelGroup(std::string group) {
	return batchfiles.at(group);
}
