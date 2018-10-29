#pragma once
#ifndef __NPCSTATES_H
#define __NPCSTATES_H

#include "singleton.h"
#include "state.h"

#include <cstdlib>
#include <ctime>

class NPC;

class sit : public State<NPC>
{
	~sit() {}
	void Enter(NPC* agent);
	void Execute(NPC* agent);
	void Exit(NPC* agent);
};

class toss : public State<NPC>
{
	~toss() {}
	void Enter(NPC* agent);
	void Execute(NPC* agent);
	void Exit(NPC* agent);
};

class rage : public State<NPC>
{
	~rage() {}
	void Enter(NPC* agent);
	void Execute(NPC* agent);
	void Exit(NPC* agent);
};

class avoid : public State<NPC>
{
	~avoid() {}
	void Enter(NPC* agent);
	void Execute(NPC* agent);
	void Exit(NPC* agent);
};

class wander : public State<NPC>
{
	~wander() {}
	void Enter(NPC* agent);
	void Execute(NPC* agent);
	void Exit(NPC* agent);
};

class global : public State<NPC>
{
	~global() {}
	void Enter(NPC* agent);
	void Execute(NPC* agent);
	void Exit(NPC* agent);
};

typedef Singleton<sit> sit_state;
typedef Singleton<toss> throw_state;
typedef Singleton<rage> rage_state;
typedef Singleton<avoid> avoid_state;
typedef Singleton<wander> wander_state;
typedef Singleton<global> global_state;
#endif
