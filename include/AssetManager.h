#pragma once

#include "TextureManager.h"
#include "Singleton.h"
#include "AudioEngine.h"
#include "ModelManger.h"

/**
* @class AssetManager
* @brief Provides an  interface to the various resource managing modules.
*
* @author Morgan Smolder
* @version 01
* @date 02/04/2018
*/

class AssetManager
{
public:
	AssetManager();
	~AssetManager();
	/**
	* @brief Requests for a new resource to be loaded.
	*
	* @param path - Location of the resource on disk.
	* @param type - The type of resource to load.
	* @param name - The handle to be used in calls to utilise resource.
	* @return bool - Wether or not the resource was loaded correctly.
	*/
	bool addResource(std::string path, std::string type, std::string name); 
	
	/**
	* @brief Uses resource with given handle.
	*
	* @param path - Location of the resource on disk.
	* @param type - The type of resource to load.
	* @param name - The handle to be used in calls to utilise resource.
	*
	* @return bool - Wether or not the resource could be successfully used.
	*/
	bool useResource(std::string name);

	/**
	* @brief Adds a model to the asset manager.
	*
	* @param path - Location of the resource on disk.
	* @param type - The type of resource to load.
	* @param name - The handle to be used in calls to utilise resource.
	* @param scale - The scale vector for the model.
	*
	* @return bool - Wether or not the resource could be successfully used.
	*/
	bool addModel(std::string path, std::string type, std::string name, vec3 & scale);

	/**
	* @brief Add sound to the channel.
	*
	* @param path - Location of the resource on disk.
	* @param type - The type of resource to load.
	* @param name - The handle to be used in calls to utilise resource.
	* @param loop - Flag to check if the sound should loop.
	*
	* @return bool - If the sound was successfully added.
	*/
	bool addSound(std::string path, std::string type, std::string name, bool loop);

private:
	///Pointer to texture manager module
	TextureManager* TexMan;
	///Pointer to audio manager module
	AudioEngine* AE;
	///Pointer to model manager module
	ModelManger* MM;
};

