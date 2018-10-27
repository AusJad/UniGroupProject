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
#include "saveFileIO.h"

#include "Geometry3D.h"

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
	GameObject(const GameObject & tocpy);

	virtual GameObject* create() = 0;

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
	virtual const vec3 & getPos() const;

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
	virtual Model* getModel();

	/**
	* @brief A virtual method for if the GameObject is visible or not.
	*
	* @return bool - If the object is visible or not.
	*/
	virtual bool isVisible();

	/**
	* @brief A virtual method to stop the object.
	*/
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

	/**
	* @brief The default message handler for GameObjects.
	*
	* @param message - The message.
	*
	* @return bool - If the message was processed.
	*/
	bool defaultMessageHandler(Message & message);

	/**
	* @brief A virtual method to determine what to do with the object apon collision.
	*
	* @param prevloc - The objects previous location.
	* @param colgoid - The ID of the object collided with.
	*/
	virtual void onCollide(vec3 & prevloc, const Identifiers & colgoid);

	void setIdentifiers(const Identifiers & toset) { this->id = toset; };

	virtual void onCollide2(vec3 & prevloc, const vec3 & colpos) {};

	/**
	* @brief A virtual method to determine if the object has gravity or not.
	*
	* @return bool - If the object has gravity.
	*/
	virtual bool hasGravity();

	//mm
	/**
	* @brief A virtual method for putting all data in a string to be saved to file.
	*
	* @return string - The data for file.
	*/
	virtual std::string toString();

	virtual bool fromstring(std::string toread);

	/**
	* @brief A virtual method for putting all data from file back into the object.
	*
	* @param toread - The data from file.
	* 
	* @return bool - If the data was input.
	*/
	virtual bool fromstring(std::string linehead, std::string & toread);

	virtual bool hasOBB() { return false; }
	virtual OBB getOBB() { return OBB(); }
	virtual OBB getOBB(int obbNum) { return OBB(); };
	virtual int getNumOBBs();
	virtual bool isStatic() { return false; }
	virtual std::vector<OBB> getOBBs() { return std::vector<OBB>(); };
	virtual bool hasMultiObb() { return false; };

	// mm
	physvec3 getAngularVel();
	physvec3 getVel();
	physmat4 getIntert_tensor();
	float getTotalMass();

	void setAngularVel(physvec3 angvel);
	void setVel(physvec3 v);
	void setIntert_tensor(physmat4 it);
	void setTotalMass(float tm);

	virtual physvec3 getDimentions() { return physvec3(-1, -1, -1); };

	virtual void calcMass();


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

	// mm
	physvec3 angularvel, vel;
	physmat4 intert_tensor;
	float totalmass;

	/**
	* @brief The message receiver.
	*/
	void msgrcvr();
};

