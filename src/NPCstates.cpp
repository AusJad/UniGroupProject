#include "../include/NPCstates.h"
#include "../include/NPC.h"

void sit::Enter(NPC* agent)
{
	// code for entering "sit"
}

void sit::Execute(NPC* agent)
{
	// code for "sit" state
}

void sit::Exit(NPC* agent)
{
	// code for exiting "sit"
}

void toss::Enter(NPC* agent)
{
	// code for entering "toss"
}

void toss::Execute(NPC* agent)
{
	// code for "toss" state
}

void toss::Exit(NPC* agent)
{
	// code for exiting "toss"
}

void rage::Enter(NPC* agent)
{
	// code for entering "rage"
	agent->addemotion(vec4(0, 0, 0, 1)); // Max out rage
	
	// double check this is how it works.
	this->Execute(agent);
}

void rage::Execute(NPC* agent)
{
	// code for "toss" rage

	// select a random object and pathfind to it
	// once at object keep going "walking into it"
}

void rage::Exit(NPC* agent)
{
	// code for exiting "rage"

	if (agent->getemotion().w() <= agent->getdefault().w())
	{
		// exit state
	}
}

void avoid::Enter(NPC* agent)
{
	// code for entering "avoid"
	agent->addemotion(vec4(0, 0, 0, -1.0f)); // Max out terror

	this->Execute(agent);
}

void avoid::Execute(NPC* agent)
{
	// code for "avoid" rage

	// flee method from camera
}

void avoid::Exit(NPC* agent)
{
	// code for exiting "avoid"

	if (agent->getemotion().w() >= agent->getdefault().w())
	{
		// exit state
	}
}

void wander::Enter(NPC* agent)
{
	// code for entering "wander"

	
}

void wander::Execute(NPC* agent)
{
	vec3 tmp = agent->getPos();
	//std::cout << "In 'wander' X: " << tmp.x() << "Y:" << tmp.y() << std::endl;

	

}

void wander::Exit(NPC* agent)
{
	// code for exiting "wander"

}

void global::Enter(NPC* agent)
{
	// code for entering "global"
}

void global::Execute(NPC* agent)
{
	// code for "global" rage
}

void global::Exit(NPC* agent)
{
	// code for exiting "global"
}

