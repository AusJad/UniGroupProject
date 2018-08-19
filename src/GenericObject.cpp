#include "GenericObject.h"

GenericObject::GenericObject() {
	scalex = 1;
	scaley = 1;
	scalez = 1;
	angley = 0;
	anglex = 0;
	anglez = 0;
	id.setType("GENERIC_OBJ");
}

std::string GenericObject::toString() {
	std::string out;

	out += "GO_START\n";
	out += "POS," + std::to_string(trans.x()) + "," + std::to_string(trans.y()) + "," + std::to_string(trans.z()) + "\n";
	out += "SCALE," + std::to_string(scalex) + "," + std::to_string(scaley) + "," + std::to_string(scalez) + "\n";
	out += "ANGLE," + std::to_string(anglex) + "," + std::to_string(angley) + "," + std::to_string(anglez) + "\n";
	if (!tex.empty()) out += "TEX," + tex + "\n";
	out += "GO_END\n";

	return out;
}

void GenericObject::setScaleX(float nscalex) { 
	scalex = nscalex; 
}

void GenericObject::setScaleY(float nscaley) { 
	scaley = nscaley; 
}

void GenericObject::setScaleZ(float nscalez) { 
	scalez = nscalez; 
}

void GenericObject::updateBounds() {
	if (model != NULL) {
		model->setScale(vec3(scalex, scaley, scalez));
	}
}

void GenericObject::render() {
	GeoStream << BEGIN_STREAM << trans_3(trans) << scale_3(scalex, scaley, scalez) << rot_4(anglex, 1, 0, 0) << rot_4(angley, 0, 1, 0) << rot_4(anglez, 0, 0, 1);

	if (model != NULL) model->render(trans);

	GeoStream << END_STREAM;
}

GenericObject::GenericObject(const GenericObject & tocpy) : GameObject(*this) {
	scalex = tocpy.scalex;
	scaley = tocpy.scaley;
	scalez = tocpy.scalez;
	trans = tocpy.trans;
	tex = tocpy.tex;
	angley = tocpy.angley;
	anglex = tocpy.anglex;
	anglez = tocpy.anglez;
}