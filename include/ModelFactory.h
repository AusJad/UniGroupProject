#pragma once

#include "Model.h"
#include "RawTerrain.h"
#include "ImportModel.h"
#include "TexturedSquare.h"


/**
* @class ModelFactory
* @brief Class for creating model objects
*
* @author Morgan Smolder
* @version 01
* @date 02/04/2018
*/
class ModelFactory
{
public:

	ModelFactory();

	/**
	* @brief Create a model.
	*
	* @param path - The file path.
	* @param type - The type of model.
	*
	* @return Model* - The model data.
	*/
	Model* create(std::string path, std::string type);
private:
	/// The next id of the model to be created.
	static unsigned nextid;
};

