#pragma once
#include <Assimp/scene.h>
#include <Assimp/Importer.hpp>
#include <Assimp/postprocess.h>
#include "RenderModuleStubb.h"
#include "Singleton.h"
#include "Model.h"
//#include "vec2.h"
#include "TextureManager.h"
#include "Maths.h"
#include "ModelMesh.h"

/**
* @class ImportModel
* @brief Class for importing models from assimp
*
* @author Jarad Mckay
* @version 01
* @date 02/04/2018
*/
class ImportModel : public Model
{
public:
	ImportModel* create() const;

	ImportModel();
	ImportModel(const ImportModel & tocpy);
	~ImportModel();

	/**
	* @brief Load the model from file.
	*
	* @param filename - The file name.
	*
	* @return bool - If the model loaded.
	*/
	bool loadModel(std::string filename);

	/**
	* @brief Set the scale vector.
	*
	* @param toset - The scale vector.
	*/
	void setScale(vec3 & toset);

	/**
	* @brief Update function.
	*/
	void update(float time);

	/**
	* @brief rendering function.
	*
	* @param transmat - The translation matrix.
	*/
	void render(const vec3 & transmat);

	/**
	* @brief Get the vertices of the model.
	*
	* @return vector<ve3> - The verticies of the model.
	*/
	std::vector<vec3>& getVerticies();

private:
	/// The model data.
	const aiScene *model;

	vec3 scale;

	/**
	* @brief Set the max and min values.
	*/
	void setMinsAndMaxs();

	/**
	* @brief Create a random string.
	*
	* @param len - The length of the string.
	*
	* @return string - The random string.
	*/
	std::string RandomString(unsigned len);

	///Vector storing meshes for a model.
	std::vector<ModelMesh> modelDetails;

	/// The texture data.
	std::vector<std::string> texture;

	///stores all the verticies of all the meshes of a model.
	std::vector<vec3> allVerticies;

	/**
	* @brief Set the center of the point.
	*
	* @param point - The position.
	*/
	void centerOnPoint(vec3 &point);
};

