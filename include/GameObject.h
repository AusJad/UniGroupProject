#pragma once
//#include "vec3.h"
#include "LUAScriptManager.h"
#include "Singleton.h"
#include <string>
#include "Identifiers.h"
#include "MessagingBus.h"
#include "ResourceList.h"
#include "RenderMOduleStubb.h"
#include "Model.h"
#include "Maths.h"
#include "ModelManger.h"

// mm
#include "saveFileIO.h"

/**
* @class GameObject
* @brief Class for handling game objects and all their data.
*
* @author Morgan Smolder
* @version 01
* @date 02/04/2018
*/
class GameObject
{
public:
	GameObject();
	GameObject(Identifiers & id, vec3 pos, ResourceList & list);
	~GameObject();

	/**
	* @brief Set the id of the object
	*
	* @param id - New id.
	*/
	void setID(int id);

	/**
	* @brief Get the d of the object.
	*
	* @return int - The id.
	*/
	int getID() const;

	/**
	* @brief Set the position of the object.
	*
	* @param pos - The new position.
	*/
	void setPos(vec3 pos);

	/**
	* @brief Get the positon of the object.
	*
	* @return vec3 - The position of the object.
	*/
	const vec3 & getPos() const;

	/**
	* @brief Get the type of the object.
	*
	* @return string - The type of the object.
	*/
	std::string getType();

	/**
	* @brief Update the object.
	*
	* @param time - System time.
	*/
	virtual void update(float time) = 0;

	/**
	* @brief Virtual method to render the object.
	*/
	virtual void render() = 0;

	/**
	* @brief Virtaul method to get the center offset of the object.
	*
	* @return vec3 - The center offset of the object.
	*/
	virtual vec3 getCenterOffset();

	/**
	* @brief Get the identifier of the object.
	*
	* @return Identifiers - The identifier of the object.
	*/
	const Identifiers &getIdentifiers();

	/**
	* @brief Get the state of the object.
	*
	* @return int - The state of the object.
	*/
	int getState();

	/**
	* @brief Set the state of the object.
	*
	* @param state - The state of the object.
	*/
	void setState(int state);


	/**
	* @brief Virtual method to set the model of the object.
	*
	* @param m - The model for the object.
	*/
	virtual void setModel(Model* M);

	/**
	* @brief Get the model of the object.
	*
	* @return Model* - The model of the object.
	*/
	Model* getModel();

	virtual bool isVisible();
	virtual void stop();

	/**
	* @brief Set the target position vector of the object.
	*
	* @param vec3 - The new target position vector of the object.
	*/
	virtual void setTarget(const vec3 target);

	/**
	* @brief Get the target position vector of the object.
	*
	* @return vec3 - The target position vector of the object.
	*/
	const vec3 & getTarget();

	/**
	* @brief Find if the object is collidiable with other objects.
	*
	* @return bool - If the object can collide.
	*/
	virtual bool isCollidable();

	bool defaultMessageHandler(Message & message);

	virtual void onCollide(vec3 & prevloc, const Identifiers & colgoid);

	virtual bool hasGravity();

	//mm
	virtual std::string toString();
	virtual bool fromstring(std::string toread);

protected:
	/// The state of the object.
	int state;
	/// The position of the object.
	vec3 pos;
	/// The position vector of the target.
	vec3 target;
	/// The position vector for the look at target.
	vec3 targetlook;
	/// The objects identifier.
	Identifiers id;
	/// The resources linked to the object.
	ResourceList resources;
	/// The model data for the object.
	Model* model;

	/**
	* @brief The message receiver.
	*/
	void msgrcvr();
};

