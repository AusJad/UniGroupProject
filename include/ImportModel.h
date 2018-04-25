#pragma once

#include <Assimp/Importer.hpp>
#include <Assimp/postprocess.h>
#include <Assimp/scene.h>
#include "RenderModuleStubb.h"
#include "Singleton.h"
#include "Model.h"
#include "TextureManager.h"
#include "Mesh.h"

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
	void update();

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
	/**
	* @brief Set the max and min values.
	*/
	void setMinsAndMaxs();

	/**
	* @brief Set the center of the point.
	*
	* @param point - The position.
	*/
	void centerOnPoint(vec3 &point);


	/**
	* @brief Create a random string.
	*
	* @param len - The length of the string.
	*
	* @return string - The random string.
	*/
	std::string RandomString(unsigned len);


	///Vector storing meshes for a model.
	std::vector<Mesh> modelDetails;

	/// The texture data.
	std::vector<std::string> texture;

	/// The model data.
	const aiScene *model;
};

