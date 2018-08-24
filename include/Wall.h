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
		void render(const vec3 & transmat) {}
		void centerOnPoint(vec3 & point) {}
		std::vector<vec3>& getVerticies() { return std::vector<vec3>(); }
		void setScale(vec3 & toset) {};
		void updateBounds(vec3 & pos, float width, float depth, float height) {
			
			if (pos.x() < pos.x() + width) {
				minx = pos.x();
				maxx = pos.x() + width;
			}
			else {
				maxx = pos.x();
				minx = pos.x() + width;
			}

			if (pos.y() < pos.y() + height) {
				miny = pos.y();
				maxy = pos.y() + height;
			}
			else {
				maxy = pos.y();
				miny = pos.y() + height;
			}

			if (pos.z() < pos.z() + depth) {
				minz = pos.z();
				maxz = pos.z() + depth;
			}
			else {
				maxz = pos.z();
				minz = pos.z() + depth;
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

	//tmp while still GO
	std::string toString();
	Model* getModel() { return &aabb; }
	void updateBounds() { aabb.updateBounds(trans, width, depth, height); }
	void update(float time) {}
	GameObject* create() { return new Wall(*this); }
	Wall(const Wall & tocpy);
	vec3 getCenterOffset() { return vec3(0, height / 2, 0); };

private:
	float width;
	float height;
	float depth;
	vec3 drawpos;
	vec3 trans;

	std::string tex;

	float angley;
	float anglex;
	float anglez;

	float texrepx;
	float texrepy;

	bool hasCol;

	Bounds aabb;
};

