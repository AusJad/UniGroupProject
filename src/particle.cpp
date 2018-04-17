#include "particle.h"

// Default constructor.
particle::particle()
{

}


// Constructor with all arguements.
particle::particle(vec3 pos, vec3 vel, vec4 col, int l, float s)
{
	position = pos;
	velocity = vel;
	colour = col;
	life = l;
	size = s;
}

// Start gets and sets.
vec3 particle::getPos()
{
	return position;
}

void particle::setPos(vec3 p)
{
	position = p;

}

vec3 particle::getVel()
{
	return velocity;
}

void particle::setVel(vec3 v)
{
	velocity = v;
}

vec4 particle::getColour()
{
	return colour;
}

void particle::setColour(vec4 c)
{
	colour = c;
}

int particle::getLife()
{
	return life;
}

void particle::setLife(int l)
{
	life = l;
}

float particle::getSize()
{
	return size;
}

void particle::setSize(float s)
{
	size = s;
}
// End gets and sets.

// Updates movement vector by adding current velocity vector to it.
void particle::update()
{
	position.add(velocity);
	life--;
}