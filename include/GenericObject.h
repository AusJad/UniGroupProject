#pragma once

#include "GameObject.h"
#include <vector>


class GenericObject : public GameObject
{
public:
	GenericObject();
	void render();
	void update(float time) {};
	void setScaleX(float nscalex);
	void setScaleY(float nscaley);
	void setScaleZ(float nscalez);
	void setPos(vec3 & npos) { trans = npos; }
	void setAngleX(float nx) { anglex = nx; }
	void setAngleY(float ny) { angley = ny; }
	void setAngleZ(float nz) { anglez = nz; }
	float getAngleX() { return anglex; }
	float getAngleY() { return angley; }
	float getAngleZ() { return anglez; }
	float getScaleX() { return scalex; }
	float getScaleY() { return scaley; }
	float getScaleZ() { return scalez; }
	void updateBounds();
	const vec3 & getPos() const { return trans; }
	

	//tmp while still GO
	std::string toString();
	GameObject* create() { return new GenericObject(*this); }
	GenericObject(const GenericObject & tocpy);

	bool isStatic() { return true; }
	bool hasOBB() { return true; };
	OBB getOBB();
	std::vector<OBB> getOBBs();
	bool hasMultiObb();
	int getNumOBBs();
	OBB getOBB(int obbNum);

private:
	float scalex;
	float scaley;
	float scalez;
	vec3 trans;
	OBB obb;
	std::vector<OBB> obbs;
	float angley;
	float anglex;
	float anglez;
};

