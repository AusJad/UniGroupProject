#include "EngineStateWriter.h"


bool EngineStateWriter::writeState(std::string filename) {
	std::ofstream outfile(filename.c_str());
	if (!outfile) return false;

	std::string out;

	out += LVL->toString();

	for (unsigned i = 0; i < SM->getGOH().getNumObjects(); i++) {
		if (SM->getGOH().getObject(i) != NULL) {
			if (SM->getGOH().getObject(i)->getType() == "WALL" || SM->getGOH().getObject(i)->getType() == "GENERIC_OBJ") {
				out += SM->getGOH().getObject(i)->toString();
			}
		}
	}

	if (SM->getGOH().getTerrain() != NULL) out += SM->getGOH().getTerrain()->toString();

	outfile.write(out.c_str(), out.size());

	outfile.close();

	return true;
}

bool EngineStateWriter::readState(std::string filename) {
	std::ifstream infile(filename.c_str());
	if (!infile) return false;
	std::string in;
	
	LVL->reset();

	bool hasHead = false;

	try {
		while (infile.peek() != EOF) {
			getline(infile, in);
			if (in == "LEVEL_HEAD") {
				hasHead = true;
				updateLevelInfo(infile);
			}
			else
			if (in == "TERRAIN_START") {
				addTerrain(infile);
			}
			else
			if (in == "WALL_START") {
				addWall(infile);
			}
			else
			if (in == "GO_START") {
				addGenericObj(infile);
			}
		}
	}
	catch (...) {
		return false;
	}

	if (!hasHead) {
		CAM->getActiveCam()->setPos(LVL->getStartPos());
		CAM->getActiveCam()->setHorizontalAngle(LVL->getStartOrientation().x());
		CAM->getActiveCam()->setVerticalAngle(LVL->getStartOrientation().y());
	}

	return true;
}

void EngineStateWriter::updateLevelInfo(std::ifstream & toparse) {
	std::string in;
	std::string linehead;
	vec3 tmpv;
	vec2 tmpv2;
	float tmpf;

	while (in != "LEVEL_TAIL" && toparse.peek() != EOF) {
		getline(toparse, in);
		
		if (in.find(',') != std::string::npos) {
			linehead = in.substr(0, in.find(','));
			in = in.substr(in.find(',') + 1);
		}
		else {
			linehead = "";
		}

		if (linehead == "NAME") {
			LVL->setName(in);
		}
		else
		if (linehead == "START_POS") {
			tmpv.sx((float)atof(in.substr(0, in.find(',') + 1).c_str()));
			in = in.substr(in.find(',') + 1);
			tmpv.sy((float)atof(in.substr(0, in.find(',') + 1).c_str()));
			in = in.substr(in.find(',') + 1);
			tmpv.sz((float)atof(in.c_str()));
			LVL->setStartPos(tmpv);
		}
		else
		if (linehead == "START_OR") {
			tmpf = (float)atof(in.substr(0, in.find(',') + 1).c_str());
			in = in.substr(in.find(',') + 1);
			tmpv2.sx(tmpf);
			tmpf = (float)atof(in.c_str());
			tmpv2.sy(tmpf);
			LVL->setStartOreientation(tmpv2);
		}
	}

	CAM->getActiveCam()->setPos(LVL->getStartPos());
	CAM->getActiveCam()->setHorizontalAngle(LVL->getStartOrientation().x());
	CAM->getActiveCam()->setVerticalAngle(LVL->getStartOrientation().y());
}

void EngineStateWriter::addTerrain(std::ifstream & toparse) {
	std::string in;
	std::string linehead;

	TerrainObject * tmpw;
	tmpw = new TerrainObject();
	if (tmpw == NULL) return;

	while (in != "TERRAIN_END" && toparse.peek() != EOF) {
		getline(toparse, in);

		if (in.find(',') != std::string::npos) {
			linehead = in.substr(0, in.find(','));
			in = in.substr(in.find(',') + 1);
		}
		else {
			linehead = "";
		}

		if (linehead == "NAME") {
			Model * M = NULL;
			M = MMAN->useModel(in, in);
			if (M == NULL) {
				delete tmpw;
				return;
			}
			tmpw->setModel(M);
		}
	}

	tmpw->setID(GOF->getNextId());
	SM->getGOH().addTerrain(tmpw);
	SM->setSceneHeightMap(SM->getCurScene(), tmpw);
}

void EngineStateWriter::addGenericObj(std::ifstream & toparse) {
	std::string in;
	std::string linehead;
	vec3 tmpv;
	float tmpf;

	GenericObject * tmpw;
	tmpw = new GenericObject();
	if (tmpw == NULL) return;

	while (in != "GO_END" && toparse.peek() != EOF) {
		getline(toparse, in);
		
		if (in.find(',') != std::string::npos) {
			linehead = in.substr(0, in.find(','));
			in = in.substr(in.find(',') + 1);
		}
		else {
			linehead = "";
		}

		if (linehead == "POS") {
			tmpv.sx((float)atof(in.substr(0, in.find(',') + 1).c_str()));
			in = in.substr(in.find(',') + 1);
			tmpv.sy((float)atof(in.substr(0, in.find(',') + 1).c_str()));
			in = in.substr(in.find(',') + 1);
			tmpv.sz((float)atof(in.c_str()));
			tmpw->setPos(tmpv);
		}
		else
		if (linehead == "SCALE") {
			tmpf = (float)atof(in.substr(0, in.find(',') + 1).c_str());
			in = in.substr(in.find(',') + 1);
			tmpw->setScaleX(tmpf);
			tmpf = (float)atof(in.substr(0, in.find(',') + 1).c_str());
			in = in.substr(in.find(',') + 1);
			tmpw->setScaleY(tmpf);
			tmpf = (float)atof(in.c_str());
			tmpw->setScaleZ(tmpf);
		}
		else
		if (linehead == "ANGLE") {
			tmpf = (float)atof(in.substr(0, in.find(',') + 1).c_str());
			in = in.substr(in.find(',') + 1);
			tmpw->setAngleX(tmpf);
			tmpf = (float)atof(in.substr(0, in.find(',') + 1).c_str());
			in = in.substr(in.find(',') + 1);
			tmpw->setAngleY(tmpf);
			tmpf = (float)atof(in.c_str());
			tmpw->setAngleZ(tmpf);
		}
		else
			if (linehead == "MODEL") {
				Model * M = NULL;
				M = MMAN->useModel(in, in);
				if (M == NULL) {
					delete tmpw;
					return;
				}
				//std::cout << "Name: " << M->getName() << std::endl;
				tmpw->setModel(M);
				if (MMAN->hasMultiObb(M->getName())) {
					std::vector<OBB> tmpobb = MMAN->getMultiObb(M->getName());
					mat3 tmprotation = Rotation3x3(tmpw->getAngleX(), tmpw->getAngleY(), tmpw->getAngleZ());
					tmpw->addMultiObb(tmpobb);
				}
						
			}
	}

	tmpw->updateBounds();
	tmpw->setID(GOF->getNextId());
	SM->getGOH().addGameObject(tmpw);
}

void EngineStateWriter::addWall(std::ifstream & toparse) {
	std::string in;
	std::string linehead;
	vec3 tmpv;
	float tmpf;

	Wall * tmpw;
	tmpw = new Wall();
	if (tmpw == NULL) return;

	while (in != "WALL_END" && toparse.peek() != EOF) {
		getline(toparse, in);
		
		if (in.find(',') != std::string::npos) {
			linehead = in.substr(0, in.find(','));
			in = in.substr(in.find(',') + 1);
		}
		else {
			linehead = "";
		}

		if (linehead == "POS") {
			tmpv.sx((float)atof(in.substr(0, in.find(',') + 1).c_str()));
			in = in.substr(in.find(',') + 1);
			tmpv.sy((float)atof(in.substr(0, in.find(',') + 1).c_str()));
			in = in.substr(in.find(',') + 1);
			tmpv.sz((float)atof(in.c_str()));
			tmpw->setPos(tmpv);
		}
		else
		if (linehead == "DIMENSIONS") {
			tmpf = (float)atof(in.substr(0, in.find(',') + 1).c_str());
			in = in.substr(in.find(',') + 1);
			tmpw->setWidth(tmpf);
			tmpf = (float)atof(in.substr(0, in.find(',') + 1).c_str());
			in = in.substr(in.find(',') + 1);
			tmpw->setHeight(tmpf);
			tmpf = (float)atof(in.c_str());
			tmpw->setDepth(tmpf);
		}
		else
		if (linehead == "ANGLE") {
			tmpf = (float)atof(in.substr(0, in.find(',') + 1).c_str());
			in = in.substr(in.find(',') + 1);
			tmpw->setAngleX(tmpf);
			tmpf = (float)atof(in.substr(0, in.find(',') + 1).c_str());
			in = in.substr(in.find(',') + 1);
			tmpw->setAngleY(tmpf);
			tmpf = (float)atof(in.c_str());
			tmpw->setAngleZ(tmpf);
		}
		else
		if (linehead == "TEX") {
			tmpw->setTex(in);
		}
		else
		if (linehead == "TEXCOORD") {
			tmpf = (float)atof(in.substr(0, in.find(',') + 1).c_str());
			in = in.substr(in.find(',') + 1);
			tmpw->setTexRepX(tmpf);
			tmpf = (float)atof(in.c_str());
			tmpw->setTexRepY(tmpf);
		}
		else
		if (linehead == "COL") {
			if (in == "0") tmpw->setHasCol(false);
		}
	}
	tmpw->updateBounds();
	tmpw->setID(GOF->getNextId());
	SM->getGOH().addGameObject(tmpw);
}