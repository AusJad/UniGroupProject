#pragma once

#include "Model.h"
#include "ModelFactory.h"
#include <map>

/**
* @class ModelManger
* @brief Class for handling model objects
*
* @author Morgan Smolder
* @version 01
* @date 02/04/2018
*/
class ModelManger
{
public:
	ModelManger();
	~ModelManger();

	/**
	* @brief Load the model.
	*
	* @param path - The path of the file.
	* @param type - The type of model.
	* @param name - The name of the model.
	*
	* @return bool - If the model loaded.
	*/
	bool loadModel(std::string path, std::string type, std::string name);

	/**
	* @brief Use the model.
	*
	* @param name - The name of the model.
	*
	* @return Model* - The model data.
	*/
	Model* useModel(std::string name, std::string instancename);

	/**
	* @brief Get the model refrence.
	* 
	* @param name - The name of the model.
	* 
	* @return Model* - The model data.
	*/
	Model* getModelRefrence(std::string name);

	/**
	* @brief Load the model.
	*
	* @param path - The file path.
	* @param type - The file type.
	* @param name - The file name.
	* @param scale - The scale vector.
	*
	* @return bool - If the model loaded.
	*/
	bool loadModel(std::string path, std::string type, std::string name, vec3 & scale);

private:
	/// The model creation object.
	ModelFactory modelfactory;
	/// A map of models.
	std::map<std::string, Model*> models;
};

