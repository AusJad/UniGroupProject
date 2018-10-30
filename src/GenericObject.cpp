#include "GenericObject.h"

GenericObject::GenericObject() {
	scalex = 1;
	scaley = 1;
	scalez = 1;
	angley = 0;
	anglex = 0;
	anglez = 0;
	id.setType("GENERIC_OBJ");
	totalmass = 1;
}

std::string GenericObject::toString() {
	std::string out;

	out += "GO_START\n";
	out += "POS," + std::to_string(trans.x()) + "," + std::to_string(trans.y()) + "," + std::to_string(trans.z()) + "\n";
	out += "SCALE," + std::to_string(scalex) + "," + std::to_string(scaley) + "," + std::to_string(scalez) + "\n";
	out += "ANGLE," + std::to_string(anglex) + "," + std::to_string(angley) + "," + std::to_string(anglez) + "\n";
	if (model != NULL) out += "MODEL," + model->getName() + "\n";
	out += "GO_END\n";

	return out;
}

bool GenericObject::addMultiObb(std::vector<OBB> & in) {
	this->obbsConfig = in;
	this->obbs = this->obbsConfig;
	return true;
};

OBB GenericObject::getOBB() {
	return obb;
}

OBB GenericObject::getOBB(unsigned int index ) {
	if (index < obbs.size())
		return obbs[index];
}

std::vector<OBB> GenericObject::getOBBs() {
	return obbs;
};

OBB GenericObject::getOBBConfig(unsigned int index) {
	if (index < obbsConfig.size()) {
		return obbsConfig[index];
	}
}

bool GenericObject::hasMultiObb() {
	if (obbsConfig.size() > 0) { return true; }
	else { return false; }	
};

int GenericObject::getNumOBBs() {
	return obbsConfig.size();
};

OBB GenericObject::getOBB(int obbNum) {
	return obbs.at(obbNum);
};

void GenericObject::setScaleX(float nscalex) { 
	scalex = nscalex; 
}

void GenericObject::setScaleY(float nscaley) { 
	scaley = nscaley; 
}

void GenericObject::setScaleZ(float nscalez) { 
	scalez = nscalez; 
}

void GenericObject::update(float time) {
	const float dampening = 0.99f;

	//std::cout << "Generic objects update function" << std::endl;

	vel *= dampening;
	trans.sx(trans.x() + vel.x);
	trans.sy(trans.y() + vel.y);
	trans.sz(trans.z() + vel.z);

	////MD - trans = vec3(vel.x, vel.y, vel.z);
	//physvec3 angularAcceleration = MultiplyVector(torques, Inverse(intert_tensor));

	angularvel *= dampening;
	physvec3 orientation = Decompose(obb.orientation);
	orientation += angularvel * time;
	anglex = anglex + DEG2RAD(orientation.x);
	angley = angley + DEG2RAD(orientation.y);
	anglez = anglez + DEG2RAD(orientation.z);

	updateBounds();
	render();
}

void GenericObject::updateBounds() {
	if (model != NULL) {
		model->setScale(vec3(scalex, scaley, scalez));
		std::vector<vec3> minmax = model->computeMMax();
		if (this->hasMultiObb()) {
			for (int i = 0; i < obbs.size(); i++){
				//obbs[i].position = physvec3((trans.x() + obbsConfig[i].position.x * (scalex)), trans.y() + obbsConfig[i].position.y * (scaley), trans.z() + obbsConfig[i].position.z * (scalez));
				obbs[i].size.x = obbsConfig[i].size.x * scalex;
				obbs[i].size.y = obbsConfig[i].size.y * scaley;
				obbs[i].size.z = obbsConfig[i].size.z * scalez;
				//rotate around origin
				//physvec3 tmp = MultiplyPoint(((obbs[i].position - obbsConfig[i].position) * physvec3(scalex, scaley, scalez)), Rotation(anglex, angley, anglez));
				obbs[i].position = trans;
				physvec3 tmp2 = physvec3(obbsConfig[i].position.x, obbsConfig[i].position.y, obbsConfig[i].position.z) * physvec3(scalex, scaley, scalez);
				physvec3 tmp = MultiplyPoint(tmp2, Rotation(anglex, angley, anglez));
				obbs[i].position += tmp;
				//std::cout << "tmp.x: " << tmp.x << " tmp.y: " << tmp.y << " tmp.z: " << tmp.z << std::endl;
				
				// = trans + tmp;
				//obbs[i].position.x = tmp.x;
				//obbs[i].position.y = tmp.y;
				//obbs[i].position.z = tmp.z;
				//obbs[i].position = physvec3((trans.x() + obbsConfig[i].position.x * (scalex)), trans.y() + obbsConfig[i].position.y * (scaley), trans.z() + obbsConfig[i].position.z * (scalez));
				obbs[i].orientation = Rotation3x3(anglex, angley, anglez);
				//obbs[i].position -= physvec3((obbsConfig[i].position.x * (scalex)), obbsConfig[i].position.y * (scaley), obbsConfig[i].position.z * (scalez));

				this->calcMass();//mm
		} 
		}
		else {
			obb.position = physvec3(trans.x(), trans.y(), trans.z());
			obb.size = physvec3((minmax.at(1).x() - minmax.at(0).x()) / 2,
				(minmax.at(1).y() - minmax.at(0).y()) / 2,
				(minmax.at(1).z() - minmax.at(0).z()) / 2);
			obb.orientation = Rotation3x3(anglex, angley, anglez);

			this->calcMass();//mm
			this->calcCOM();
		}
	}
}

void GenericObject::render() {
	
	GeoStream << BEGIN_STREAM << trans_3(trans) << scale_3(scalex, scaley, scalez) << rot_4(anglex, 1, 0, 0) << rot_4(angley, 0, 1, 0) << rot_4(anglez, 0, 0, 1);
	if (model != NULL) model->render(trans);
//
	GeoStream << END_STREAM;

	physvec3 rot;
	if (this->hasMultiObb()) {
		GeoStream << START_ATTRIB << color_3(0.6f, 1.0f, 0.0f);
		OBB tmpobb;
		for (int i = 0; i < this->getNumOBBs(); i++) {
			RNDR->enableWireframe();
			tmpobb = this->getOBB(i);
			rot = Decompose(tmpobb.orientation);
			GeoStream << BEGIN_STREAM << trans_3(tmpobb.position.x, tmpobb.position.y, tmpobb.position.z) << rot_4(RAD2DEG(rot.x), 1, 0, 0) << rot_4(RAD2DEG(rot.y), 0, 1, 0) << rot_4(RAD2DEG(rot.z), 0, 0, 1);
			RNDR->DrawRectangularPrism(vec3(), tmpobb.size.x, tmpobb.size.y, tmpobb.size.z);
			GeoStream << END_STREAM;
			RNDR->disableWireFrame();
			RNDR->DrawRectangularPrism(vec3(tmpobb.position.x, tmpobb.position.y, tmpobb.position.z), 3, 3, 3);
			
		}
	}
	else {
		GeoStream << START_ATTRIB << color_3(1.0f, 0.6f, 0.0f);
		rot = Decompose(obb.orientation);
		RNDR->enableWireframe();
		GeoStream << BEGIN_STREAM << trans_3(obb.position.x, obb.position.y, obb.position.z) << rot_4(RAD2DEG(rot.x), 1, 0, 0) << rot_4(RAD2DEG(rot.y), 0, 1, 0) << rot_4(RAD2DEG(rot.z), 0, 0, 1);
		RNDR->DrawRectangularPrism(vec3(), obb.size.x, obb.size.y, obb.size.z);
		GeoStream << END_STREAM;
		RNDR->disableWireFrame();
		RNDR->DrawRectangularPrism(vec3(obb.position.x, obb.position.y, obb.position.z), 3, 3, 3);
		
	}
	GeoStream << END_ATTRIB;
}

bool GenericObject::addMultiObb(OBB in) {
	obbs.push_back(in);
		return true;
}

GenericObject::GenericObject(const GenericObject & tocpy) : GameObject(*this) {
	scalex = tocpy.scalex;
	scaley = tocpy.scaley;
	scalez = tocpy.scalez;
	trans = tocpy.trans;
	angley = tocpy.angley;
	anglex = tocpy.anglex;
	anglez = tocpy.anglez;
}

// mm
physvec3 GenericObject::getDimentions() 
{
	return physvec3(model->getMaxX() - model->getMinX(), model->getMaxY() - model->getMinY(), model->getMaxY() - model->getMinY());
};

void GenericObject::calcMass()
{
	if (this->hasMultiObb())
	{
		for (int i = 0; i < obbs.size(); i++)
		{
			totalmass += obbs[i].mass;
		}
	}
	else
	{
		totalmass = obb.mass;
	}
}

void GenericObject::calcCOM()
{
	float x = 0;
	float y = 0;
	float z = 0;
	if (this->hasMultiObb())
	{
		for (int i = 0; i < obbs.size(); i++)
		{
			x += obbs[i].mass * obbs[i].position.x;
			y += obbs[i].mass * obbs[i].position.y;
			z += obbs[i].mass * obbs[i].position.z;
		}
		x /= totalmass;
		y /= totalmass;
		z /= totalmass;

		COM = physvec3(x, y, z);
	}
	else
	{
		COM = obb.position;
	}

	//std::cout << "x: " << COM.x << " y: " << COM.y << " z:" << COM.z << std::endl;
}

physvec3 GenericObject::getCOM()
{
	return COM;
}