#pragma once
#include "GameObject.h"
#include <iostream>
#include "AudioEngine.h"
#include "StateMachine.h"
#include "State.h"

#include <map>
#include "State.h"
#include "Traits.h"

#include <math.h>

/**
* @class NPC
* @brief Class for creating NPCs
*
* @author Morgan Smolder
* @version 01
* @date 02/04/2018
*/
class NPC : public GameObject
{
public:
	NPC(Identifiers & id, vec3 pos, ResourceList & list);
	NPC();
	~NPC();
	NPC(const NPC & tocpy);

	GameObject* create();

	/**
	* @brief The update function.
	*
	* @param time - The system time.
	*/
	void update(float time);

	/**
	* @brief The render function.
	*/
	void render();

	/**
	* @brief Get the center offset.
	*
	* @return vec3 - The offset.
	*/
	vec3 getCenterOffset();

	/**
	* @brief Get the NPCs velocity.
	*
	* @return vec3 - The velocity.
	*/
	const vec3 & getVelocity();

	/**
	* @brief Get the NPCs health.
	*
	* @return float - The health.
	*/
	const float & getHealth();

	/**
	* @brief Set the NPCs velocity.
	*
	* @param velocity - The new velocity.
	*/
	void setVelocity(const vec3 & velocity);

	/**
	* @brief Set the health of the NPC.
	*
	* @param health - The new health of the NPC.
	*/
	void setHealth(float health);

	/**
	* @brief Set the speed of the NPC.
	*
	* @param speed - The new speed of the NPC.
	*/
	void setSpeed(float speed);

	/**
	* @brief Get the speed of the NPC.
	*
	* @return float - The speed of the NPC.
	*/
	float getSpeed();

	/**
	* @brief A method to make the NPC stop what its doing.
	*/
	void stop();

	/**
	* @brief A default message handler method.
	*
	* @param message - The message.
	*
	* @return bool - If the message was processed.
	*/
	bool NPCDefaultMessageHandler(Message & message);

	/**
	* @brief Get the heading position.
	*
	* @return vec3 - The heading position.
	*/
	const vec3 & getHeading();

	/**
	* @brief Set the heading position.
	*
	* @param heading - The new heading position.
	*/
	void setHeading(const vec3 & heading);

	/**
	* @brief Set the l angle.
	*
	* @param nangle - The new angle.
	*/
	void setLAngle(float nangle);

	//mm
	/**
	* @brief Set the NPC data to a string.
	*
	* @return string - The NPC data.
	*/
	std::string toString();

	/**
	* @brief Set the NPC data from a string.
	*
	* @param toread - The string being parsed.
	*
	* @return bool - If the data loaded.
	*/
	bool fromstring(std::string toread);

	void checkUpdateRndrChange();

	void setUpdatable(bool toset);

	bool isCollidable();

	bool getCanAttack();

	void setCanAttack(bool nval);

	/**
	* @brief A virtual method to determine what to do with the object apon collision.
	*
	* @param prevloc - The objects previous location.
	* @param colgoid - The ID of the object collided with.
	*/
	void onCollide(vec3 & prevloc, const Identifiers & colgoid);

	void setEvadeTime(float toset);

	float getEvadeTime();

	void onCollide2(vec3 & prevloc, const vec3 & colpos);

	const vec3 & getEvadeTarget();
	void setEvadeTarget(const vec3 & toset);

	//mm
	std::map<std::string, std::map<int, bool>> getAffordances();
	
	// Reason for 2 GenerateAffordances functions is because im unsure if we are passing in a single gameobject on a loop or a vector of game objects in a single call
	void GenerateAffordances(std::vector<GameObject*> GOs);
	//void GenerateAffordances(GameObject *GO);

private:
	vec3 evadetarget;
	/// Velocity of the NPC.
	vec3 velocity;
	/// The heading of the NPC.
	vec3 heading;
	/// The look angle of the NPC.
	float lookangle;
	/// The health of the NPC.
	float health;
	/// The speed of the NPC.
	float speed;
	///Flag to determine wether npc should be updated(is active)
	bool canUpdate = false;
	///Flag to determine whether npc should be rendered
	bool canRender = false;
	///can attack
	bool canAttack;

	float evadetime;


	//mm
	std::map<std::string, std::map<int, bool>> Affordances;
	float maxBench; // Do you even lift bro

	// These are private as they are only called for GenerateAffordances()
	bool canSit(GameObject *go);
	bool canMove(GameObject *go);
	bool canPick_up(GameObject *go);

	physvec3 getDimentions();

	State* currState;
	std::vector<State*> allStates; // All possible states - This may need to be done a better way if time permits.
	mat4 EmotionNormalisation;

	std::vector<Mods*> all_Emo_Mods;
	std::vector<Defs*> all_Emo_Defs;
	vec4 DefaultEmotion = vec4( 0, 0, 0, 0 ); // Default emotional state for individual NPC
	vec4 Emotion; // Because human emotion is just vec4 obviously.
	/*
		+x = Exstasy
		-x = Grief
		
		+y = Admiration
		-y = Loathing

		+z = Vigilance
		-z = Amazement

		+w = Rage
		-w = Terror
	*/
	void addMod(Mods* m);
	void addDef(Defs* d);

	void ApplyTraits();
	void findNextState();
	void normaliseEmotion();
	void stateUpdate();
	void addEmotions(vec4 emo);

	stateMachine<NPC> *npcFSM;

};