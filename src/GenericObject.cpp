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
	if (model != NULL) out += "MODEL," + model->getName() + "\n";
	out += "GO_END\n";

	return out;
}

OBB GenericObject::getOBB() {
	return obb;
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
		std::vector<vec3> minmax = model->computeMMax();

		obb.position = physvec3(trans.x(), trans.y(), trans.z());
		obb.size = physvec3((minmax.at(1).x() -minmax.at(0).x()) / 2,
			(minmax.at(1).y() - minmax.at(0).y()) / 2,
			(minmax.at(1).z() - minmax.at(0).z()) / 2);
		obb.orientation = Rotation3x3(anglex, angley, anglez);
	}
}

void GenericObject::render() {
	GeoStream << BEGIN_STREAM << trans_3(trans) << scale_3(scalex, scaley, scalez) << rot_4(anglex, 1, 0, 0) << rot_4(angley, 0, 1, 0) << rot_4(anglez, 0, 0, 1);

	if (model != NULL) model->render(trans);

	GeoStream << END_STREAM;

	/*
	GeoStream << START_ATTRIB << color_3(1.0f, 0.6f, 0.0f);
	RNDR->enableWireframe();
	physvec3 rot = Decompose(obb.orientation);
	GeoStream << BEGIN_STREAM << trans_3(obb.position.x, obb.position.y, obb.position.z) << rot_4(RAD2DEG(rot.x), 1, 0, 0) << rot_4(RAD2DEG(rot.y), 0, 1, 0) << rot_4(RAD2DEG(rot.z), 0, 0, 1);
	RNDR->DrawRectangularPrism(vec3(), obb.size.x, obb.size.y, obb.size.z);
	GeoStream << END_STREAM;
	RNDR->disableWireFrame();
	RNDR->DrawRectangularPrism(vec3(obb.position.x, obb.position.y, obb.position.z), 3, 3, 3);
	GeoStream << END_ATTRIB;*/
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