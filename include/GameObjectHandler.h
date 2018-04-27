#pragma once
#include "GameObjectFactory.h"
#include "QuadTree.h"

/**
* @struct GameObjectWrapper
* @brief Struct for holding all game object data.
*
* @author Morgan Smolder
* @version 01
* @date 02/04/2018
*/
struct GameObjectWrapper {
	GameObject* pointer;
	GameObjectWrapper(GameObject* insert) { pointer = insert; };
	GameObjectWrapper() {};
};

/**
* @class GameObjectHandler
* @brief Class for handling game objects and setting them up in the world
*
* @author Morgan Smolder
* @version 01
* @date 02/04/2018
*/
class GameObjectHandler
{
public:
	GameObjectHandler();
	~GameObjectHandler();

	/**
	* @brief Set the world dimensions
	*
	* @param tlx - Top left x value.
	* @param tlz - Top left z value.
	* @param brx - Bottom right x value.
	* @param brz - Bottom right z value.
	*/
	void setWorldDimensions(float tlx, float tlz, float brx, float brz);

	/**
	* @brief Add a object to the handler.
	*
	* @param id - The identifier.
	* @param list - The list of resources.
	* 
	* @return bool - If the object was added.
	*/
	bool addObject(Identifiers id, vec3 pos, ResourceList & list);

	/**
	* @brief Update function for the manager.
	*
	* @param time - The system time.
	*/
	void update(float time);

	/**
	* @brief The renderer function.
	*/
	void render();

	/**
	* @brief To find game objects grouped spatially around the target game object in the quadtree.
	*
	* @param tofind - The target game object.
	*
	* @return vector<GameObject*> - A list of game objects.
	*/
	std::vector<GameObject*> findSpatiallyGroupedGameObjects(GameObject* tofind);

	/**
	* @brief Get the game objects identifier.
	*
	* @param name - The name of the game object.
	*
	* @param int - The game objects id.
	*/
	int GetGameObjectID(std::string name);

	/**
	* @brief Get the game object.
	*
	* @param name - The game objects name.
	*
	* @return GameObject* - Pointer to the game object.
	*/
	GameObject* GetGameObject(std::string name);

	/**
	* @brief Get the number of objects.
	*
	* @return unsigned - The number of objects.
	*/
	unsigned getNumObjects();

	/**
	* @brief Get the game object.
	*
	* @param index - The index of the game object.
	*
	* @return GameObject * - The game object.
	*/
	GameObject* getObject(unsigned index);

	/**
	* @brief Refresh the quadtree.
	*/
	void refreshTree();

	/**
	* @brief Add terrain to the tree.
	*
	* @param id - The identifier for the terrain.
	* @param pos - The position of the terrain.
	* @param list - The resource list.
	*
	* @return bool - If the terrain was added.
	*/
	bool addTerrain(Identifiers id, vec3 pos, ResourceList & list);

private:
	/// Terrain.
	GameObject* terrain;
	/// Game object vector.
	std::vector<GameObject*> gameobjects;
	/// Quadtree for game objects.
	QuadTree<GameObjectWrapper> gameobjectQT;
	/// Game object factory object to create game objects.
	GameObjectFactory* GOF;
	/// The identifier object.
	Identifiers id;
	/// Vector of game objects for temporary useage.
	std::vector<GameObject*> tmpobjects;

	/**
	* @brief Message receiver method.
	*/
	void msgrcvr();

	/**
	* @brief Add a object to the temporary game object vector.
	*
	* @param id - The identifier of the object.
	* @param pos - The position of the object.
	* @param target - The target position vector of the object.
	* @param model - The resources for the model of the object.
	*/
	bool addTmpObj(Identifiers id, vec3 pos, vec3 target, ResourceList model);
	/// Game object vector for searching.
	static std::vector<GameObject*> searchres;

	/**
	* @brief Get the position function.
	*
	* @param element - The game object.
	*
	* @return pair - The data from the tree.
	*/
	static pair getposfunc(const GameObjectWrapper & element);

	/**
	* @brief Traverse function.
	*
	* @param elements - A vector for game objects.
	* @param topleft - Top left element in the tree.
	* @param bottomright - Bottom right element in the tree.
	*/
	static void travfunc(const std::vector< std::list<GameObjectWrapper> > & elements, pair topleft, pair bottomright);

	/**
	* @brief Comaprison function for two game objects.
	*
	* @param element - The first element.
	* @param comarator - The second element.
	*
	* @return bool - If the game objects are the same.
	*/
	static bool comparisonfunc(const GameObjectWrapper & element, const GameObjectWrapper & comparator);

	/**
	* @brief On find get the data around the element.
	*
	* @param elements - A vector of game objects.
	* @param topleft - The element to the top left of the element.
	* @param bottomright - The element to the bottom of the element.
	*/
	static void onFind(const std::vector<std::list<GameObjectWrapper> > & elements, pair topleft, pair bottomright);
};

