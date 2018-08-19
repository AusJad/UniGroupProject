#include "EngineStateWriter.h"


bool EngineStateWriter::writeState(std::string filename) {
	std::ofstream outfile(filename.c_str());
	if (!outfile) return false;

	std::string out;

	for (unsigned i = 0; i < SM->getGOH().getNumObjects(); i++) {
		if (SM->getGOH().getObject(i) != NULL) {
			if (SM->getGOH().getObject(i)->getType() == "WALL" || SM->getGOH().getObject(i)->getType() == "GENERIC_OBJ") {
				out += SM->getGOH().getObject(i)->toString();
			}
		}
	}

	outfile.write(out.c_str(), out.size());

	outfile.close();

	return true;
}

bool EngineStateWriter::readState(std::string filename) {
	std::ifstream infile(filename.c_str());
	if (!infile) return false;
	std::string in;
	
	try {
		while (infile.peek() != EOF) {
			getline(infile, in);
			if (in == "WALL_START") {
				addWall(infile);
			}
		}
	}
	catch (...) {
		return false;
	}

	return true;
}

void EngineStateWriter::addWall(std::ifstream & toparse) {
	std::string in;
	std::string linehead;
	vec3 tmpv;
	float tmpf;

	Wall * tmpw;
	tmpw = new Wall();
	if (tmpw == NULL) return;

	while (in != "WALL_END") {
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
	}

	tmpw->updateBounds();
	tmpw->setID(GOF->getNextId());
	SM->getGOH().addGameObject(tmpw);
}