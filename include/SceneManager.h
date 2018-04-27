#pragma once
#include "Scene.h"
#include "AudioEngine.h"
#include "Controls.h"
#include "Console.h"

/**
* @class SceneManager
* @brief Class for handling the scene object
*
* @author Morgan Smolder
* @version 01
* @date 02/04/2018
*/
class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	/**
	* @brief Add a scene to the manager.
	*/
	void addScene(void);

	/**
	* @brief Add a object to the manager.
	*
	* @param id - The object identifier.
	* @param sceneno - The scene number.
	* @param pos - The postion vector.
	* @param list - The resource list.
	*
	* @return bool - If the object was added.
	*/
	bool addObject(Identifiers & id, unsigned sceneno, vec3 pos, ResourceList & list);

	/**
	* @brief Attach a terrain to the scene
	*
	* @param id - The identifier for the terrain.
	* @param sceneno - The scene id.
	* @param pos - The position vector.
	* @param list - The resource lists.
	*
	* @return bool - If the terrain was attached.
	*/
	bool attachTerrain(Identifiers & id, unsigned sceneno, vec3 pos, ResourceList & lists);

	/**
	* @brief Get the game object id.
	* 
	* @param name - the game object name.
	*
	* @return int - The game object id.
	*/
	int GetGameObjectID(std::string name);

	/**
	* @brief The update function
	*
	* @param time - System time.
	*/
	void update(float time);

	/**
	* @brief The render function.
	*/
	void render();

	/**
	* @brief Set the current scene.
	*
	* @param sceneno - The scene number to be set to.
	*/
	void setCurrScene(unsigned sceneno);

	/**
	* @brief Get the scene number.
	*
	* @return unsigned - The scene number.
	*/
	unsigned getNumScenes();

	/**
	* @brief Get the game object.
	*
	* @param name - The game objects name.
	*
	* @return GameObject* - The game object.
	*/
	GameObject* GetGameObject(std::string name);

	/**
	* @brief Set the scene heightmap.
	*
	* @param sceneno - The scene number.
	* @param hmObj - The heightmap object.
	*
	* @return bool - If the scene heightmap was set.
	*/
	bool setSceneHeightMap(unsigned sceneno, GameObject* hmObj);

	/**
	* @brief Attach controls to a scene.
	*
	* @param sceneno - The scene id.
	* @param toset - The resource list.
	*
	* @return bool - If the controls were attached to the scene.
	*/
	bool attachControls(unsigned sceneno, ResourceList toset);

	void attachConsoleBehaviour(std::string entrypoint);

private:
	/// The scene vector.
	std::vector<Scene> scenes;
	/// The current scene id.
	unsigned currscene;
	/// The identifier.
	Identifiers id;

	Console console;
	
	/**
	* @brief Initalise the scene.
	*
	* @param sceneind - The scene index.
	*/
	void initScene(unsigned sceneind);

	/**
	* @brief Close the scene.
	*
	* @param sceneind - The scene index.
	*/
	void closeScene(unsigned sceneind);

	/**
	* @brief The message reveiver method.
	*/
	void msgrcvr();
};

