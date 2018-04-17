#include "particleSystem.h"

void particleSystem::bufferInit(vec3 pos, int effectLife)
{
	position = pos;
	eLife = effectLife;
}

bool particleSystem::updateBuffer()
{
	// Start setting up colouring vectors.
	vec4 orange;
	vec4 darkOrange;
	vec4 lightOrange;

	orange[0] = 255; // r
	orange[1] = 165; // g
	orange[2] = 0; // b
	orange[3] = 0; // a

	darkOrange[0] = 255;
	darkOrange[1] = 140;
	darkOrange[2] = 0;
	darkOrange[3] = 0;

	lightOrange[0] = 240;
	lightOrange[1] = 128;
	lightOrange[2] = 128;
	lightOrange[3] = 0;
	// End setting up colouring vectors.

	// Loop to go through buffer
	for (int i = 0; i < pb.size(); i++)
	{
		// If particle life is 0 or lower reuse dead particle
		if (pb[i].getLife() < 0 && getELife() > 0)
		{
			//pb.erase(pb.begin() + i); // Erases the particle if its life is 0 or lower.
			pb[i] = generateParticle();
		}

		// THIS COLOURING LOOP IS FOR FIRE ONLY.
		if (pb[i].getLife() < 100) // assuming max life 150
		{
			pb[i].setColour(darkOrange);
		}
		else if (pb[i].getLife() < 75)
		{
			pb[i].setColour(orange);
		}
		else if (pb[i].getLife() < 75)
		{
			pb[i].setColour(lightOrange);
		}
	}
	/*  only needed if erasing particles
	if (pb.size() <= 0)
	{
		return false;
	}
	*/

	eLife--;

	return true;
	
}

particle particleSystem::generateParticle()
{
	// Generate randomized starting positions for the particles within 5 10 points of position of effect.
	vec3 tmpPos;
	tmpPos[0] = position[0] + (float)(rand() % 5 + -5);
	tmpPos[1] = position[1] + (float)(rand() % 5 + -5);
	tmpPos[2] = position[2] + (float)(rand() % 5 + -5);

	particle p;
	p.setPos(tmpPos);

	// Generate randomized life for particles.
	p.setLife(rand() % 150); // Creates a random life for the particle between 1 and 150

	// IF LOOP HERE IF MORE TYPE EFFECTS ARE ADDED FOR DIFFERENT COLOURS
	// DEFAULTED TO FIRE COLOURING
	vec4 tmpColour;
	tmpColour[0] = 255.0f;
	tmpColour[1] = 0.0f;
	tmpColour[2] = 0.0f;
	tmpColour[3] = 0.0f;

	p.setColour(tmpColour);
	
	// Setting default size of particles. ** NOTE -- THIS IS A ASSUMPTION BUT THIS VARIABLE CAN EASILY BE CHANGED AS ITS ONLY WRITTEN ONCE AND THE SIZE WONT CHANGE **
	p.setSize(1.0);
	return p;
}

void particleSystem::populateBuffer()
{
	// DEFAULT NUMBER OF PARTICLES CAN BE CHANGED LATER IF MORE EFFECTS ARE ADDED TO A TYPEDEF THAT CHANGES DEPENDING ON TYPE OF EFFECT
	int numOfParticles = 150;

	// Populates buffer with number of particles required for effect.
	for (int i = 0; i < numOfParticles; i++)
	{
		if (pb[i].getLife() <= 0)
		{
			pb[i] = generateParticle();
		}
	}
}

void particleSystem::drawBuffer()
{
	// Cycle through buffer and draw each particle in it.
	for (int i = 0; i < pb.size(); i++)
	{
		drawParticle(pb[i]);
	}
}

// GL draw function.
void particleSystem::drawParticle(particle p)
{
	glDepthMask(GL_FALSE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glColor4f(p.getColour()[0] * cos((float)(rand() % 1)), p.getColour()[1] * cos((float)(rand() % 1)), p.getColour()[2] * cos((float)(rand() % 1)), p.getLife * 0.02);
	glBegin(GL_QUADS);
	glVertex3f(p.getPos()[0], p.getPos()[1], p.getPos()[2] + p.getSize());
	glVertex3f(p.getPos()[0] + p.getSize(), p.getPos()[1], p.getPos()[2] + p.getSize());
	glVertex3f(p.getPos()[0] + p.getSize(), p.getPos()[1] + p.getSize(), p.getPos()[2] + p.getSize());
	glVertex3f(p.getPos()[0], p.getPos()[1] + p.getSize(), p.getPos()[2] + p.getSize());

	glVertex3f(p.getPos()[0], p.getPos()[1], p.getPos()[2]);
	glVertex3f(p.getPos()[0] + p.getSize(), p.getPos()[1], p.getPos()[2]);
	glVertex3f(p.getPos()[0] + p.getSize(), p.getPos()[1] + p.getSize(), p.getPos()[2]);
	glVertex3f(p.getPos()[0], p.getPos()[1] + p.getSize(), p.getPos()[2]);

	glVertex3f(p.getPos()[0], p.getPos()[1], p.getPos()[2]);
	glVertex3f(p.getPos()[0] + p.getSize(), p.getPos()[1], p.getPos()[2]);
	glVertex3f(p.getPos()[0] + p.getSize(), p.getPos()[1], p.getPos()[2] + p.getSize());
	glVertex3f(p.getPos()[0], p.getPos()[1], p.getPos()[2] + p.getSize());

	glVertex3f(p.getPos()[0], p.getPos()[1] + p.getSize(), p.getPos()[2]);
	glVertex3f(p.getPos()[0] + p.getSize(), p.getPos()[1] + p.getSize(), p.getPos()[2]);
	glVertex3f(p.getPos()[0] + p.getSize(), p.getPos()[1] + p.getSize(), p.getPos()[2] + p.getSize());
	glVertex3f(p.getPos()[0], p.getPos()[1] + p.getSize(), p.getPos()[2] + p.getSize());

	glVertex3f(p.getPos()[0], p.getPos()[1], p.getPos()[2]);
	glVertex3f(p.getPos()[0], p.getPos()[1] + p.getSize(), p.getPos()[2]);
	glVertex3f(p.getPos()[0], p.getPos()[1] + p.getSize(), p.getPos()[2] + p.getSize());
	glVertex3f(p.getPos()[0], p.getPos()[1], p.getPos()[2] + p.getSize());

	glVertex3f(p.getPos()[0] + p.getSize(), p.getPos()[1], p.getPos()[2]);
	glVertex3f(p.getPos()[0] + p.getSize(), p.getPos()[1] + p.getSize(), p.getPos()[2]);
	glVertex3f(p.getPos()[0] + p.getSize(), p.getPos()[1] + p.getSize(), p.getPos()[2] + p.getSize());
	glVertex3f(p.getPos()[0] + p.getSize(), p.getPos()[1], p.getPos()[2] + p.getSize());

	glEnd();
	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);
}

vec3 particleSystem::getEPos()
{
	return position;
}

void particleSystem::setEPos(vec3 p)
{
	position = p;
}

int particleSystem::getELife()
{
	return eLife;
}

void particleSystem::setELife(int l)
{
	eLife = l;
}