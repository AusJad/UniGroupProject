#pragma once

#include "Model.h"
#include "vec2.h"
#include "RenderModuleStubb.h"
#include "MessagingBus.h"
#include <iostream>
#include "TextureManager.h"

/**
* @struct MD2header
* @brief Contains header data.
*
* @author Morgan Smolder
* @version 01
* @date 08/05/2018
*/
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

/**
* @struct md2vec3
* @brief Contains position data.
*
* @author Morgan Smolder
* @version 01
* @date 08/05/2018
*/
struct md2vec3 {
	float data[3];
};

/**
* @struct md2skin
* @brief Contains texture data.
*
* @author Morgan Smolder
* @version 01
* @date 08/05/2018
*/
struct md2skin {
	char name[64];
};

/**
* @struct md2texcord
* @brief Contains texture coord data.
*
* @author Morgan Smolder
* @version 01
* @date 08/05/2018
*/
struct md2texcord {
	short x;
	short y;
	md2texcord(short nx, short ny) : x(nx), y(ny) {};
	md2texcord() {};
};

/**
* @struct md2Tri
* @brief Contains triangle data.
*
* @author Morgan Smolder
* @version 01
* @date 08/05/2018
*/
struct md2Tri {
	unsigned short faces[3];
	unsigned short txcoordind[3];
};

/**
* @struct md2vertex
* @brief Contains mesh vertex data.
*
* @author Morgan Smolder
* @version 01
* @date 08/05/2018
*/
struct md2vertex {
	unsigned char pos[3];
	unsigned char normalind;
};

/**
* @struct md2animframe
* @brief Contains animation data.
*
* @author Morgan Smolder
* @version 01
* @date 08/05/2018
*/
struct md2animframe {
	md2vec3 scale;
	md2vec3 trans;
	std::string name;
	md2vertex * verticies;
	float minx, minz, miny, maxx, maxz, maxy;
};

/**
* @struct Material
* @brief Contains material data.
*
* @author Morgan Smolder
* @version 01
* @date 08/05/2018
*/
struct Material {
	std::string texture;
};

/**
* @struct Mesh
* @brief Contains mesh data.
*
* @author Morgan Smolder
* @version 01
* @date 08/05/2018
*/
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

/**
* @class MD2Model
* @brief Provides an interface for model animations.
*
* @author Morgan Smolder
* @version 01
* @date 08/05/2018
*/
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

	 /**
	 * @brief Increment the current frame.
	 */
	 void incFrame();

	 /**
	 * @brief Find if there is an animation.
	 *
	 * @param animation - A file path to a animation.
	 *
	 * @return bool - If there was an animation.
	 */
	 bool hasAnimation(std::string animation);

	 /**
	 * @brief Play the animation.
	 *
	 * @param toplay - The animation data.
	 * @param loop - If the animation should loop.
	 *
	 * @return bool - If the animation played.
	 */
	 bool playAnimation(std::string toplay, bool loop);

	 /**
	 * @brief Stop the animation.
	 */
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

	 /**
	 * @brief Get the min translated x value.
	 *
	 * @return float - Min translated value.
	 */
	 virtual float getMinTX() { return frames.at(curframe).minx + lasttrans.x(); };

	 /**
	 * @brief Get the min translated z value.
	 *
	 * @return float - Min translated value.
	 */
	 virtual float getMinTZ() { return frames.at(curframe).minz + lasttrans.z(); };

	 /**
	 * @brief Get the min translated y value.
	 *
	 * @return float - Min translated value.
	 */
	 virtual float getMinTY() { return frames.at(curframe).miny + lasttrans.y(); };

	 /**
	 * @brief Get the max translated x value.
	 *
	 * @return float - Max translated value.
	 */
	 virtual float getMaxTX() { return frames.at(curframe).maxx + lasttrans.x(); };

	 /**
	 * @brief Get the max translated z value.
	 *
	 * @return float - Max translated value.
	 */
	 virtual float getMaxTZ() { return frames.at(curframe).maxz + lasttrans.z(); };

	 /**
	 * @brief Get the max translated y value.
	 *
	 * @return float - Max translated value.
	 */
	 virtual float getMaxTY() { return frames.at(curframe).maxy + lasttrans.y(); };

private:
	/**
	* @brief Build an animation list.
	*/
	void buildAnimationList();
	/**
	* @brief Get the number index.
	*
	* @param tosearch - The name of the animation being looked for.
	*
	* @return int - The index.
	*/
	int getNumInd(std::string & tosearch);

	/**
	* @brief Render the animation.
	*/
	void renderAnimated();

	/**
	* @brief Render the static objects.
	*/
	void renderStatic();

	/**
	* @brief Method to get interpolation.
	*/
	void linInterpolate();

	/**
	* @brief A message receiver method.
	*/
	void msgrcvr();

	/**
	* @brief A method to calc the min x and y values.
	*/
	void calcXminYmin();

	/// The pointer to the child.
	MD2Model * child;
	/// A map of the animations.
	std::map<std::string, std::vector<unsigned> > animations;
	/// The header.
	MD2header header;
	/// A path to the model texture.
	std::string skins;
	/// The texture coords.
	std::vector<md2texcord> texcoords;
	/// The triangle for rendering
	std::vector<md2Tri> triangles;
	/// A vector of frames.
	std::vector<md2animframe> frames;
	/// The current frame.
	unsigned curframe;
	/// The next frame.
	unsigned nextframe;
	/// The key for the active animation.
	std::string activeanimation;
	/// The scale of the model.
	vec3 scale;
	/// The translation for the model.
	vec3 trans;
	/// If the animation is playing.
	bool animationplaying;
	/// If the animation should loop.
	bool loop;
	/// The current interpolation value.
	float curinerpolation;
};

