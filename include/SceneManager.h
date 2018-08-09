#pragma once
#include "Scene.h"
#include "AudioEngine.h"
#include "Controls.h"
#include "Console.h"
#include "Singleton.h"

//mm
#include "saveFileIO.h"

#define SM Singleton<SceneManager>::getInstance() 

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

	/**
	* @brief Attach console behaviour to the console.
	*
	* @param entrypoint - The behaviour.
	*/
	void attachConsoleBehaviour(std::string entrypoint);

	/**
	* @brief Attach text to the console.
	*
	* @param tex - The texture data for the text.
	*/
	void attachConsoleTex(std::string tex);

	/**
	* @brief Set the scene resource list.
	*
	* @param toset - The resource list.
	* @param sceneno - The scene number.
	*
	* @return bool - If the resources were set.
	*/
	bool setSceneResources(ResourceList & toset, unsigned sceneno);

	static void findPath(const vec3 & pos, const vec3 & target);

	void interpretClick(int x, int y);

private:
	/// The scene vector.
	std::vector<Scene> scenes;
	/// The current scene id.
	unsigned currscene;
	/// The identifier.
	Identifiers id;
	/// The console.
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

	/**
	* @brief A method to save the game.
	*
	* @param savename - The name of the file to be saved.
	*
	* @return bool - If the game was saved.
	*/
	bool saveGame(std::string savename);

	/**
	* @brief A method to load the game from file.
	*
	* @param filetoload - The file to load.
	*
	* @return bool - If the game loaded.
	*/
	bool loadGame(std::string filetoload);
};

