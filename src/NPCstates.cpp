#include "../include/NPCstates.h"
#include "../include/NPC.h"

void sit::Enter(NPC* agent)
{
	// Setting up map searching
	std::map<int, bool>::iterator it;
	std::map<int, bool> storage;
	std::vector<int> viableGOs;

	// Temp storage for target GameObject
	GameObject* targetGO;

	// RNG for target object selection
	int rng = 0;

	// Finding vector of viable "sitting" objects
	storage = agent->getAffordances()["SIT"];

	for (it = storage.begin(); it != storage.end(); it++)
	{
		if (it->second)
		{
			viableGOs.push_back(it->first);
		}
	}

	// Randomly select a viable "sitting" object
	srand(time(NULL));
	rng = rand() % viableGOs.size() - 1;

	// Generate waypoints to selected object
	for (int i = 0; i < viableGOs.size(); i++)
	{
		for (int j = 0; j < agent->getGOs().size(); j++)
		{
			if (agent->getGOs()[j]->getID() == viableGOs[i])
			{
				agent->generateWaypoints(agent->getGOs()[j]->getPos());
				targetGO = agent->getGOs()[j];
			}
		}
	}

	agent->setVel(physvec3(2, 0, 2));
	agent->setTarget(agent->getWaypoint().top());
}

void sit::Execute(NPC* agent)
{
	// If agent is within range of the waypoint pop waypoint and move to next
	if (abs(agent->getPos().x() - agent->getWaypoint().top().x()) < 100 && abs(agent->getPos().z() - agent->getWaypoint().top().z()) < 100)
	{
		agent->popWaypoint();
		agent->setTarget(agent->getWaypoint().top());
		std::cout << "Poped path" << std::endl;
	}

	if (agent->getWaypoint().empty())
	{
		// sit function here
		agent->setVel(physvec3(0, 0, 0));
		std::cout << "Agent " << agent->getID() << " is sitting." << std::endl;
	}

	agent->addemotion(vec4(-0.002, -0.001, 0, 0)); // Add some emotion to exit state
}

void sit::Exit(NPC* agent)
{
	// code for exiting "sit"
}

void toss::Enter(NPC* agent)
{
	// Setting up map searching
	std::map<int, bool>::iterator it;
	std::map<int, bool> storage;
	std::vector<int> viableGOs;

	// Temp storage for target GameObject
	GameObject* targetGO;

	// RNG for target object selection
	int rng = 0;

	// Finding vector of viable "sitting" objects
	storage = agent->getAffordances()["MOVE"];

	for (it = storage.begin(); it != storage.end(); it++)
	{
		if (it->second)
		{
			viableGOs.push_back(it->first);
		}
	}

	// Randomly select a viable "sitting" object
	srand(time(NULL));
	rng = rand() % viableGOs.size() - 1;

	// Generate waypoints to selected object
	for (int i = 0; i < viableGOs.size(); i++)
	{
		for (int j = 0; j < agent->getGOs().size(); j++)
		{
			if (agent->getGOs()[j]->getID() == viableGOs[i])
			{
				agent->generateWaypoints(agent->getGOs()[j]->getPos());
				targetGO = agent->getGOs()[j];
			}
		}
	}

	agent->setVel(physvec3(2, 0, 2));
	agent->setTarget(agent->getWaypoint().top());
}

void toss::Execute(NPC* agent)
{
	vec3 lastPos;
	// If agent is within range of the waypoint pop waypoint and move to next
	if (abs(agent->getPos().x() - agent->getWaypoint().top().x()) < 100 && abs(agent->getPos().z() - agent->getWaypoint().top().z()) < 100)
	{
		lastPos = agent->getWaypoint().top();
		agent->popWaypoint();
		agent->setTarget(agent->getWaypoint().top());
		std::cout << "Poped path" << std::endl;
	}

	if (agent->getWaypoint().empty())
	{
		agent->setTarget(lastPos);
		// throw/move function here
		std::cout << "Agent " << agent->getID() << " is Moving an object." << std::endl;
	}

	agent->addemotion(vec4(0.001, 0, 0, -0.002)); // Add some emotion to exit state
}

void toss::Exit(NPC* agent)
{
	// code for exiting "toss"
	agent->setVel(physvec3(0, 0, 0));
}

void rage::Enter(NPC* agent)
{
	// Setting up map searching
	std::map<int, bool>::iterator it;
	std::map<int, bool> storage;
	std::vector<int> viableGOs;

	// Temp storage for target GameObject
	GameObject* targetGO;

	// RNG for target object selection
	int rng = 0;

	// Finding vector of viable "sitting" objects
	storage = agent->getAffordances()["MOVE"];

	for (it = storage.begin(); it != storage.end(); it++)
	{
		for (int i = 0; i < agent->getGOs().size(); i++)
		{
			if (agent->getGOs()[i]->getIdentifiers().getType() == "CAM")
			{
				agent->generateWaypoints(agent->getGOs()[i]->getPos());
			}
		}
	}

	agent->setVel(physvec3(2, 0, 2));
	agent->setTarget(agent->getWaypoint().top());
}

void rage::Execute(NPC* agent)
{
	vec3 lastPos;
	// If agent is within range of the waypoint pop waypoint and move to next
	if (abs(agent->getPos().x() - agent->getWaypoint().top().x()) < 100 && abs(agent->getPos().z() - agent->getWaypoint().top().z()) < 100)
	{
		lastPos = agent->getWaypoint().top();
		agent->popWaypoint();
		agent->setTarget(agent->getWaypoint().top());
		std::cout << "Poped path" << std::endl;
	}

	if (agent->getWaypoint().empty())
	{
		agent->setTarget(lastPos);
		// throw/move function here
		std::cout << "Agent " << agent->getID() << " is Raging at you." << std::endl;
	}

	agent->addemotion(vec4(0.001, 0, 0, -0.002)); // Add some emotion to exit state
}

void rage::Exit(NPC* agent)
{
	agent->setVel(physvec3(0, 0, 0));
	// code for exiting "rage"
}

void avoid::Enter(NPC* agent)
{
	// Setting up map searching
	std::map<int, bool>::iterator it;
	std::map<int, bool> storage;
	std::vector<int> viableGOs;

	vec3 delta;

	// Temp storage for target GameObject
	GameObject* targetGO;

	// RNG for target object selection
	int rng = 0;

	// Finding vector of viable "sitting" objects
	storage = agent->getAffordances()["MOVE"];

	for (it = storage.begin(); it != storage.end(); it++)
	{
		for (int i = 0; i < agent->getGOs().size(); i++)
		{
			if (agent->getGOs()[i]->getIdentifiers().getType() == "CAM")
			{
				//delta = agent->getGOs()[i]->getPos() - agent->getPos(); // Weird physvec3 errors
				// just doing subtraction by hand

				delta.sx(agent->getGOs()[i]->getPos().x() - agent->getPos().x());
				delta.sy(agent->getGOs()[i]->getPos().y() - agent->getPos().y());
				delta.sz(agent->getGOs()[i]->getPos().z() - agent->getPos().z());

				delta.normailse();

				delta.sx(delta.x() + 100);
				delta.sz(delta.z() + 100);

				agent->generateWaypoints(delta);
			}
		}
	}

	agent->setVel(physvec3(2, 0, 2));
	agent->setTarget(agent->getWaypoint().top());
}

void avoid::Execute(NPC* agent)
{
	vec3 lastPos;
	// If agent is within range of the waypoint pop waypoint and move to next
	if (abs(agent->getPos().x() - agent->getWaypoint().top().x()) < 100 && abs(agent->getPos().z() - agent->getWaypoint().top().z()) < 100)
	{
		lastPos = agent->getWaypoint().top();
		agent->popWaypoint();
		agent->setTarget(agent->getWaypoint().top());
		std::cout << "Poped path" << std::endl;
	}

	if (agent->getWaypoint().empty())
	{
		agent->setTarget(lastPos);
		agent->setVel(physvec3(0, 0, 0));
		// throw/move function here
		std::cout << "Agent " << agent->getID() << " is running from you." << std::endl;
	}

	agent->addemotion(vec4(-0.001, 0, 0, 0.002)); // Add some emotion to exit state
}

void avoid::Exit(NPC* agent)
{
	// code for exiting "avoid"
}

void wander::Enter(NPC* agent)
{
	// code for entering "wander"
}

void wander::Execute(NPC* agent)
{
	// code for "wander"
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