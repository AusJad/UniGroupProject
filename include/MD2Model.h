#pragma once

#include "Model.h"
#include "vec2.h"
#include "RenderModuleStubb.h"
#include "MessagingBus.h"
#include <iostream>
#include "TextureManager.h"

struct MD2header{
	int id;
	int version;
	int skinWidth;
	int skinHeight;
	int frameSize;
	int numSkins;
	int numVerts;
	int numTexCoords;
	int numTri;
	int numGLCommands;
	int numFrames;
	int offsetSkins;
	int offsetTexCoord;
	int offsetTri;
	int offsetFrame;
	int offsetGLCommands;
	int fileSize;
};

struct md2vec3 {
	float data[3];
};

struct md2skin {
	char name[64];
};

struct md2texcord {
	short x;
	short y;
	md2texcord(short nx, short ny) : x(nx), y(ny) {};
	md2texcord() {};
};

struct md2Tri {
	unsigned short faces[3];
	unsigned short txcoordind[3];
};

struct md2vertex {
	unsigned char pos[3];
	unsigned char normalind;
};

struct md2animframe {
	md2vec3 scale;
	md2vec3 trans;
	std::string name;
	md2vertex * verticies;
	float minx, minz, miny, maxx, maxz, maxy;
};

struct Material {
	std::string texture;
};

struct Mesh {
	/// Vector for the verticies.
	std::vector<vec3> Vertices;
	/// Vector for the texture coords.
	std::vector<vec2> texCoords;
	/// Vector for the normals.
	std::vector<vec3> Normals;
	/// Vector for the indexies
	std::vector<unsigned> vertIndex;
	/// The texture data.
	Material* material;
};

class MD2Model : public Model
{
public:
	MD2Model();
	~MD2Model();


	/**
	* @brief Virtual method to create a model
	*
	* @return Model * - The model data.
	*/
	 MD2Model * create() const ;

	/**
	* @brief Virtual method to load a model.
	*
	* @param filename - The filename.
	*
	* @return bool - If the model loaded.
	*/
	 bool loadModel(std::string filename);

	/**
	* @brief Virtual method to update the model.
	*/
	 void update(float time);

	/**
	* @brief Virtual method to render the model.
	*
	* @param transmat - The translation matrix.
	*/
	 void render(const vec3 & transmat);

	/**
	* @brief Virtual method to get the center on the point.
	*
	* @param point - The position to get the center of.
	*/
	 void centerOnPoint(vec3 & point);

	/**
	* @brief Virtual method to get the verticies.
	*
	* @return vector<vec3> - The verticies.
	*/
	 std::vector<vec3>& getVerticies();

	/**
	* @brief Virtual method to get the scale.
	*
	* @param toset - The vector to be set.
	*/
	 void setScale(vec3 & toset);

	 void incFrame();

	 bool hasAnimation(std::string animation);

	 bool playAnimation(std::string toplay, bool loop);

	 void stopAnimation();

	 /**
	 * @brief Get the min x value.
	 *
	 * @return float - The min x value.
	 */
	 float getMinX() { return frames.at(curframe).minx; };

	 /**
	 * @brief Get the min z value.
	 *
	 * @return float - The min z value.
	 */
	 virtual float getMinZ() { return frames.at(curframe).minz; };

	 /**
	 * @brief Get the min y value.
	 *
	 * @return float - The min y value.
	 */
	 virtual float getMinY() { return frames.at(curframe).miny; };

	 /**
	 * @brief Get the max x value.
	 *
	 * @return float - The max x value.
	 */
	 virtual float getMaxX() { return frames.at(curframe).maxx; };

	 /**
	 * @brief Get the max z value.
	 *
	 * @return float - The maz z value.
	 */
	 virtual float getMaxZ() { return frames.at(curframe).maxz; };

	 /**
	 * @brief Get the max y value.
	 *
	 * @return float - The max y value.
	 */
	 virtual float getMaxY() { return frames.at(curframe).maxy; };

	 virtual float getMinTX() { return frames.at(curframe).minx + lasttrans.x(); };

	 virtual float getMinTZ() { return frames.at(curframe).minz + lasttrans.z(); };

	 virtual float getMinTY() { return frames.at(curframe).miny + lasttrans.y(); };

	 virtual float getMaxTX() { return frames.at(curframe).maxx + lasttrans.x(); };

	 virtual float getMaxTZ() { return frames.at(curframe).maxz + lasttrans.z(); };

	 virtual float getMaxTY() { return frames.at(curframe).maxy + lasttrans.y(); };

private:
	void buildAnimationList();
	int getNumInd(std::string & tosearch);
	void renderAnimated();
	void renderStatic();
	void linInterpolate();
	void msgrcvr();
	void calcXminYmin();

	MD2Model * child;
	std::map<std::string, std::vector<unsigned> > animations;
	MD2header header;
	std::string skins;
	std::vector<md2texcord> texcoords;
	std::vector<md2Tri> triangles;
	std::vector<md2animframe> frames;
	unsigned curframe;
	unsigned nextframe;
	std::string activeanimation;
	vec3 scale;
	vec3 trans;
	bool animationplaying;
	bool loop;
	float curinerpolation;
};

