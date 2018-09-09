#pragma once

#include "vec3.h"
#include "RenderModuleStubb.h"
#include "TextureManager.h"
#include "GameObject.h"

class Bounds : public Model {
	public:
		Bounds * create() const { return NULL; }
		bool loadModel(std::string filename) { return true; }
		void update(float time) {}
		void render(const vec3 & transmat) {
			RNDR->enableWireframe();
			RNDR->DrawRectangularPrism(vec3(minx, miny, minz), (maxx - minx)/2, (maxy - miny) / 2, (maxz - minz) / 2);
			RNDR->disableWireFrame();
		}
		void centerOnPoint(vec3 & point) {}
		std::vector<vec3>& getVerticies() { return std::vector<vec3>(); }
		void setScale(vec3 & toset) {};
		void updateBounds(vec3 pos, float width, float depth, float height, vec3 anglexyz) {
			
			vec3 postmp = pos;
			pos = vec3();

			vec4 corners[8];

			corners[0] = vec4(pos.x() - width, pos.y() - height, pos.z() - depth, 1);
			corners[1] = vec4(pos.x() - width, pos.y() - height, pos.z() + depth, 1);
			corners[2] = vec4(pos.x() - width, pos.y() + height, pos.z() + depth, 1);
			corners[3] = vec4(pos.x() + width, pos.y() - height, pos.z() + depth, 1);
			corners[4] = vec4(pos.x() - width, pos.y() + height, pos.z() - depth, 1);
			corners[5] = vec4(pos.x() + width, pos.y() + height, pos.z() - depth, 1);
			corners[6] = vec4(pos.x() + width, pos.y() - height, pos.z() - depth, 1);
			corners[7] = vec4(pos.x() + width, pos.y() + height, pos.z() + depth, 1);

			mat4 rot;
			
			rot = Maths::setmat4(rot, 1);

			rot = Maths::translate(rot, postmp);
			rot = Maths::rotate(rot, Maths::radians(anglexyz.x()), vec3(1, 0, 0));
			rot = Maths::rotate(rot, Maths::radians(anglexyz.y()), vec3(0, 1, 0));
			rot = Maths::rotate(rot, Maths::radians(anglexyz.z()), vec3(0, 0, 1));

			for (unsigned i = 0; i < 8; i++) {
				corners[i] = rot * corners[i];
			}


			minx = corners[0].x();
			maxx = corners[0].x();

			miny = corners[0].y();
			maxy = corners[0].y();

			minz = corners[0].z();
			maxz = corners[0].z();

			for (unsigned i = 1; i < 8; i++) {
				if (corners[i].x() < minx) minx = corners[i].x();
				if (corners[i].x() > maxx) maxx = corners[i].x();

				if (corners[i].y() < miny) miny = corners[i].y();
				if (corners[i].y() > maxy) maxy = corners[i].y();

				if (corners[i].z() < minz) minz = corners[i].z();
				if (corners[i].z() > maxz) maxz = corners[i].z();
			}

			lasttrans = vec3();
		}
};

class Wall : public GameObject
{
public:
	Wall();
	void render();
	void setWidth(float nwidth) { width = nwidth; }
	void setHeight(float nheight) { height = nheight; }
	void setDepth(float ndepth) { depth = ndepth; }
	void setPos(vec3 & npos) { trans = npos; }
	void setTex(std::string ntex) { tex = ntex; };
	void setAngleX(float nx) { anglex = nx; }
	void setAngleY(float ny) { angley = ny; }
	void setAngleZ(float nz) { anglez = nz; }
	float getAngleX() { return anglex; }
	float getAngleY() { return angley; }
	float getAngleZ() { return anglez; }
	float getWidth() { return width; }
	float getHeight() { return height; }
	float getDepth() { return depth; }
	const vec3 & getPos() const { return trans; }
	const std::string getTex() { return tex; }
	void setTexRepX(float toset) { texrepx = toset; };
	void setTexRepY(float toset) { texrepy = toset; };
	void setHasCol(bool toset) { hasCol = toset; }
	float getTexRepX() { return texrepx; }
	float getTexRepY() { return texrepy; }
	bool isCollidable() { return hasCol; }
	bool isStatic() { return true; }

	//tmp while still GO
	std::string toString();
	Model* getModel() { return &aabb; }
	void updateBounds() { 
		aabb.updateBounds(trans, width, depth, height, vec3(anglex, angley, anglez)); 

		obb.position = physvec3(trans.x(), trans.y(), trans.z());
		obb.size = physvec3(width / 2, height / 2, depth / 2);
		obb.orientation = Rotation3x3(anglex, angley, anglez);
	}

	void update(float time) {}
	GameObject* create() { return new Wall(*this); }
	Wall(const Wall & tocpy);
	vec3 getCenterOffset() { return vec3(0, height / 2, 0); };

	static void toggleDrawBounds();
	static void DisableBB();
	static bool boundsVis();

	bool hasOBB() { return true; };
	OBB getOBB();
private:
	float width;
	float height;
	float depth;
	vec3 drawpos;
	vec3 trans;

	std::string tex;
	
	static bool drawBounds;

	float angley;
	float anglex;
	float anglez;

	float texrepx;
	float texrepy;

	bool hasCol;

	Bounds aabb;
	OBB obb;
};

