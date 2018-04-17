#pragma once

#include "particle.h"
#include <vector>
#include <stdlib.h>
#include "GL/glut.h"


using namespace std;

typedef vector <particle> particleBuffer; // Particle container
typedef enum { FIRE = 1, WATER = 2 } TYPE_OF_EFFECT; // FOR ADDING MORE EFFECT TYPES LATER

/**
*@class paricleSystem
* @brief Used to setup and update a buffer of particles and to draw them.
*
* @author Matthew MacLennan
* @version 1.0
* @date 02 / 03 / 2018
*/
class particleSystem
{
public:
	particleBuffer pb; /// Buffer for particles.

	/**
	* @brief Set up effect variables
	*
	* @param pos(vec3) - New position.
	* @param position(vec3) - Position of the effect.
	* @param effectLife(int) - New life span of effect.
	* @param eLife(int) - Life span of the effect.
	*
	* @return NONE.
	*/
	void bufferInit(vec3 pos, int effectLife);

	/**
	* @brief Generates a particle based on effect position.
	*
	* @param tmpPos(vec3) - Temporary particle position.
	* @param tmpColour(vec4) - Temporary particle colour.
	* @param p(particle) - Particle being created.
	*
	* @return particle.
	*/
	particle generateParticle();

	/**
	* @brief Populates the buffer with particles.
	*
	* @param numOfParticles(int) - Number of particles in the effect.
	* @param life(int) - life span of the particle.
	*
	* @return NONE.
	*/
	void populateBuffer();

	/**
	* @brief Updates the particles in the buffer.
	*
	* @param Orange(vec4) - RGBA of orange.
	* @param darkOrange(vec4) - RGBA of dark orange.
	* @param lightOrange(vec4) - RGBA of light orange.
	* @param life(int) - Life span of particle.
	* @param pb[i](particle) - Particle being sent for update from buffer.
	*
	* @return bool.
	*/
	bool updateBuffer();

	/**
	* @brief Draws buffer.
	*
	* @param pb[i](particle) - Particle being drawn.
	*
	* @return NONE.
	*/
	void drawBuffer();

	/**
	* @brief Draws particle.
	*
	* @param p(particle) - Particle being drawn.
	*
	* @return NONE.
	*/
	void drawParticle(particle p);

	/**
	* @brief Gets effect position.
	*
	* @param position(vec3) - Position of effect.
	*
	* @return vec3.
	*/
	vec3 getEPos();

	/**
	* @brief Sets effect position.
	*
	* @param poisition(vec3) - Position of effect.
	* @param p(vec3) - New position of effect.
	*
	* @return NONE.
	*/
	void setEPos(vec3 p);

	/**
	* @brief Get effect life span.
	*
	* @param eLife(int) - Life span of effect.
	*
	* @return int.
	*/
	int getELife();

	/**
	* @brief Set effect life span.
	*
	* @param eLife(int) - Life span of effect.
	* @param l(int) - New life span of effect.
	*
	* @return NONE.
	*/
	void setELife(int l);

private:
	vec3 position; /// Position of effect.
	int eLife; /// Life span of effect.
};