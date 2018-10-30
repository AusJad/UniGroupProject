#pragma once

#include "GameObject.h"
#include <vector>
#include "matrices.h"

#define GRAVITY physvec3(0.0f, -9.8f, 0.0f)

class GenericObject : public GameObject
{
public:
	GenericObject();
	void render();
	void update(float time);
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
	OBB getOBB( unsigned int index );
	OBB getOBBConfig( unsigned int index );
	std::vector<OBB> getOBBs();
	bool hasMultiObb();
	int getNumOBBs();
	OBB getOBB(int obbNum);
	bool addMultiObb(OBB in);
	bool addMultiObb(std::vector<OBB> & in);

	//mm
	physvec3 getDimentions();

	void calcMass();
	void calcCOM();
	physvec3 getCOM();

private:
	float scalex;
	float scaley;
	float scalez;
	vec3 trans;
	OBB obb;
	std::vector<OBB> obbs;
	std::vector<OBB> obbsConfig;
	float angley;
	float anglex;
	float anglez;

	physvec3 COM;
};

