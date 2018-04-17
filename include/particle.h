#pragma once

#include "Maths.h"

/**
* @class paricle
* @brief Used to define particles for particle effects.
*
* @author Matthew MacLennan
* @version 1.0
* @date 02/03/2018
*/
class particle
{
public:
	particle(); // Default constructor
	particle(vec3 pos, vec3 vel, vec4 col, int l, float s);  // Constructor with all arguments

	/**
	* @brief Gets position vector.
	*
	* @param position(vec3) - Particle position.
	*
	* @return vec3.
	*/
	vec3 getPos();
	/**
	* @brief Sets position vector.
	*
	* @param position(vec3) - Particle position.
	* @param p(vec3) - New position of particle.
	*
	* @return NONE.
	*/
	void setPos(vec3 p);
	/**
	* @brief Gets velocity vector.
	*
	* @param velocity(vec3) - Particle velocity.
	*
	* @return vec3.
	*/
	vec3 getVel();
	/**
	* @brief Sets velocity vector.
	*
	* @param velocity(vec3) - Particle velocity.
	* @param v(vec3) - New velocity of particle.
	*
	* @return NONE.
	*/
	void setVel(vec3 v);
	/**
	* @brief Gets colour vector.
	*
	* @param colour(vec4) - Particle colour.
	*
	* @return vec4.
	*/
	vec4 getColour();
	/**
	* @brief Sets colour vector.
	*
	* @param colour(vec4) - Particle colour.
	* @param c(vec4) - New colour of particle.
	*
	* @return NONE.
	*/
	void setColour(vec4 c);
	/**
	* @brief Gets life.
	*
	* @param life(int) - Particle life.
	*
	* @return int.
	*/
	int getLife();
	/**
	* @brief Sets life.
	*
	* @param life(int) - Particle life.
	* @param l(int) - New life of particle.
	*
	* @return NONE.
	*/
	void setLife(int l);
	/**
	* @brief Gets size.
	*
	* @param size(float) - Particle size.
	*
	* @return float.
	*/
	float getSize();
	/**
	* @brief Sets size.
	*
	* @param size(float) - Particle size.
	* @param s(float) - New size of particle.
	*
	* @return NONE.
	*/
	void setSize(float s);

	/**
	* @brief Updates movement of particle based on velocity.
	*
	* @param particle(particle) - The particle container object containing all information about the particle.
	*
	* @return NONE.
	*/
	void update();

private:
	vec3 position;  /// Position of particle.
	vec3 velocity; /// Velocity of particle.
	vec4 colour; /// RGBA value of particle.
	int life; /// Life span counter of particle.
	float size; /// Physical size of particle.

};

